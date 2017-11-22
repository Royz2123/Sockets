#pragma once
#include "AsyncSocket.h"

// TODO: More than one socket for server
class ServerSocket : public AsyncSocket
{
public:
	ServerSocket(sockaddr* addr, int addr_len);
	~ServerSocket();

	SOCKET acceptConnection();

protected:
	sockaddr* addr;
};