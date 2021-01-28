#pragma once
#include <nlohmann/json.hpp>
#include <iostream>
#include <vector>
#include "HTTP.h"
using json = nlohmann::json;
/*{"size": {"size_x": 6, "size_y": 3, "size_z": 1}, 
"merged": [["A1", "A2"], ["B2", "B3"], ["C1", "C2"], ["D2", "D3"], ["E2", "E3", "F2", "F3"]]}*/
int GetScheme(const string& ip, const int& PORT) {
    //std::string responseString = GetJsonByHTTP("http://127.0.0.1/scheme", 5000);
    json responseJson = json::parse(GetJsonByHTTP(ip, PORT));
    json object1 = responseJson["size"];
    json object2 = responseJson["merged"];
    int x = object1["size_x"];
    int y = object1["size_y"];
    int z = object1["size_z"];
    std::vector<vector<string>> vec = object2;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
    cout << "z = " << z << endl;
    cout << endl << endl;
    for (auto& i : vec) {
        for (auto& j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
    return 0;
}