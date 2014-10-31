#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>

using namespace std;

class TCPClient
{
private:
	int Server_Socket;
	int Make_Command(char* Command,int _size, humans obj);

public:
	TCPClient(void);
	TCPClient(string IP, int Port);
	void Set(string IP, int Port);
	void Sending(vector<humans*> infos);
	bool isConnected;

};

