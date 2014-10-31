#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "tcp-client.h"
using namespace std;
int main(int argc, char *argv[]){
    char str[1024];
    try{
      TCPClient client("127.0.0.1", 1234);
      cout << "connected" << endl;
      while(true){
        printf("> ");
        gets(str);
        client.send(str);
        cout << client.read() << endl;
      }
      client.close();
    } catch(TCPException e){
      cerr << e.what() << endl << "close client" << endl;
    }
    return 0;
}
