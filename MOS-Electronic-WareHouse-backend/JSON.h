#pragma once

#include <vector>
#include <string>
#include "JSON.h"
#include "Position.h"

/*{"size": {"size_x": 6, "size_y": 3, "size_z": 1}, 
"merged": [["A1", "A2"], ["B2", "B3"], ["C1", "C2"], ["D2", "D3"], ["E2", "E3", "F2", "F3"]]}*/


/*структура конфигурации склада, возвращаемая из парсера.*/
struct POSTJSON {
    int size_x;
    int size_y;
    int size_z;
    std::vector<std::vector<std::string>> vecAssociations;
};

/*Парсинг схемы склада из JSON, полученного от удалённого сервера*/
POSTJSON GetScheme(const std::string& ip, const int& PORT);

/*curl --header "Content-Type: application/json" --request POST 
--data "{"body": {["Name": "dddd","UUID": "1ddevefffwewdef","Height": 30,"Width": 150,
"Depth": 700,"Weight": 200]}}' http://localhost/data*/


/*Парсинг в вектор Position для добавления позиций из JSON. */
std::vector<Position> GetAddPositionFromJSON(std::string strJson);

/*Парсинг в вектор UUID элементов для выдачи из JSON.*/
std::vector<string> GetIssuePositionFromJSON(std::string strJson);