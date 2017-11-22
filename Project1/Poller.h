#include <vector>

#include "Client.h"
#include "Server.h"


class Selecter 
{
public:
	Selecter();
	Selecter(AsyncSocket* sock);

	void addPollable();
	void addPollable(AsyncSocket * sock);
	void poll();

	vector<AsyncSocket*> getReaders();
	vector<AsyncSocket*> getWriters();

protected:
	// ready writers and readers
	vector<AsyncSocket*> readers;
	vector<AsyncSocket*> writers;

	// all sockets
	vector<AsyncSocket*> sockets;
	FD_SET writeSet;
	FD_SET readSet;
};