#ifndef TCPACCEPTOR_H
#define TCPACCEPTOR_H

#include <winsock2.h>
#include <ws2tcpip.h>

#include "TCPStream"

class TCPAcceptor {

	int		m_lsd;
	string	m_address;
	int		m_port;
	bool	m_listening;

public:
	TCPAcceptor(int port, const char* address="");
	~TCPAcceptor();
 
	int			start();
	TCPStream*	accept();

private:
	TCPAcceptor() {}
};

#endif //TCPACCPTOR_H