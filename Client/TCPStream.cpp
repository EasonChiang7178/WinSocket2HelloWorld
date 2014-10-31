#include "TCPStream.h"

std::string message::getMessage() const {
	return messageToSend;
}

void testMessage::makeMessage() {
	this->messageToSend = this->blabla;
}

TCPStream::TCPStream(int sd, struct sockaddr_in* address) : socketDescriptor(sd) {
	char ip[50];
	inet_ntop(PF_INET, (struct in_addr*)&(address->sin_addr.s_addr), ip, sizeof(ip)-1);
	peerIP = ip;
	peerPort = ntohs(address->sin_port);
}

TCPStream::~TCPStream() {
	closesocket(socketDescriptor);
	WSACleanup();
}

void TCPStream::send(message& dataToSend) {
	dataToSend.makeMessage();
	if (::send(socketDescriptor, dataToSend.getMessage().c_str(), dataToSend.getMessage().size() + 1, 0) == SOCKET_ERROR)
//----
	;
//----
}

std::string TCPStream::receive() {
	const size_t messageSize = 256;
	char messageRecived[messageSize];

	if (::recv(socketDescriptor, messageRecived, messageSize, 0) == 0)
//----
	;
//----
	return std::string(messageRecived);
}