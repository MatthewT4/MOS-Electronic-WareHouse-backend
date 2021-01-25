#pragma once;
//#pragma comment(lib, "rpcrt4.lib")  // UuidCreate - Minimum supported OS Win 2000
//#include <windows.h>
using namespace std;



enum class TypePosition {
    Small, //1000*1000*1000
    Medium, //1000*2000*1000
    Big, //2000*2000*1000
    RemoteWarehouse //удалённый склад.
};
 
class TypeAndSizePosition {
public:
    TypeAndSizePosition(const int& x, const int& y, const int& z) {
        // Small
        if (x <= 1000 and y <= 1000 and z <= 1000) {
            height = x;
            width = y;
            depth = z;
            type = TypePosition::Small;
        }

        // Medium

        else if (x <= 1000 and y <= 2000 and z <= 1000) {
            height = x;
            width = y;
            depth = z;
            type = TypePosition::Medium;
        }

        else if (x <= 2000 and y <= 1000 and z <= 1000) {
            height = y;
            width = x;
            depth = z;
            type = TypePosition::Medium;
        }

        else if (x <= 1000 and y <= 1000 and z <= 2000) {
            height = z;
            width = y;
            depth = x;
            type = TypePosition::Medium;
        }

        //Big

        else if (x <= 2000 and y <= 2000 and z <= 1000) {
            height = x;
            width = y;
            depth = z;
            type = TypePosition::Big;
        }

        else if (x <= 2000 and y <= 1000 and z <= 2000) {
            height = x;
            width = z;
            depth = y;
            type = TypePosition::Big;
        }

        else if (x <= 1000 and y <= 2000 and z <= 2000) {
            height = z;
            width = y;
            depth = x;
            type = TypePosition::Big;
        }

        else {
            height = x;
            width = y;
            depth = z;
            type = TypePosition::RemoteWarehouse;
        }
    }
    TypePosition GetType() {
        return type;
    }
private:
    int height;
    int width;
    int depth;
    TypePosition type;
};

class Position {
public:
    Position(string InName, int InWeight, TypeAndSizePosition InSizeAndType) : name(InName), weigt(InWeight), sizeAndType(InSizeAndType) {
        //uuid = generateUUID()
    }
private:
    string name;
    int weigt;
    TypeAndSizePosition sizeAndType;
    string uuid;
};
/* unit test:
        300*300*300 -> Small
        200*500*2100 -> RemoteWarehouse
        1000*1200*2000 -> Big
        

        
*/
