#pragma once

#include <vector>
#include <string>
/*{"size": {"size_x": 6, "size_y": 3, "size_z": 1}, 
"merged": [["A1", "A2"], ["B2", "B3"], ["C1", "C2"], ["D2", "D3"], ["E2", "E3", "F2", "F3"]]}*/

struct POSTJSON {
    int size_x;
    int size_y;
    int size_z;
    std::vector<std::vector<std::string>> vecAssociations;
};
POSTJSON GetScheme(const string& ip, const int& PORT);