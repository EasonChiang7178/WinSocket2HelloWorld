#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

using namespace std;

class TCPStream {
	int		socketDescriptor;
	string	peerIP;
	int		peerPort;

public:
	~TCPStream();

	size_t send(char* buffer, size_t len);
	size_t receive(char* buffer, size_t len);
 
	string getPeerIP()	{ return peerIP; }
	int getPeerPort()	{ return peerPort; }

private:
	TCPStream();
	TCPStream(int socketdescriptor, SOCKADDR_IN* address);
	TCPStream(const TCPStream& stream);

	friend class TCPAcceptor;
	friend class TCPConnector;
};