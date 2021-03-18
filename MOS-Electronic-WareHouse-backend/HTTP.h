#pragma once
#include <curl/curl.h>
#include <iostream>
#include <sstream>
#include <algorithm>

/*Измененить ip и порт сервера склада
Чтобы изменить только ip - передаём в порт аргумент -1.
Чтобы изменить только порт - передаём ip с аргументом "none".
*/
void SetIpAndPort(std::string inIp, int inPort);
/*Получение JSON схемы с сервера.*/
std::string GetJsonByHTTP();
/*Отправка данных на сервер склада*/
bool SendDataToServer(std::string data);