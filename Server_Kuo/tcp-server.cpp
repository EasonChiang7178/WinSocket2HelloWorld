#include <iostream>
#include <winsock.h>
#include "tcp-server.h"
#include "tcp-exception.h"

#define MAXLINE 4096
TCPServer::TCPServer(int port)throw(TCPException){
    struct sockaddr_in serv;
    WSADATA wsadata;
    if(WSAStartup(MAKEWORD(2,2), &wsadata)!=0)
      throw TCPException("err: can't use WinSock DLL");
    if((d_sd=socket(AF_INET, SOCK_STREAM, 0)) == (unsigned)SOCKET_ERROR)
      throw TCPException("err: can't open TCP socket");
    serv.sin_family      = AF_INET;
    serv.sin_addr.s_addr = 0;
    serv.sin_port        = htons(port);
    if(bind(d_sd, (LPSOCKADDR)&serv, sizeof(serv)) < 0)
      throw TCPException("err: can't bind local address");
    if(listen(d_sd, SOMAXCONN) < 0)
      throw TCPException("err: listen() error");
}
void TCPServer::accept()throw(TCPException){
    struct sockaddr_in cli;
    int cli_len = sizeof(cli);
    d_cli_sd = ::accept(d_sd, (struct sockaddr*)&cli, &cli_len);
    if(d_cli_sd == (unsigned)SOCKET_ERROR)
      throw TCPException("err: accept() error");
}
std::string TCPServer::read()throw(TCPException){
    int n;
    char str[MAXLINE];
    if((n=::recv(d_cli_sd, str, MAXLINE, 0)) == 0)
      throw TCPException("err: connection closed");
    str[n] = '\0';
    return std::string(str);
}
void TCPServer::send(std::string s)throw(TCPException){
    if(::send(d_cli_sd, s.c_str(), s.size(), 0) == SOCKET_ERROR)
      throw TCPException("err: connection closed");
}
void TCPServer::close(){
    closesocket(d_sd);
    closesocket(d_cli_sd);
    WSACleanup(); 
}
