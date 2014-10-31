#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

using namespace std;

class message {
public:
	std::string getMessage() const;

protected:
	std::string messageToSend;
	virtual void makeMessage() = 0;

	friend class TCPStream;
};

class testMessage : public message {
public:
	std::string blabla;

protected:
	virtual void makeMessage();
};

class TCPStream {
	int		socketDescriptor;
	string	peerIP;
	int		peerPort;

public:
	~TCPStream();

	void		send(message& dataToSend);
	std::string receive();
 
	string getPeerIP()	{ return peerIP; }
	int getPeerPort()	{ return peerPort; }

private:
	TCPStream();
	TCPStream(int socketdescriptor, SOCKADDR_IN* address);
	TCPStream(const TCPStream& stream);

	friend class TCPAcceptor;
	friend class TCPConnector;
};

