#pragma once
#include <curl/curl.h>
#include <iostream>
#include <sstream>
#include <algorithm>


/*Получение JSON схемы с сервера.*/
std::string GetJsonByHTTP(std::string ip, int PORT);