#ifndef TCPCONNECTOR_H
#define TCPCONNECTOR_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#include "TCPStream.h"

class TCPConnector {
public:
	TCPStream& Connect(const int port = 1000, const std::string server = "localhost");

private:
	int interpretHostName(const std::string hostName, IN_ADDR* address_info);
};

#endif //TCPCONNECTOR_H