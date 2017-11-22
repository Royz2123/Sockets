#include "Server.h"
#include "Client.h"

#define CLIENT_MODE 0
#define SERVER_MODE 1

#define DEFAULT_BIND_ADDRESS "0.0.0.0"
#define DEFAULT_CONNECT_ADDRESS "127.0.0.1"


void defineUsage()
{
	std::cout << "Usage:\t\t NetworkUtils.exe   mode   [address]" << std::endl;
	std::cout << "Mode:\t\t" << SERVER_MODE << " - Server, " << CLIENT_MODE << " - Client" << std::endl;
	std::cout << "Address:\t ip_address:port. Example: 127.0.0.1:8080" << std::endl;
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
	inet_pton(AF_INET, "192.0.2.33", &(address));
	int addr_len = str_addr.length();

	// Client Mode
	if (mode == CLIENT_MODE)
	{
		// Create a client socket and send "hello"
		ClientSocket sock = ClientSocket(&address, addr_len);
		sock.write("hello");
	}
	else if (mode == SERVER_MODE)
	{
		// Create a server socket and recv something
		// TODO: Asynchronous
		ServerSocket sock = ServerSocket(&address, addr_len);
		ClientSocket acceptedSocket = ClientSocket(sock.acceptConnection());

		// Quick convo
		acceptedSocket.read();
		acceptedSocket.write("hi");
	}
	else
	{
		std::cout << "Invalid mode chosen" << std::endl;
		defineUsage();
		return 1;
	}
	return 0;
}