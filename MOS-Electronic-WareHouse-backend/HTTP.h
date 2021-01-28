#pragma once
#include <curl/curl.h>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;


string GetJsonByHTTP(string ip, int PORT);