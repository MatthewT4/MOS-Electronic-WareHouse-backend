#include "Position.h"

void Test() {
    string InName = "Book";
    int Inheight = 10,
        Inwidth = 5,
        Indepth = 3,
        Inweigt = 2;
    Position Pos1 = { InName, Inweigt, TypeAndSizePosition(Inheight, Inwidth, Inweigt) };
    //создание элемента position
}

string operator+(string st, TypePosition tp) {
    std::string tpTost = "";
    if (tp == TypePosition::Small) {
        tpTost = "Small";
    }
    else if (tp == TypePosition::Medium) {
        tpTost = "Medium";
    }
    else if (tp == TypePosition::Big) {
        tpTost = "Big";
    }
    else if (tp == TypePosition::RemoteWarehouse) {
        tpTost = "RemoteWarehouse";
    }
    return st + tpTost;
}
