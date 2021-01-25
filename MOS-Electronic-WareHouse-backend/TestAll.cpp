#include "TestAll.h"


void Check(TypeAndSizePosition& p, TypePosition t, string n) {
    if (p.GetType() != t) {
        throw invalid_argument(n);
    }
}
void TestTypeAndPosition() {
    {
        TypeAndSizePosition a = { 500, 900, 1000 };
        Check(a, TypePosition::Small, "1");
    }
    {
        TypeAndSizePosition a = { 2000, 1000, 1000 };
        Check(a, TypePosition::Medium, "2");
    }
    {
        TypeAndSizePosition a = { 1000, 1900, 2000 };
        Check(a, TypePosition::Big, "3");
    }
    {
        TypeAndSizePosition a = { 1000, 1000, 1000 };
        Check(a, TypePosition::Small, "4");
    }
    {
        TypeAndSizePosition a = { 1000, 2000, 1000 };
        Check(a, TypePosition::Medium, "5");
    }
    {
        TypeAndSizePosition a = { 300, 300, 300 };
        Check(a, TypePosition::Small, "6");
    }
    {
        TypeAndSizePosition a = { 200, 500, 2100 };
        Check(a, TypePosition::RemoteWarehouse, "7");
    }
    {
        TypeAndSizePosition a = { 1000, 1200, 2000 };
        Check(a, TypePosition::Big, "8");
    }
}
void TestWareHouse() {
    {
        WareHouse wh;
        wh.AddElement(Cell(TypePosition::Small, Position("uud1131"), { "A1" }));
        Cell c = wh.GetElementToUUID("uud1131");
        if (c.posit.GetUUid() != "uud1131") {
            throw logic_error("WareHouse logic Error: test 1");
        }
    }
}

void TestAll()
{
    try {
        TestTypeAndPosition();
        TestWareHouse();
    }
    catch (exception ex) {
        cout << "!!Exception: " << ex.what();
        exit(-1);
    }
    cout << "Tests OK!";
}