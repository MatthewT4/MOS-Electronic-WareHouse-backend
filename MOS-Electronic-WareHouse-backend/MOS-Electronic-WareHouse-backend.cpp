#include <pthread.h>
#include <sys/types.h> 
#include <stdio.h> 
#include <Windows.h> 

#include <fastcgi/fcgi_config.h>
#include <fastcgi/fcgiapp.h>
//#include <fastcgi/fcgi_stdio.h>
//#include <fastcgi/fastcgi.h>
#include <iostream>
#include <stdio.h>
#include "Position.h"
#include <stdexcept>
#include "TestAll.h"
#include "HTTP.h"
#include "JSON.h"
#include "DataBase.h"
#include "FastCGI.h"



#define THREAD_COUNT 8 
#define SOCKET_PATH ":9000" 

using namespace std;



int main()

{
    //SendDataToServer("https://dt.miet.ru/ppo_it/api/", 443, "[{\"uuid\":\"67568fb7f2c1d06d40450a478863bab1\",\"destination\":[\"A7\"]},{\"uuid\":\"bd751ff4c9739a943f40dc2ff5285cdc\",\"destination\":[\"B7\"]}]");
    //SendDataToServer("http://127.0.0.1", 5000, "[{\"uuid\":\"67568fb7f2c1d06d40450a478863bab1\",\"destination\":[\"A7\"]},{\"uuid\":\"bd751ff4c9739a943f40dc2ff5285cdc\",\"destination\":[\"B7\"]}]");
    cout << GetJsonByHTTP("http://127.0.0.1/scheme", 5000) << endl << endl;
    cout << "===========================================================================" << endl;
    cout << "Information:" << endl
        << "Server protocol: FactCGI\n"
        << "Debug:" << false << endl
        << "Configuration:" << true << endl;
    cout << "===========================================================================" << endl;
    cout << "Starting server..........." << endl;
    std::string DBName = "WareHouse.db";
    {
        WareHouse WH(DBName);
        auto& i = WH.GetDB();
        bool CreateNewTable = true;
        if (i.CheckingForValuesDB()) {
            std::cout << "The current warehouse configuration was detected." << endl
                << "Do you want to create a new configuration? "
                << "(The old warehouse configuration and data about stored items will be permanently deleted)"
                << "[Y/n]: ";
            string s;
            cin >> s;
            if (s != "Y") {
                CreateNewTable = false;
                cout << "The current warehouse configuration will be saved!" << endl;
            }
            else {
                cout << "Creating a new configuration..." << endl;
            }
        }
        if (CreateNewTable) {
            cout << "We get the data and create a new warehouse configuration..." << endl;
            if (WH.CreateDBTable(GetScheme("http://127.0.0.1/scheme", 5000))) {
                cout << "The new warehouse configuration has been successfully created!" << endl;
            }
            else {
                cout << "Error creating the warehouse configuration!" << endl;
                exit(1);
            }
        }
        /*WareHouse wh(
        GetScheme("http://127.0.0.1/scheme", 5000), DBName);
        cout << GetJsonByHTTP("http://127.0.0.1/scheme", 5000) << endl << endl;*/
        //GetScheme("http://127.0.0.1/scheme", 5000);
        //TestAll();
    }
    //FastMain();
    CreareFCGIConnect(DBName);
    TestDB();
    cout << GetJsonByHTTP("http://127.0.0.1/scheme", 5000) << endl << endl;
    GetScheme("http://127.0.0.1/scheme", 5000);
    TestAll();
    return 0;
}

//хранит дескриптор открытого сокета.
//static int socketId;
//static string OldMethod = "";

//static void* doit(void* a)
//{
//    char* buffer = new char;
//    int rc, i;
//    FCGX_Request request;
//    char* server_name;
//
//    if (FCGX_InitRequest(&request, socketId, 0) != 0)
//    {
//        //ошибка при инициализации структуры запроса 
//        printf("Can not init request\n");
//        return NULL;
//    }
//    printf("Request is inited\n");
//
//    for (;;)
//    {
//        static pthread_mutex_t accept_mutex = PTHREAD_MUTEX_INITIALIZER;
//
//        //попробовать получить новый запрос 
//        printf("Try to accept new request\n");
//        pthread_mutex_lock(&accept_mutex);
//        rc = FCGX_Accept_r(&request);
//        pthread_mutex_unlock(&accept_mutex);
//
//        if (rc < 0)
//        {
//            //ошибка при получении запроса 
//            printf("Can not accept new request\n");
//            break;
//        }
//        printf("request is accepted\n");
//
//        //получить значение переменной 
//        server_name = FCGX_GetParam("SERVER_NAME", request.envp);
//        std::cout << "Server name: " << server_name << std::endl;
//        string method = FCGX_GetParam("REQUEST_METHOD", request.envp);
//        std::cout << "Method name: " << method << std::endl;
//        string DOCUMENT_URIq = FCGX_GetParam("CONTENT_TYPE", request.envp);
//        std::cout << "CONTENT_TYPE name: " << DOCUMENT_URIq << std::endl;
//        string DOCUMENT_ROOTq = FCGX_GetParam("CONTENT_LENGTH", request.envp);
//        std::cout << "CONTENT_LENGTH name: " << DOCUMENT_ROOTq << std::endl;
//        string InURL = FCGX_GetParam("REQUEST_URI", request.envp);
//        std::cout << "REQUEST_URI name: " << InURL << std::endl;
//        FCGX_PutS("Content-type: application/json\r\n", request.out);
//        FCGX_PutS("\r\n", request.out);
//        //вывести тело ответа (например - html-код веб-страницы) 
//        /*FCGX_PutS("<html>\r\n", request.out);
//        FCGX_PutS("<head>\r\n", request.out);
//        FCGX_PutS("<title>FastCGI Hello! (multi-threaded C, fcgiapp library)</title>\r\n", request.out);
//        FCGX_PutS("</head>\r\n", request.out);
//        FCGX_PutS("<body>\r\n", request.out);*/
//        if (method == "GET") {
//            if (InURL == "/data" /*or OldMethod == "/data"*/) {
//                DataBase db("test.db");
//                string dataa = db.SelectData("SELECT * FROM WareHouse Where TypeCell = 'Midlle' AND Empty = 0 ORDER BY HeightCell");
//                cout << "dataa: " << dataa << endl;
//                FCGX_PutS(dataa.c_str(), request.out);
//            }
//        }
//        else if (method == "POST") {
//            /*auto ii = FCGI_fgetc(FCGI_stdin);
//            cerr << "FCGI_fgetc(FCGI_stdin)" << ii;**/
//            buffer = new char;
//            int FCGX_GetStr(char* str, int n, FCGX_Stream * stream);
//            FCGX_GetStr(buffer, 50, request.in);
//            string b = buffer;
//            cerr << "buffer: " << b << endl;
//        }
//        //вывести все HTTP-заголовки (каждый заголовок с новой строки) 
//        //между заголовками и телом ответа нужно вывести пустую строку 
//       /* FCGX_PutS("<h1>FastCGI Hello! 222 (multi-threaded C, fcgiapp library)</h1>\r\n", request.out);
//        FCGX_PutS("<p>Request accepted from host <i>", request.out);
//        FCGX_PutS(server_name ? server_name : "?", request.out);
//        FCGX_PutS("</i></p>\r\n", request.out);
//        FCGX_PutS("</body>\r\n", request.out);
//        FCGX_PutS("</html>\r\n", request.out);*/
//
//        //"заснуть" - имитация многопоточной среды 
//        //Sleep(6000);
//
//        //закрыть текущее соединение 
//        FCGX_Finish_r(&request);
//
//       // OldMethod = method;
//        //завершающие действия - запись статистики, логгирование ошибок и т.п. 
//    }
//
//    return NULL;
//}
//int main(void)
//{
//    int i;
//    pthread_t id[THREAD_COUNT];
//
//    //инициализация библилиотеки 
//    FCGX_Init();
//    printf("Lib is inited\n");
//
//    //открываем новый сокет 
//    socketId = FCGX_OpenSocket(SOCKET_PATH, 20);
//    if (socketId < 0)
//    {
//        //ошибка при открытии сокета 
//        return 1;
//    }
//    printf("Socket is opened\n");
//
//    //создаём рабочие потоки 
//    for (i = 0; i < THREAD_COUNT; i++)
//    {
//        pthread_create(&id[i], NULL, doit, NULL);
//    }
//
//    //ждем завершения рабочих потоков 
//    for (i = 0; i < THREAD_COUNT; i++)
//    {
//        pthread_join(id[i], NULL);
//    }
//
//    return 0;
//}
 