#include <typeinfo>

#include "Server.h"
#include "Client.h"
#include "Poller.h"

#define CLIENT_MODE 0
#define SERVER_MODE 1

#define DEFAULT_BIND_ADDRESS "0.0.0.0"
#define DEFAULT_CONNECT_ADDRESS "127.0.0.1"


void defineUsage()
{
	std::cout << "Usage:\t\tNetworkUtils.exe   mode   [address]" << std::endl;
	std::cout << "Mode:\t\t" << SERVER_MODE << " - Server, " << CLIENT_MODE << " - Client" << std::endl;
	std::cout << "Address:\tIP_address:port. Example: 127.0.0.1:8080" << std::endl;
	getchar();
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		defineUsage();
		return 1;
	}

	int mode = atoi(argv[1]);
	
	// Create address struct and len
	string str_addr = (mode == CLIENT_MODE) ? DEFAULT_CONNECT_ADDRESS : DEFAULT_BIND_ADDRESS;
	if (argc >= 2) {
		str_addr = argv[2];
	}
	struct sockaddr address;
	inet_pton(AF_INET, str_addr.c_str(), &(address));
	int addr_len = str_addr.length();

	// Client Mode
	if (mode == CLIENT_MODE)
	{
		// Create a client socket and send "hello"
		ClientSocket sock = ClientSocket(&address, addr_len);
		sock.setText("hello");
		sock.write();
	}
	else if (mode == SERVER_MODE)
	{
		// Create a server socket and recv something
		ServerSocket sock = ServerSocket(&address, addr_len);

		cout << "hello";

		// Create an async poller
		Selecter poller = Selecter((AsyncSocket*)&sock);

		while (true)
		{
			poller.poll();

			// handle readers
			for (AsyncSocket* currSock : poller.getReaders())
			{
				// handle listener sockets
				if (typeid(*currSock) == typeid(ServerSocket))
				{
					SOCKET sock = ((ServerSocket*)currSock)->acceptConnection();
					poller.addPollable((AsyncSocket*)&ClientSocket(sock));
				}
				// handle all other sockets read
				else
				{
					currSock->read();
				}
			}

			// handle writers
			for (AsyncSocket* currSock : poller.getWriters())
			{	
				currSock->write();	
			}
		}
	}
	else
	{
		std::cout << "Invalid mode chosen" << std::endl;
		defineUsage();
		return 1;
	}
	return 0;
}