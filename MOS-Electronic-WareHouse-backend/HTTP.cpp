#include "HTTP.h"
#include <iostream>
#include <nlohmann/json.hpp>

static std::string IpServer = "http://127.0.0.1";
static int portServer = 5000;
size_t writefunc(void* ptr, size_t size, size_t nmemb, std::string* data) {
	data->append((char*)ptr, size * nmemb);
	return size * nmemb;
}
/*Измененить ip и порт сервера склада
Чтобы изменить только ip - передаём в порт аргумент -1.
Чтобы изменить только порт - передаём ip с аргументом "none".
*/
void SetIpAndPort(std::string inIp, int inPort) {
	if (inIp != "none") {
		IpServer = inIp;
	}
	if (inPort != -1) {
		portServer = inPort;
	}
}

std::string GetJsonByHTTP() {
	CURL* curl;//Объект CURL

	//объект в который будет записан результат вызова функции curl_easy_perform
	CURLcode res;
	std::cout << IpServer << " " << portServer << std::endl;
	//выполняем инициализацю
	curl = curl_easy_init();
	if (!curl) { //проверяем все ли ОК
		std::cerr << "cURL ERROR curl_easy_init" << std::endl;
		exit(1);
	}
	//дальше работаем с опциями
	std::string finish = "";
	//curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1/scheme");
	//curl_easy_setopt(curl, CURLOPT_PORT, 5000);
	std::string vr = IpServer + "/scheme";
	const char* ip = vr.c_str();
	curl_easy_setopt(curl, CURLOPT_URL, ip);
	curl_easy_setopt(curl, CURLOPT_PORT, portServer);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &finish);
	/*//указываем использовать прокси сервер
	curl_easy_setopt(curl, CURLOPT_PROXY, "ip_proxy:8080");

	//задаем опцию отображение заголовка страницы
	curl_easy_setopt(curl, CURLOPT_HEADER, 1);
	*/
	//вызываем функцию curl_easy_perform которая обработает все наши заданные опции и вернет результат, если res будет равен 0 то начит всё прошло успешно, иначе возникла какая то ошибка.
	res = curl_easy_perform(curl);
	if (res != CURLE_OK) {
		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		return "Error func";
	}
	//завершаем нашу сессию
	curl_easy_cleanup(curl);
	return finish;
}
/*POST method
	header: JSON*/
bool SendDataToServer(std::string data) {
	CURL* curl;
	CURLcode res;
	std::string finish = "";
	/* In windows, this will init the winsock stuff */
	curl_global_init(CURL_GLOBAL_ALL);

	/* get a curl handle */
	curl = curl_easy_init();
	if (curl) {
		/* First set the URL that is about to receive our POST. This URL can
		   just as well be a https:// URL if that is what should receive the
		   data. */
		std::string type = "Content-Type:application/json";
		//curl_easy_setopt(curl, CURLOPT_URL, ip);
		/* Now specify the POST data */
		//curl_easy_setopt(curl, CURLOPT_PORT, PORT);
		/*curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1");
		curl_easy_setopt(curl, CURLOPT_PORT, 5000);*/
		const char* ip = IpServer.c_str();
		curl_easy_setopt(curl, CURLOPT_URL, ip);
		curl_easy_setopt(curl, CURLOPT_PORT, portServer);
		//curl_easy_setopt(curl, CURLOPT_HTTPHEADER, type);
		//curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
		std::string ddatta = "[{\"uuid\":\"67768fb7f2c1d06d40450a478863bab1\",\"destination\":[\"C1\", \"C2\", \"D1\", \"D2\"]}]";
		std::cout << "data: " << data << std::endl << std::endl;
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
		//curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &finish);
		struct curl_slist* header = NULL;
		header = curl_slist_append(header, "Content-Type:application/json");
		/* Perform the request, res will get the return code */
		res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
		res = curl_easy_perform(curl);
		std::cout << "Ok!" << std::endl;
		/* Check for errors */
		if (res != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			return false;
		}
		curl_easy_cleanup(curl);
		curl_global_cleanup();
		std::cout << "finish: " << finish << std::endl << std::endl;
		try {
			nlohmann::json jres = nlohmann::json::parse(finish);
			if (jres["status"] != "ok") {
				return false;
			}
		}
		catch (std::exception& ex) {
			std::cerr << "[HTTP/SendDataToServer](json parsing exception)" << std::endl;
			return false;
		}
		return true;
	}
	//std::cout << "Finish: " << finish << std::endl;
	//std::cout << finish;
	curl_global_cleanup();
	return false;
}
bool DeletePositionHTTP(std::string inData) {
	CURL* curl;//Объект CURL

	//объект в который будет записан результат вызова функции curl_easy_perform
	CURLcode res;
	std::cout << IpServer << " " << portServer << std::endl;
	//выполняем инициализацю
	curl = curl_easy_init();
	if (!curl) { //проверяем все ли ОК
		std::cerr << "cURL ERROR curl_easy_init" << std::endl;
		exit(1);
	}
	//дальше работаем с опциями
	std::string finish = "";
	//curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1/scheme");
	//curl_easy_setopt(curl, CURLOPT_PORT, 5000);
	std::string vr = IpServer + "/position";
	curl_easy_setopt(curl, CURLOPT_URL, vr.c_str());
	curl_easy_setopt(curl, CURLOPT_PORT, portServer);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, inData.c_str());
	curl_easy_setopt(curl, CURLOPT_POST, 0); // выключаем POST
	curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
	//curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &finish);
	struct curl_slist* header = NULL;
	header = curl_slist_append(header, "Content-Type:application/json");
	/* Perform the request, res will get the return code */
	res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
	
	/*//указываем использовать прокси сервер
	curl_easy_setopt(curl, CURLOPT_PROXY, "ip_proxy:8080");

	//задаем опцию отображение заголовка страницы
	curl_easy_setopt(curl, CURLOPT_HEADER, 1);
	*/
	//вызываем функцию curl_easy_perform которая обработает все наши заданные опции и вернет результат, если res будет равен 0 то начит всё прошло успешно, иначе возникла какая то ошибка.
	res = curl_easy_perform(curl);
	if (res != CURLE_OK) {
		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		return false;
	}
	std::cout << "del Finsh: " << finish << std::endl << std::endl;
	//завершаем нашу сессию
	curl_easy_cleanup(curl);
	std::cout << "Del Ok!" << std::endl;
	return true;
}