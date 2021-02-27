#include "HTTP.h"
#include <iostream>

size_t writefunc(void* ptr, size_t size, size_t nmemb, std::string* data) {
	data->append((char*)ptr, size * nmemb);
	return size * nmemb;
}

std::string GetJsonByHTTP(std::string ip, int PORT)
{
	CURL* curl;//������ CURL

	//������ � ������� ����� ������� ��������� ������ ������� curl_easy_perform
	CURLcode res;

	//��������� ������������
	curl = curl_easy_init();
	if (!curl) { //��������� ��� �� ��
		std::cerr << "cURL ERROR curl_easy_init" << std::endl;
		exit(1);
	}
	//������ �������� � �������
	std::string finish = "";
	//curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1/scheme");
	curl_easy_setopt(curl, CURLOPT_URL, ip);
	//curl_easy_setopt(curl, CURLOPT_PORT, 5000);
	curl_easy_setopt(curl, CURLOPT_PORT, PORT);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &finish);
	/*//��������� ������������ ������ ������
	curl_easy_setopt(curl, CURLOPT_PROXY, "ip_proxy:8080");

	//������ ����� ����������� ��������� ��������
	curl_easy_setopt(curl, CURLOPT_HEADER, 1);
	*/
	//�������� ������� curl_easy_perform ������� ���������� ��� ���� �������� ����� � ������ ���������, ���� res ����� ����� 0 �� ����� �� ������ �������, ����� �������� ����� �� ������.
	res = curl_easy_perform(curl);
	//��������� ���� ������
	curl_easy_cleanup(curl);
	return finish;
}

bool SendDataToServer(std::string ip, int PORT, std::string data) {
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
		curl_easy_setopt(curl, CURLOPT_URL, ip);
		/* Now specify the POST data */
		curl_easy_setopt(curl, CURLOPT_PORT, PORT);
		//curl_easy_setopt(curl, CURLOPT_HTTPHEADER, type);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
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
		/* always cleanup */
		curl_easy_cleanup(curl);
	}
	//std::cout << finish;
	curl_global_cleanup();
	return true;
}