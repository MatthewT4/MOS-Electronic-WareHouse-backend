#pragma once;

using namespace std;

enum class TypePosition {
    Small, //1000*1000*1000
    Medium, //1000*2000*1000
    Big, //2000*2000*1000
    RemoteWarehouse //удалённый склад.
};
 
class Position {
public:
    Position(const int& x, const int& y, const int& z) {
        if (x <= 1000 and y <= 1000 and z <= 1000) {
            height = x;
            width = y;
            depth = z;
        }
    }
private:
    int height;
    int width;
    int depth;
    TypePosition type;
};
/* unit test:
        300*300*300 -> Small
        200*500*2100 -> RemoteWarehouse
        1000*1200*2000 -> Big
        

        
*/
