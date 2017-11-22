#include "Server.h"

ServerSocket::ServerSocket(sockaddr* addr, int addr_len) : addr(addr)
{	
	// Bind to the address
	int status = bind(this->socketObject, addr, addr_len);

	if (status == SOCKET_ERROR) {
		closesocket(this->socketObject);
		WSACleanup();
		throw runtime_error("SOCKET_ERROR: Bind failed");
	}

	// Listen for connections
	status = listen(this->socketObject, SOMAXCONN);
	
	if (status == SOCKET_ERROR) {
		closesocket(this->socketObject);
		WSACleanup();
		throw runtime_error("SOCKET_ERROR: Listen failed");
	}
}

SOCKET ServerSocket::acceptConnection()
{
	SOCKET acceptedSocket = INVALID_SOCKET;
	
	// accept a connection
	acceptedSocket = accept(this->socketObject, this->addr, NULL);
	if (acceptedSocket == INVALID_SOCKET) {
		closesocket(this->socketObject);
		WSACleanup();
		throw runtime_error("SOCKET_ERROR: Accept failed");
	}
	return acceptedSocket;
}

ServerSocket::~ServerSocket()
{
	return;
}