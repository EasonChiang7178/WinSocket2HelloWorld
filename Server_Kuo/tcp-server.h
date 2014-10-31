#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <winsock.h>
#include "tcp-server.h"
#include "tcp-exception.h"

class TCPServer{
  public:
    TCPServer(int)throw(TCPException);
    std::string read()throw(TCPException);
    void send(std::string)throw(TCPException);
    void accept()throw(TCPException);
    void close();
  private:
    SOCKET d_sd;
    SOCKET d_cli_sd;
};

#endif
