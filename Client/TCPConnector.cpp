#include "TCPConnector.h"

TCPStream& TCPConnector::Connect(const int port, const std::string server) {
	/* Initialize Winsock */
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
//---
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
	}
//---

	/* Interpret DNS host name to IP address */
	SOCKADDR_IN serverAddress;
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);

	if (interpretHostName(server, &serverAddress.sin_addr) != 0)
		inet_pton(AF_INET, server.c_str(), &(serverAddress.sin_addr));

	SOCKET socketDescriptor = INVALID_SOCKET;
	socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
//---
	if (socketDescriptor== INVALID_SOCKET) {
	}
//---

	if (::connect(socketDescriptor, (SOCKADDR*) &serverAddress, sizeof(serverAddress)) != 0) {
//---
//---
	}
	return TCPStream(socketDescriptor, &serverAddress);
}

int TCPConnector::interpretHostName(const std::string hostName, IN_ADDR* address_info) {
	ADDRINFOA* res = NULL;
 
	int result = getaddrinfo(hostName.c_str(), NULL, NULL, &res);
	if (result == 0) {
		memcpy(address_info, &((SOCKADDR_IN*) res->ai_addr)->sin_addr, sizeof(struct in_addr));
		freeaddrinfo(res);
	}
	return result;
}