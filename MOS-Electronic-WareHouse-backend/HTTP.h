#pragma once
#include <boost/beast.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <string>

const static std::string MAIN_API = "127.0.0.1";
const static std::string PORT = "5000";

namespace http = boost::beast::http;
class Client {	
public:
	static std::string GetJSON(std::string ip) {

		boost::asio::io_context io;
		boost::asio::ip::tcp::resolver resolver(io);
		boost::asio::ip::tcp::socket socket(io);

		boost::asio::connect(socket, resolver.resolve(MAIN_API, PORT));

		http::request<http::string_body> req(http::verb::get, API_, 11);
	}
};

