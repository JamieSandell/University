#pragma once
#include <iostream>
#include <sstream>
#include <winsock2.h>

using std::string;

class Client
{
public:
	Client(void);
	~Client(void);

	string Create(string ip, u_short portNumber);
	string SendMessage2(string message);

	template <class T>
	inline std::string ToString (const T& t)
	{
		std::stringstream ss;
		ss << t;
		return ss.str();
	}

private:
	static WORD _wVersionRequested;
	static WSADATA _wsaData;
	sockaddr_in _peer;
	string _inetAddr;
	u_short _portNumber;
	SOCKET _s;
};
