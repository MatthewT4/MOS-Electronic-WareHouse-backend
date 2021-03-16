#pragma once;
#include <string>
using namespace std;


/*enum типо-размеров*/
enum class TypePosition {
    Small, //1000*1000*1000
    Medium, //1000*2000*1000
    Big, //2000*2000*1000
    RemoteWarehouse //удалённый склад.
};
 
class TypeAndSizePosition {
public:
    TypeAndSizePosition() {}
    /*Добавление позиции по входным данным. Нахождение типа позиции*/
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
    int GetHeight() { return height; }
    int GetWidth() { return width; }
    int GetDepth() { return depth; }
private:
    int height = 0;
    int width = 0;
    int depth = 0;
    TypePosition type = TypePosition::RemoteWarehouse;
};
/*оператор сложения строки и типа-размера*/
string operator+(string st, TypePosition tp);

class Position {
public:
    /*Конструктор по умолчанию, только создаёт переменную.*/
    Position();
    /*Создание переменной по имени, весу и размерам, определяется типо-размер*/
    Position(string InName, int InWeight, TypeAndSizePosition InSizeAndType);
    /*Создание переменной по имени, весу, UUID и размерам, определяется типо-размер*/
    Position(string InName, int InWeight, TypeAndSizePosition InSizeAndType, string InUuid);
    /*Создание переменной по имени, весу, комментарию, UUID и размерам, определяется типо-размер*/
    Position(string InName, int InWeight, TypeAndSizePosition InSizeAndType, string InUuid, string InComment);
    Position(string InUUID); //debug.
    /*Получить UUID позиции*/
    string GetUUid();
    /*Получить размеры позиции*/
    TypePosition GetTypePosition();
    /*Получить вес позиции.*/
    int GetWeigt();
    /*Получить длины позиции.*/
    int GetDepth();
    /*Получить высоты позиции.*/
    int GetHeight();
    /*Получить ширины позиции.*/
    int GetWidth();
    /*Получить имени позиции.*/
    std::string GetName();
    /*Получить комментария к позиции.*/
    std::string GetComment();
    /*Установить комментарий позиции.*/
    void SetComment(std::string comm);
    

private:
    std::string name;
    int weigt;
    TypeAndSizePosition sizeAndType;
    std::string uuid;
    std::string comment = "";
};
