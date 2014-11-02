#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "tcp-server.h"
using namespace std;
int main(int argc, char *argv[]){
    char str[1024];
    try{
      TCPServer server(7878);
	  //TCPServer server2(7879);
	  //TCPServer server3(7881);
      cout << "wait for client" << endl;
	  server.accept();
	  cout << "connected 1" << endl;
	  //server2.accept();
      cout << "connected 2" << endl;
	  //server3.accept();
	  cout << "connected 3" << endl;
      while(true){
		//cout << server2.read() << endl;
		printf("read 3\n");
        //cout << server2.read() << endl;
		printf("read 2\n");
		cout << server.read() << endl;
		printf("read 1\n");
        //printf("> ");
        //gets(str);
        //server.send(str);
      }
      server.close();
    } catch(TCPException e){
      cerr << e.what() << endl << "close server" << endl;
    }
    return 0;
}
