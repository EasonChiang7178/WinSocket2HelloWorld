#include "TCPStream.h"

TCPStream::TCPStream(int sd, struct sockaddr_in* address) : socketDescriptor(sd) {
	char ip[50];
	inet_ntop(PF_INET, (struct in_addr*)&(address->sin_addr.s_addr), ip, sizeof(ip)-1);
	peerIP = ip;
	peerPort = ntohs(address->sin_port);
}

TCPStream::~TCPStream() {
	closesocket(socketDescriptor);
}