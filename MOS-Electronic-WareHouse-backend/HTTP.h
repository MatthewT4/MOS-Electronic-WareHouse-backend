#pragma once
#include <curl/curl.h>
#include <iostream>
#include <sstream>
#include <algorithm>


/*��������� JSON ����� � �������.*/
std::string GetJsonByHTTP(std::string ip, int PORT);
/*�������� ������ �� ������ ������*/
bool SendDataToServer(std::string ip, int PORT, std::string data);