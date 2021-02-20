#include <nlohmann/json.hpp>
#include <iostream>
#include <vector>
#include <exception>
#include "HTTP.h"
#include "JSON.h"
#include "Position.h"


using json = nlohmann::json;
/*Парсинг схемы склада из JSON, полученного от удалённого сервера*/
POSTJSON GetScheme(const std::string& ip, const int& PORT) {
    POSTJSON post;
    try {
        //std::string responseString = GetJsonByHTTP("http://127.0.0.1/scheme", 5000);
        json responseJson = json::parse(GetJsonByHTTP(ip, PORT));
        json object1 = responseJson["size"];
        json object2 = responseJson["merged"];
        post.size_x = object1["size_x"];
        post.size_y = object1["size_y"];
        post.size_z = object1["size_z"];
        std::vector<std::vector<std::string>> vec = object2;
        post.vecAssociations = vec;
        /*
        cout << "x = " << post.size_x << endl;
        cout << "y = " << post.size_y << endl;
        cout << "z = " << post.size_z << endl;
        cout << endl << endl;
        for (auto& i : post.vecAssociations) {
            for (auto& j : i) {
                cout << j << " ";
            }
            cout << endl;
        }*/
    }
    catch (std::exception& ex) {
        std::cerr << "Error: JSON fatal error: " << ex.what() << std::endl;
        exit(1);
    }
    return post;
}
//{'body' = [{'name', 'uuid', height, width,}]}
/*Парсинг в вектор Position для добавления позиций из JSON. */
std::vector<Position> GetAddPositionFromJSON(std::string strJson) {
    std::vector<Position> VecPos;
    json JSON = json::parse(strJson);
    json body = JSON["body"];
    size_t Count = body.size();
    for (size_t i = 0; i < Count; i++) {
        Position VrPos(body[i]["Name"], body[i]["Weight"], 
            TypeAndSizePosition(body[i]["Height"], body[i]["Width"], body[i]["Depth"]), body[i]["UUID"], body[i]["Comment"]); //comment!!
        VecPos.push_back(VrPos);
    }
    return VecPos;
    //json body = JSON["body"][0]["name"];

}

/*Парсинг в вектор UUID элементов для выдачи из JSON.*/
std::vector<string> GetIssuePositionFromJSON(std::string strJson) {
    json JSON = json::parse(strJson);
    json body = JSON["UUID"];
    std::vector<string> ret;
    size_t Count = body.size();
    for (size_t i = 0; i < Count; i++) {
        ret.push_back(body[i]);
    }
    //vector<string> Vec = JSON;
    return ret;
}