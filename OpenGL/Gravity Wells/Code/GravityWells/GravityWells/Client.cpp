#include <string>
#include "Client.h"

using std::cout;
using std::endl;
using std::string;

WSADATA Client::_wsaData;
WORD Client::_wVersionRequested = MAKEWORD( 2, 0);

Client::Client(void)
{
}

Client::~Client(void)
{
	WSACleanup();
}

string Client::Create(std::string ip, u_short portNumber){
	string reply = "";
	_inetAddr = ip;
	_portNumber = portNumber;

	//if ( WSAStartup( _wVersionRequested, &_wsaData )) {
	//	return "Socket initialisation failed";
	//}

	_peer.sin_family = AF_INET;
	_peer.sin_port = htons(_portNumber);
	_peer.sin_addr.S_un.S_addr = inet_addr(_inetAddr.c_str());

	_s = socket(AF_INET, SOCK_STREAM, 0);
	if (_s==INVALID_SOCKET) {
		reply = "Create socket failed";
	} else if (connect(_s, (sockaddr *)&_peer, sizeof(_peer))==SOCKET_ERROR) {
		reply = ToString(WSAGetLastError());
	}

	return reply;
}

string Client::SendMessage2(string message){
	unsigned int bufferLength = message.size();
	unsigned int bufferLengthBigEndian = htonl(bufferLength);
	int res = sizeof(bufferLengthBigEndian);

	char *buffer = new char[bufferLength];
	memcpy(buffer, message.c_str(), bufferLength);
	string test = ToString(bufferLengthBigEndian);
	const char *test2;
	test2 = message.c_str();

	cout << "Message to send = " << message << endl;
	string reply = "";
	if (send(_s, (char *)&bufferLengthBigEndian, sizeof(bufferLengthBigEndian), 0)==SOCKET_ERROR) {
		reply = "Send failed with " + ToString(WSAGetLastError());
	} else if (send(_s, test2, bufferLength, 0)==SOCKET_ERROR) {
		reply = "Send failed with " + ToString(WSAGetLastError());
	} //else if (recv(s, buffer, message.size(), 0)==SOCKET_ERROR) {
		//reply = "Receive failed with " + WSAGetLastError();
	//} //else {
		//cout << "Message Received" << buffer;
	//}

	delete [] buffer;

	return reply;
}