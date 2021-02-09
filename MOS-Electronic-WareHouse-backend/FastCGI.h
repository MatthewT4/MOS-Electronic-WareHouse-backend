#pragma once
#include <string>



#define THREAD_COUNT 8 
#define SOCKET_PATH ":9000" 


//хранит дескриптор открытого сокета.
static int socketId;
static std::string OldMethod = "";

static void* doit(void* a);
void FastMain(void);