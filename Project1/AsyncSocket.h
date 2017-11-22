#pragma once
#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define IP 0
#define DEFAULT_LEN 1024

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

using namespace std;


class AsyncSocket {
public:
	AsyncSocket();
	AsyncSocket(SOCKET existingSocket);
	~AsyncSocket();

	int read();
	int write();

	void AsyncSocket::setText(string str);
	SOCKET getSocket();
	bool isRead();
	bool isWrite();
protected:
	// buf we need to send
	string toSend;

	SOCKET socketObject;
	const static int domain = AF_INET;
	const static int type = SOCK_STREAM;
	const static int protocol = IP;
};


