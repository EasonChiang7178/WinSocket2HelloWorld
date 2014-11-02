
#include <iostream>
#include <string>

#include "TCPConnector.h"

using namespace std;

int main(int argc, char** argv) {
	TCPConnector connector;
	//TCPStream stream = connector.connect(1234, "127.0.0.1");
	connector.addConnection(7878, "127.0.0.1");
	connector.addConnection(7878, "127.0.0.1");
	connector.addConnection(7878, "127.0.0.1");
	connector.addConnection(7878, "127.0.0.1");
	connector.addConnection(7878, "127.0.0.1");
	//connector.addConnection(7879, "127.0.0.1");
	//connector.addConnection(7881, "127.0.0.1");

	vector< TCPStream > streams = connector.connectAll();

	vector< testMessage > testVec;

	string keyBoardInput = "";
	while (keyBoardInput != "q") {
		cout << "> ";
		cin >> keyBoardInput;

		if (keyBoardInput != "enter") {
			testMessage testStr;
			testStr.blabla = keyBoardInput;
			testVec.push_back(testStr);
		} else {
			for (auto iter = streams.begin(); iter != streams.end(); iter++) {
				iter->addMessages(testVec);
				iter->send();
			}

			testVec.clear();
			testVec.resize(0);
		}
	}

	return 0;
}