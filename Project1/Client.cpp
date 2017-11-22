#include "Client.h"

ClientSocket::ClientSocket(const sockaddr* addr, int addr_len) : addr(addr)
{
	if (connect(this->socketObject, addr, addr_len) == SOCKET_ERROR)
	{
		closesocket(this->socketObject);
		throw runtime_error("SOCKET_ERROR: Connection Refused");
	}
}

ClientSocket::ClientSocket(SOCKET sock) : AsyncSocket(sock)
{
	return;
}

ClientSocket::~ClientSocket()
{
	return;
}