#pragma once
#include <sstream>
#include <iostream>
#include <process.h>
#include <vector>
#include <winsock2.h>
#include "GravityWell.h"
#include "Timer.h"
#include "Vector3f.h"

#pragma comment(lib, "Ws2_32.lib")

struct Connection
{
	SOCKET transferSocket;
	bool connected;
	int id;
	GravityWell gravityWell;
};

class Server
{
public:
	Server(void);
	~Server(void);

	inline void AddAcceptableIP(const std::string &ip){_acceptableIPs.push_back(ip);};
	int FindPeer(int peerID)const;//Find a stored peer based on the ID
	inline float GetGravityWellSize(int peerID)const{return _peer[FindPeer(peerID)].gravityWell.GetRadius();};
	void InitialiseServer(void);
	bool IsPeerConnected(int peerID)const;
	static bool IsLocalIP(const std::string &ip){
		WORD wVersionRequested = MAKEWORD( 2, 0 );
		WSADATA wsaData;
		WSAStartup( wVersionRequested, &wsaData );

		char name[255];
		PHOSTENT hostinfo;
		std::string ip2;

		if (gethostname(name, sizeof(name)) == 0)//Succeeded
		{
			std::cout << "Host name: " << name << std::endl;
			if ((hostinfo = gethostbyname(name)) != NULL)
			{
				int nCount = 0;
				while (hostinfo->h_addr_list[nCount])
				{
					ip2 = inet_ntoa(*(struct in_addr *)hostinfo->h_addr_list[nCount]);
					if (ip2 == ip){ // found a match so this is ip of the machine
						WSACleanup();
						return true;
					}
					else
						break;
				}
			}
		}
		WSACleanup();
		return false;
	};
	inline void UninitialiseServer(void){WSACleanup();};

	template <class T>
	inline std::string ToString (const T& t)
	{
		std::stringstream ss;
		ss << t;
		return ss.str();
	}

	inline void Resume(HANDLE hThread){ResumeThread(hThread);};
	void Start(u_short portNumber);

private:
	bool AcceptConnection(int peer);
	void CreateThread(void);
	bool IsIPAcceptable(const std::string &ip)const;
	bool IsPeerAlive(int peer)const;
	bool ReceiveMessage(int peer);
	int Run();
	static unsigned __stdcall ThreadFunc(void *param) {
		if (param)
			return ((Server*)param)->Run();
		return -1;  // Return error
	}
	bool WaitForConnection(int port);
	void WaitForTermination(void);

private:
	static WORD _wVersionRequested;
	static WSADATA _wsaData;

	std::vector<std::string> _acceptableIPs;
	WSAEVENT _event[4];
	HANDLE _hThread;
	SOCKET _listeningSocket;
	sockaddr_in _peerAddr;
	Connection _peer[3]; //4 peers but don't include yourself
	u_short _portNumber;
	bool _terminate;
	Timer _timer;

};