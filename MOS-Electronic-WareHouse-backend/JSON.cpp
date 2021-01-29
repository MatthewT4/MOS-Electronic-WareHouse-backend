#include <nlohmann/json.hpp>
#include <iostream>
#include <vector>
#include <exception>
#include "HTTP.h"
#include "JSON.h"


using json = nlohmann::json;

POSTJSON GetScheme(const string& ip, const int& PORT) {
    POSTJSON post;
    try {
        //std::string responseString = GetJsonByHTTP("http://127.0.0.1/scheme", 5000);
        json responseJson = json::parse(GetJsonByHTTP(ip, PORT));
        json object1 = responseJson["size"];
        json object2 = responseJson["merged"];
        post.size_x = object1["size_x"];
        post.size_y = object1["size_y"];
        post.size_z = object1["size_z"];
        std::vector<vector<string>> vec = object2;
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
    catch (exception& ex) {
        cerr << "Error: JSON fatal error: " << ex.what() << endl;
        exit(1);
    }
    return post;
}