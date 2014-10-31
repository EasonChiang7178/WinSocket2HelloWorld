#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "tcp-server.h"
using namespace std;
int main(int argc, char *argv[]){
    char str[1024];
    try{
      TCPServer server(1234);
      cout << "wait for client" << endl;
      server.accept();
      cout << "connected" << endl;
      while(true){
        cout << server.read() << endl;
        printf("> ");
        gets(str);
        server.send(str);
      }
      server.close();
    } catch(TCPException e){
      cerr << e.what() << endl << "close server" << endl;
    }
    return 0;
}
