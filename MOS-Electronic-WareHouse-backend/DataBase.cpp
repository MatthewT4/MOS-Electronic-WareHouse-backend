#include "DataBase.h"
#include <sstream>
#include <exception>
std::string Result = "";
static bool Che = false;
static bool IsInt(std::string Val) {
    /*try {
        std::stringstream ss;
        int a;
        ss << Val;
        ss >> a;
        return true;
    }
    catch (_exception ex) {
        return false;
    }*/
    std::string Valid = "1234567890";
    bool C = false;
    for (const auto& i : Val) {
        C = false;
        for (const auto& t : Valid) {
            if (i == t) {
                C = true;
            }
        }
        if (!C) {
            return false;
        }
    }
    return true;
}

static int SelectCallback(void* NotUsed, int argc, char** argv, char** azColName) {
    int i;
    std::string Value;
    if (Che) {
        Result += ", ";
    }
    else { Che = true; }
    Result += "{";
    bool ch = false;
    for (i = 0; i < argc; i++) {
        //Result += "%s = %s\n" + azColName[i] + argv[i] ? argv[i] : "NULL";
        if (ch) {
            Result += ", ";
        }
        else {
            ch = true;
        }
        Result += '"';
        Result += azColName[i];
        Result += '"';
        Result += ": ";
        Value = (argv[i] ? argv[i] : "NULL");
        if (IsInt(Value)) {
            Result += Value;
        }
        else {
            Result += '"';
            Result += Value;
            Result += '"';

        }
        //Result += (argv[i] ? argv[i] : "NULL");
    }
    Result += "}";
    return 0;
}

DataBase::DataBase(std::string DBName) {
    rc = sqlite3_open(DBName.c_str(), &db);
    if (rc) {
        throw std::domain_error("Can't open database:" + *sqlite3_errmsg(db));
    }
};
DataBase::~DataBase() {
    sqlite3_free(zErrMsg);
    sqlite3_close(db);
}
std::string DataBase::SelectData(std::string GetData) {
    Result = "{";
    Result += "\"status\": 200, \"body\": [";

    const char* sql = GetData.c_str();
    Che = false;
    rc = sqlite3_exec(db, sql, SelectCallback, 0, &zErrMsg);
    Result += "]}";
    if (rc != SQLITE_OK) {
       // fprintf(stderr, "[SQL error]: ", zErrMsg);
        std::cerr << "[SQL error]: " << zErrMsg << std::endl;
        return "{\"status\": 404}";
    }
    return Result;
}

void TestDB() {
    DataBase db("test.db");
    std::cout << db.SelectData("SELECT * FROM WareHouse Where TypeCell = 'Midlle' AND Empty = 0 ORDER BY HeightCell") << std::endl << std::endl;
}
