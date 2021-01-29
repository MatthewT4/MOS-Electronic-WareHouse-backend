#pragma once
#include <curl/curl.h>
#include <iostream>
#include <sstream>
#include <algorithm>



std::string GetJsonByHTTP(std::string ip, int PORT);