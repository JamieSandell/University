#include "Server.h"

WORD Server::_wVersionRequested = MAKEWORD( 2, 0 );
WSADATA Server::_wsaData;

using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::vector;

Server::Server(void)
{
	_acceptableIPs.push_back("127.0.0.1");
}

Server::~Server(void)
{
}

bool Server::AcceptConnection(int peer){
	u_long fionbio = 1;
	ioctlsocket(_peer[peer].transferSocket, FIONBIO, &fionbio);

	int peerSize = sizeof(_peerAddr);
	_peer[peer].transferSocket = accept(_listeningSocket, (sockaddr *)&_peerAddr, &peerSize);
	string peerIP = inet_ntoa(_peerAddr.sin_addr);
	if (!IsIPAcceptable(peerIP))
	{
		cout << "IP: " << peerIP << " is not an acceptable IP, connection closed." << endl;
		return false;
	}
	if (_peer[peer].transferSocket == INVALID_SOCKET)
	{
		cout << "Accept failed: " << ToString(WSAGetLastError()) << endl;
		return false;
	}
	_peer[peer].connected = true;
	cout << "Connection accepted, peer " << peer+1 << " connected from IP Address " << peerIP << "." << endl;

	int timeout = 25;
	setsockopt(_peer[peer].transferSocket, SOL_SOCKET, SO_SNDTIMEO, (char *) &timeout, sizeof(timeout));

	_event[peer+1] = WSACreateEvent();
	WSAEventSelect(_peer[peer].transferSocket, _event[peer+1], FD_READ | FD_CLOSE);
	return true;
}
void Server::CreateThread(void){
	unsigned threadId=0;
	_hThread = (HANDLE)_beginthreadex(
		NULL,		// no security attributes (child cannot inherited handle)
		1024*1024,	// 1MB stack size
		ThreadFunc,	// code to run on new thread
		this,		// pointer to host application class
		0,			// run immediately (could create suspended)
		&threadId	// OUT: returns thread ID
	);
}

int Server::FindPeer(int peerID)const{
	for (int i = 0; i < 3; i++)
	{
		if (_peer[i].id==peerID)
			return i;
		else{
			return 0;
			std::cout << "Could not find the Peer based on the ID: " << peerID << "." << std::endl;
		}
	}
}
bool Server::IsIPAcceptable(const string &ip)const{
	for (vector<string>::const_iterator it = _acceptableIPs.begin(); it != _acceptableIPs.end(); ++it)
	{
		if (ip == *it)
			return true;
	}
	return false;
}
//bool IsLocalIP(const std::string &ip){
//	WORD wVersionRequested = MAKEWORD( 2, 0 );
//	WSADATA wsaData;
//	WSAStartup( wVersionRequested, &wsaData );
//
//	char name[255];
//	PHOSTENT hostinfo;
//	string ip2;
//
//	if (gethostname(name, sizeof(name)) == 0)//Succeeded
//	{
//		cout << "Host name: " << name << endl;
//		if ((hostinfo = gethostbyname(name)) != NULL)
//		{
//			int nCount = 0;
//			while (hostinfo->h_addr_list[nCount])
//			{
//				ip2 = inet_ntoa(*(struct in_addr *)hostinfo->h_addr_list[nCount]);
//				if (ip2 == ip) // found a match so this is ip of the machine
//					return true;
//			}
//		}
//	}
//	return false;
//}
bool Server::IsPeerAlive(int peer)const{
	string ping = "PING";
	if (send(_peer[peer].transferSocket, ping.c_str(), ping.size(), 0)==SOCKET_ERROR){
		int err = WSAGetLastError();
		if (err==WSAETIMEDOUT)
		{
			return false;
		}
		return false;
	}
	return true;
}
bool Server::IsPeerConnected(int peerID)const{
	int peer = FindPeer(peerID);
	if (IsPeerAlive(peer))
		return true;
	return false;
}
void Server::InitialiseServer(void){
	if ( WSAStartup( _wVersionRequested, &_wsaData )) {
		cout << "Socket initialisation failed";
	}
}
bool Server::ReceiveMessage(int peer){
	unsigned int packetSize = 0, prefixBytesRead = 0, bytesRead = 0;
	//Read the length of the packet
	const int prefixSize = 4;

	bytesRead = recv(_peer[peer].transferSocket, (char *)&packetSize, prefixSize, 0);
	packetSize = ntohl(packetSize);
	char *packetBuffer = new char[packetSize];

	//Read in the packet
	unsigned int packetBytesRead = 0;
	do 
	{
		bytesRead = recv(_peer[peer].transferSocket, packetBuffer + packetBytesRead, packetSize - packetBytesRead, 0);
		if (bytesRead <= packetSize)
		{
			if (bytesRead >= 1)
			{
				packetBytesRead += bytesRead;
			}
			else{
				if (bytesRead == SOCKET_ERROR)
				{
					cout << "Receive failed from peer " << peer+1 << "." << endl << ToString(WSAGetLastError()) << endl;
				}
				return false;
			}
		}
	} while (packetBytesRead < packetSize);
	//trim any excess
	string bufferString = ToString(packetBuffer);
	bufferString.resize(packetSize);
	char identifier;

	stringstream ss(bufferString);
	ss >> identifier; //extract the identifier
	//for (unsigned int i = 0; i < 3; i++) //extract the floats
	//{
	//	ss >> position[i];
	//}
	cout << "Identifier " << " " << identifier << endl;
	if (identifier=='I')//Set the Peer ID
	{
		ss >> _peer[peer].id;
		cout << "ID of Peer " << peer+1 << " set to: " << _peer[peer].id << "." << endl;
	}
	else if (identifier=='G') //Peer ID + GravityWell Position + GravityWell Size
	{
		int id;
		ss >> id;
		for (int i = 0; i < 3; i++)
		{
			if (id==_peer[i].id) //found a matching peer that is stored
			{
				cout << "Peer ID: " << id << " accepted. Reading Gravity Well information..." << endl;
				//for (int j = 0; j < 3; j++)
				//{
					Vector3f position;
					float x,y,z;
					ss >> x; ss >> y; ss >> z;
					position.Assign(x,y,z);
					_peer[i].gravityWell.SetPosition(position);
				//}
				cout << "Gravity Well position set to: X=" << _peer[i].gravityWell.GetPosition().x()
					<< " Y=" << _peer[i].gravityWell.GetPosition().y() << " Z="<< _peer[i].gravityWell.GetPosition().z() << endl;
				float r;
				ss >> r;
				_peer[i].gravityWell.SetWidth(r);
				cout << "Gravity Well size set to: " << _peer[i].gravityWell.GetRadius() << endl;
				break; //No need to loop round anymore
			}
		}
	}

	return true;
}

int Server::Run(void){
	WaitForConnection(_portNumber);
	WSANETWORKEVENTS NetworkEvents;
	while (!_terminate)
	{
		int n = WSAWaitForMultipleEvents(4, _event, FALSE, INFINITE, FALSE);
		//if (n>-1)
		//{
			WSAEnumNetworkEvents(_listeningSocket, _event[0], &NetworkEvents);
			if (NetworkEvents.lNetworkEvents & FD_ACCEPT)
			{
				for (int i = 0; i < 3; i++)
				{
					if (!_peer[i].connected)
					{
						AcceptConnection(i);
						break;
					}
				}			
			}	

			for (int i = 0; i < 3; i++)
			{
				if (!_peer[i].connected)
					continue;
				WSAEnumNetworkEvents(_peer[i].transferSocket, _event[i+1], &NetworkEvents);
				if (NetworkEvents.lNetworkEvents & FD_READ)
				{
					ReceiveMessage(i);
				}
				else if (NetworkEvents.lNetworkEvents & FD_CLOSE)
				{
					_peer[i].connected = false;
					cout << "Peer " << i+1 << " disconnected" << endl;
				}
				else if (_timer.HasTimePassed())
				{
					if (!IsPeerAlive(i)){
						cout << "Peer " << i+1 << " did not respond, terminating connection with the peer." << endl;
						_peer[i].connected = false;
					}
				}
			}
		//}
		Sleep(100);//Need the sleep or cpu cycles is eaten up, WSAWaitForMultipleEvents should be in a wait state but keeps returning -1
			// even though no event is fired and the timeout is set to INFINITE
	}
	return 0;
}

void Server::Start(u_short portNumber){
	_portNumber = portNumber;
	_terminate = false;
	_peer[0].connected = _peer[1].connected = _peer[2].connected = false;
	CreateThread();
}

bool Server::WaitForConnection(int port){
	sockaddr_in peer;
	peer.sin_family = AF_INET;
	peer.sin_port = htons(port);
	peer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	// Create listening socket
	_listeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	u_long fionbio = 1;
	ioctlsocket(_listeningSocket, FIONBIO, &fionbio);	

	_event[0] = WSACreateEvent();
	WSAEventSelect(_listeningSocket, _event[0], FD_ACCEPT);

	if (_listeningSocket == INVALID_SOCKET)
	{
		cout << "Failed to create socket" << endl;
		return false;
	}	
	if ( bind(_listeningSocket, (sockaddr *)&peer, sizeof(peer)) == SOCKET_ERROR)
	{
		cout << "Failed to bind socket" << endl;
		return false;
	}

	if (listen(_listeningSocket, 1) == SOCKET_ERROR)
	{
		cout << "failed to listen" << endl;
		return false;
	}
	cout << "listening..." << endl;
	return true;
}

void Server::WaitForTermination(void){
	// wait for it to stop
	WaitForSingleObject(_hThread, INFINITE);
	// close thread handle
	CloseHandle(_hThread);
	_hThread = 0;
}