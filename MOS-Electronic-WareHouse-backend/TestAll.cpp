#include "TestAll.h"
#include "DataBase.h"

template <class Value, class Valid>
void Check(Value p, Valid t, string n) {
    if (p != t) {
        throw invalid_argument(n);
    }
}
void TestTypeAndPosition() {
    {
        TypeAndSizePosition a = { 500, 900, 1000 };
        Check(a.GetType(), TypePosition::Small, "1");
    }
    {
        TypeAndSizePosition a = { 2000, 1000, 1000 };
        Check(a.GetType(), TypePosition::Medium, "2");
    }
    {
        TypeAndSizePosition a = { 1000, 1900, 2000 };
        Check(a.GetType(), TypePosition::Big, "3");
    }
    {
        TypeAndSizePosition a = { 1000, 1000, 1000 };
        Check(a.GetType(), TypePosition::Small, "4");
    }
    {
        TypeAndSizePosition a = { 1000, 2000, 1000 };
        Check(a.GetType(), TypePosition::Medium, "5");
    }
    {
        TypeAndSizePosition a = { 300, 300, 300 };
        Check(a.GetType(), TypePosition::Small, "6");
    }
    {
        TypeAndSizePosition a = { 200, 500, 2100 };
        Check(a.GetType(), TypePosition::RemoteWarehouse, "7");
    }
    {
        TypeAndSizePosition a = { 1000, 1200, 2000 };
        Check(a.GetType(), TypePosition::Big, "8");
    }
}
void TestWareHouse() {
    string Error = "WareHouse logic Error: ";
    {
        WareHouse wh;
        wh.AddElement(Cell(TypePosition::Small, Position("uud1131"), { "A1" }));
        Cell c = wh.GetElementToUUID("uud1131");
        Check(c.posit.GetUUid(), "uud1131", Error + "test 1");
    }
    {
        WareHouse wh;
        auto i = wh.GetElementToUUID("0000");
        Check(i.Error, true, Error + "test 2");
    }
}

/*void TestDBSystem() {
    DataBase db("test.db");
    cout << db.SelectData("SELECT * FROM WareHouse Where TypeCell = 'Midlle' AND Empty = 0 ORDER BY HeightCell");
}*/
void TestAll()
{
    try {
        TestTypeAndPosition();
        //TestWareHouse();
        //TestDBSystem();
    }
    catch (exception ex) {
        cout << "!!Exception: " << ex.what();
        exit(-1);
    }
    cout << "Tests OK!";
}