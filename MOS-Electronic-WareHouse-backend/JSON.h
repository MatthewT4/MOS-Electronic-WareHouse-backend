#pragma once

#include <vector>
#include <string>
#include "JSON.h"
#include "Position.h"

/*{"size": {"size_x": 6, "size_y": 3, "size_z": 1}, 
"merged": [["A1", "A2"], ["B2", "B3"], ["C1", "C2"], ["D2", "D3"], ["E2", "E3", "F2", "F3"]]}*/

struct POSTJSON {
    int size_x;
    int size_y;
    int size_z;
    std::vector<std::vector<std::string>> vecAssociations;
};

POSTJSON GetScheme(const std::string& ip, const int& PORT);

/*curl --header "Content-Type: application/json" --request POST 
--data "{"body": {["Name": "dddd","UUID": "1ddevefffwewdef","Height": 30,"Width": 150,
"Depth": 700,"Weight": 200]}}' http://localhost/data*/
std::vector<Position> GetPositionFromJSON(std::string strJson);