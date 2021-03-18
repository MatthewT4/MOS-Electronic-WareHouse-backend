#pragma once
#include <curl/curl.h>
#include <iostream>
#include <sstream>
#include <algorithm>

/*���������� ip � ���� ������� ������
����� �������� ������ ip - ������� � ���� �������� -1.
����� �������� ������ ���� - ������� ip � ���������� "none".
*/
void SetIpAndPort(std::string inIp, int inPort);
/*��������� JSON ����� � �������.*/
std::string GetJsonByHTTP();
/*�������� ������ �� ������ ������*/
bool SendDataToServer(std::string data);