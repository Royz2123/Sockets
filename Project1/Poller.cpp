#include "Poller.h"


Selecter::Selecter()
{
	return;
}

Selecter::Selecter(AsyncSocket* sock)
{
	addPollable(sock);
}

void Selecter::addPollable(AsyncSocket* sock)
{
	// add this socket to all the sockets
	this->sockets.push_back(sock);

	// add to read/write lists
	if (sock->isRead())
	{
		FD_SET(sock->getSocket(), &(this->readSet));
	}
	if (sock->isWrite())
	{
		FD_SET(sock->getSocket(), &(this->writeSet));
	}
}

void Selecter::poll()
{
	// call select function
	select(
		0,
		&(this->readSet),
		&(this->writeSet),
		NULL,
		NULL
	);

	for (int i = 0; i < this->sockets.size(); i++)
	{
		AsyncSocket* currSock = this->sockets[i];

		// handle read
		if (FD_ISSET(currSock, &(this->readSet)))
		{
			this->readers.push_back(currSock);
		}

		// handle write
		if (FD_ISSET(currSock, &(this->writeSet)))
		{
			this->writers.push_back(currSock);
		}
	}
}

vector<AsyncSocket*> Selecter::getReaders()
{
	return this->readers;
}


vector<AsyncSocket*> Selecter::getWriters()
{
	return this->writers;
}


