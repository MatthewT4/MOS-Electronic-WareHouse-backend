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

Position::Position() {}
Position::Position(string InName, int InWeight, TypeAndSizePosition InSizeAndType) : name(InName), weigt(InWeight), sizeAndType(InSizeAndType) {
    //uuid = generateUUID()
}
Position::Position(string InName, int InWeight, TypeAndSizePosition InSizeAndType, string InUuid) : name(InName),
weigt(InWeight), sizeAndType(InSizeAndType), uuid(InUuid) {
    //uuid = generateUUID()
}
Position::Position(string InName, int InWeight, TypeAndSizePosition InSizeAndType, string InUuid, string InComment) : name(InName),
weigt(InWeight), sizeAndType(InSizeAndType), uuid(InUuid), comment(InComment){
    //uuid = generateUUID()
}
Position::Position(string InUUID) : uuid(InUUID) {} //debug, delete continue!!!!!!
string Position::GetUUid() {
    return uuid;
}
TypePosition Position::GetTypePosition() {
    return sizeAndType.GetType();
}
int Position::GetWeigt() { return weigt; }
int Position::GetDepth() { return sizeAndType.GetDepth(); }
int Position::GetHeight() { return sizeAndType.GetHeight(); }
int Position::GetWidth() { return sizeAndType.GetWidth(); }
std::string Position::GetName() { return name; }
std::string Position::GetComment() { return comment; }
void Position::SetComment(std::string comm) { comment = comm; }
