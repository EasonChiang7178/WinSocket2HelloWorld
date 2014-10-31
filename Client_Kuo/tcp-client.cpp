#include <iostream>
#include <string>
#include <string.h>
#include <winsock.h>
#include "tcp-client.h"
#include "tcp-exception.h"

#define MAXLINE 4096

TCPClient::TCPClient(std::string s, int port)throw(TCPException){
    d_ip = s;
    d_port = port;
    setup();
}
void TCPClient::setup()throw(TCPException){
    struct sockaddr_in serv;
    WSADATA wsadata;
    if(WSAStartup(0x101,(LPWSADATA)&wsadata) != 0)
      throw TCPException("echo_cli: can't use WinSock DLL");
    serv.sin_family      = AF_INET;
    serv.sin_addr.s_addr = inet_addr(d_ip.c_str());
    serv.sin_port        = htons(d_port);
    if((d_sd=socket(AF_INET, SOCK_STREAM, 0)) == (unsigned int)SOCKET_ERROR)
      throw TCPException("echo_cli: can't open TCP socket");
    if(connect(d_sd, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
      throw TCPException("echo_cli: can't connect to server");
}
std::string TCPClient::read()throw(TCPException){
    int n;
    char str[MAXLINE];
    if((n=::recv(d_sd, str, MAXLINE, 0)) == 0)
      throw TCPException("echo_cli: connect close");
    str[n] = '\0';
    return std::string(str);
}
void TCPClient::send(std::string s)throw(TCPException){
    if(::send(d_sd, s.c_str(), s.size()+1, 0) == SOCKET_ERROR)
      throw TCPException("echo_cli: send error");
}
void TCPClient::close(){
    closesocket(d_sd);
    WSACleanup();
}
