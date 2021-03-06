#include "AsyncSocket.h"

AsyncSocket::AsyncSocket()
{
	this->socketObject = INVALID_SOCKET;

	// Try to create  socket
	this->socketObject = socket(this->domain, this->type, this->protocol);
	if (this->socketObject == INVALID_SOCKET)
	{
		throw runtime_error("Can't create socket");
	}
}


AsyncSocket::AsyncSocket(SOCKET existingSocket)
{
	this->socketObject = existingSocket;
}

AsyncSocket::~AsyncSocket()
{
	return;
}

int AsyncSocket::read()
{
	char recvbuf[DEFAULT_LEN];
	int recvbuflen = DEFAULT_LEN;

	int status = recv(this->socketObject, recvbuf, recvbuflen, 0);

	if (status > 0)
	{
		std::cout << "Recievied:\t" << recvbuf << std::endl;
	}
	else
	{
		if (!status)
		{
			std::cout << "Connection Closing.." << std::endl;
		}
		else
		{
			std::cout << "Shutdown failed with error:" << WSAGetLastError() << std::endl;
		}
		closesocket(this->socketObject);
		WSACleanup();
		status = 0;
	}
	return status;
}

void AsyncSocket::setText(string str)
{
	this->toSend = str;
}

int AsyncSocket::write()
{
	const char* sendbuf = (this->toSend).c_str();
	int status = send(this->socketObject, sendbuf, (int)strlen(sendbuf), 0);
	
	// TODO: Not everything was sent

	if (status == SOCKET_ERROR) {
		std::cout << "Shutdown failed with error:" << WSAGetLastError() << std::endl;
		closesocket(this->socketObject);
		WSACleanup();
		status = 0;
	}
	return status;
}

SOCKET AsyncSocket::getSocket()
{
	return this->socketObject;
}

bool AsyncSocket::isRead()
{
	return true;
}

bool AsyncSocket::isWrite()
{
	return true;
}
