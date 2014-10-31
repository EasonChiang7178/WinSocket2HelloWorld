#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <winsock.h>
#include <string>
#include "tcp-exception.h"

class TCPClient{
  public:
    TCPClient(std::string, int)throw(TCPException);
    std::string read()throw(TCPException);
    void send(std::string)throw(TCPException);
    void setup()throw(TCPException);
    void close();
  private:
    int d_port;
    SOCKET d_sd;
    std::string d_ip;
};

#endif
