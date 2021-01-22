#include <iostream>
#include <stdio.h>
#include "Position.h"
#include <stdexcept>

using namespace std; 


void Check(TypeAndSizePosition& p, TypePosition t, string n) {
    if (p.GetType() != t) {
        throw invalid_argument(n);
    }
}
void TestAll() {
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

int main()
{
    try {
        TestAll();
    }
    catch (exception ex) {
        cout << "!!Exception: " << ex.what();
        return 0;
    }
    cout << "Tests OK!";
    return 0;
}
