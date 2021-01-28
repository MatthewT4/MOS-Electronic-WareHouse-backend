#include "HTTP.h"

size_t writefunc(void* ptr, size_t size, size_t nmemb, std::string* data) {
	data->append((char*)ptr, size * nmemb);
	return size * nmemb;
}

string GetJsonByHTTP(string ip, int PORT)
{
	CURL* curl;//Объект CURL

	//объект в который будет записан результат вызова функции curl_easy_perform
	CURLcode res;

	//выполняем инициализацю
	curl = curl_easy_init();
	std::string finish = "";
	if (curl) { //проверяем все ли ОК
	//дальше работаем с опциями

		curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1/scheme");
		curl_easy_setopt(curl, CURLOPT_PORT, 5000);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &finish);
		/*//указываем использовать прокси сервер
		curl_easy_setopt(curl, CURLOPT_PROXY, "ip_proxy:8080");

		//задаем опцию отображение заголовка страницы
		curl_easy_setopt(curl, CURLOPT_HEADER, 1);
		*/
		//вызываем функцию curl_easy_perform которая обработает все наши заданные опции и вернет результат, если res будет равен 0 то начит всё прошло успешно, иначе возникла какая то ошибка.
		res = curl_easy_perform(curl);
		//завершаем нашу сессию
		curl_easy_cleanup(curl);
	}
	return finish;
}