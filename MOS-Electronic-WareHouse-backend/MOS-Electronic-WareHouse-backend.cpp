#include <iostream>
#include <stdio.h>
#include "Position.h"
#include <stdexcept>
#include "TestAll.h"
#include "HTTP.h"
#include "JSON.h"
#include "DataBase.h"
using namespace std;



int main()
{
    TestDB();
    cout << GetJsonByHTTP("http://127.0.0.1/scheme", 5000) << endl << endl;
    GetScheme("http://127.0.0.1/scheme", 5000);
    TestAll();
    return 0;
}
 