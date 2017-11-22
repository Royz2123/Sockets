#pragma once
#include "AsyncSocket.h"


// TODO: More than one socket for server
class ClientSocket : public AsyncSocket
{
public:
	ClientSocket(const sockaddr* addr, int addr_len);
	ClientSocket(SOCKET sock);
	~ClientSocket();

protected:
	const sockaddr* addr;

};