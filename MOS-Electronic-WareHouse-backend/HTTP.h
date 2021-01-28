#include <curl/curl.h>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

size_t writefunc(void* ptr, size_t size, size_t nmemb, std::string* data) {
	data->append((char*)ptr, size * nmemb);
	return size * nmemb;
}

string GetHTTP(const string& ip, const int& PORT)
{
	CURL* curl;//������ CURL

	//������ � ������� ����� ������� ��������� ������ ������� curl_easy_perform
	CURLcode res;

	//��������� ������������
	curl = curl_easy_init();
	std::string finish;
	if (curl) { //��������� ��� �� ��
	//������ �������� � �������

	//������ ����� �������� �������� http://nullflow.blogspot.com
		curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1/scheme");
		curl_easy_setopt(curl, CURLOPT_PORT, 5000);
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
	}
	cout << finish;
	return 0;
}