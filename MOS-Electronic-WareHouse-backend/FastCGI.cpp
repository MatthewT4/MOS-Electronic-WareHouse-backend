#include <fastcgi/fcgi_config.h>
#include <fastcgi/fcgiapp.h>
#include "FastCGI.h"
#include <pthread.h>
#include <sys/types.h> 
#include <stdio.h> 
#include <Windows.h> 
#include <stdio.h>
#include <regex>
#include "DataBase.h"
static void* doit(void* a)
{
    int rc;
    FCGX_Request request;
    char* server_name;

    if (FCGX_InitRequest(&request, socketId, 0) != 0)
    {
        //ошибка при инициализации структуры запроса 
        printf("Can not init request\n");//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        return NULL;
    }
    printf("Request is inited\n");//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    for (;;)
    {
        static pthread_mutex_t accept_mutex = PTHREAD_MUTEX_INITIALIZER;

        //попробовать получить новый запрос 
        printf("Try to accept new request\n");//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        pthread_mutex_lock(&accept_mutex);
        rc = FCGX_Accept_r(&request);
        pthread_mutex_unlock(&accept_mutex);

        if (rc < 0)
        {
            //ошибка при получении запроса 
            printf("Can not accept new request\n");
            break;
        }
        printf("request is accepted\n");//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        //получить значение переменной 
        server_name = FCGX_GetParam("SERVER_NAME", request.envp);
        std::cout << "Server name: " << server_name << std::endl;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        std::string method = FCGX_GetParam("REQUEST_METHOD", request.envp);
        std::cout << "Method name: " << method << std::endl;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        std::string DOCUMENT_URIq = FCGX_GetParam("CONTENT_TYPE", request.envp);
        std::cout << "CONTENT_TYPE name: " << DOCUMENT_URIq << std::endl;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        std::string CL = FCGX_GetParam("CONTENT_LENGTH", request.envp);
        std::cout << "CONTENT_LENGTH name: " << CL << std::endl; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        std::string InURL = FCGX_GetParam("REQUEST_URI", request.envp);
        std::cout << "REQUEST_URI name: " << InURL << std::endl; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        FCGX_PutS("Content-type: application/json\r\n", request.out);
        FCGX_PutS("\r\n", request.out);
        //вывести тело ответа (например - html-код веб-страницы) 
        /*FCGX_PutS("<html>\r\n", request.out);
        FCGX_PutS("<head>\r\n", request.out);
        FCGX_PutS("<title>FastCGI Hello! (multi-threaded C, fcgiapp library)</title>\r\n", request.out);
        FCGX_PutS("</head>\r\n", request.out);
        FCGX_PutS("<body>\r\n", request.out);*/
        if (method == "GET") {
            if (InURL == "/data" /*or OldMethod == "/data"*/) {
                DataBase db("test.db");
                std::string dataa = db.SelectData("SELECT * FROM WareHouse"); // Where TypeCell = 'Midlle' AND Empty = 0 ORDER BY HeightCell");
                FCGX_PutS(dataa.c_str(), request.out);
            }
        }
        else if (method == "POST") {
            char* buffer = new char;
            /*auto ii = FCGI_fgetc(FCGI_stdin);
            cerr << "FCGI_fgetc(FCGI_stdin)" << ii;**/
            //delete buffer;
            SetConsoleCP(1251);
            SetConsoleOutputCP(1251);
            //int FCGX_GetStr(char* str, int n, FCGX_Stream * stream);
            FCGX_GetStr(buffer, int(FCGX_GetParam("CONTENT_LENGTH", request.envp)), request.in);
            std::string buf = buffer;
            //buf = buf[int(FCGX_GetParam("CONTENT_LENGTH", request.envp))];
            //std::string b = buffer; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            std::cerr << "buffer: " << buffer << std::endl;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            std::cerr << "stdbuffer: " << buf << std::endl;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            //std::cerr << "b: " << b << std::endl; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            buffer = {};
            delete buffer;
        }
        //вывести все HTTP-заголовки (каждый заголовок с новой строки) 
        //между заголовками и телом ответа нужно вывести пустую строку 
       /* FCGX_PutS("<h1>FastCGI Hello! 222 (multi-threaded C, fcgiapp library)</h1>\r\n", request.out);
        FCGX_PutS("<p>Request accepted from host <i>", request.out);
        FCGX_PutS(server_name ? server_name : "?", request.out);
        FCGX_PutS("</i></p>\r\n", request.out);
        FCGX_PutS("</body>\r\n", request.out);
        FCGX_PutS("</html>\r\n", request.out);*/

        //"заснуть" - имитация многопоточной среды 
        //Sleep(6000);

        //закрыть текущее соединение 
        FCGX_Finish_r(&request);

        // OldMethod = method;
         //завершающие действия - запись статистики, логгирование ошибок и т.п. 
        //delete buffer;
    }
    //delete buffer;
    return NULL;
}
void FastMain(void)
{
    int i;
    pthread_t id[THREAD_COUNT];

    //инициализация библилиотеки 
    FCGX_Init();
    printf("Lib is inited\n"); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    //открываем новый сокет 
    socketId = FCGX_OpenSocket(SOCKET_PATH, 20);
    if (socketId < 0)
    {
        //ошибка при открытии сокета 
        exit(1);      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }
    printf("Socket is opened\n"); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    //создаём рабочие потоки 
    for (i = 0; i < THREAD_COUNT; i++)
    {
        pthread_create(&id[i], NULL, doit, NULL);
    }

    //ждем завершения рабочих потоков 
    for (i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(id[i], NULL);
    }

}