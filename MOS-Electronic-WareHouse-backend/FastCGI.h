#pragma once
#include <string>
#include "WareHouse.h"



#define THREAD_COUNT 8 
#define SOCKET_PATH ":9000" 


//хранит дескриптор открытого сокета.
static int socketId;
static std::string OldMethod = "";

void CreareFCGIConnect(string InWH);
static void* doit(void* a);
void FastMain(void);