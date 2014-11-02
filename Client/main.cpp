
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "TCPConnector.h"

using namespace std;

string pathToConfig = "BodyDetection.cfg";

int main(int argc, char** argv) {
	/* Loading the configuration */
	fstream fConfig;

	fConfig.open(pathToConfig.c_str(), ios::in);
	if (fConfig.is_open() == false) {
		cerr << "> [ERROR]: " << pathToConfig << " doesn't exist!" << endl;
		exit(EXIT_FAILURE);
	}
	
	string IPAddress;
	unsigned int Port;
	double upperRightX, upperRightY,
		   upperLeftX, upperLeftY,
		   lowerRightX, lowerRightY,
		   lowerLeftX, lowerLeftY;

		// Load each line...
	string lineEntry, entryName, entryValue;
	while (fConfig.eof() == false) {
		fConfig >> lineEntry;
		size_t colonPos = lineEntry.find_last_of(':');

		entryName = lineEntry.substr(0, colonPos);
		entryValue = lineEntry.substr(colonPos + 1);

		stringstream ss;

		if (entryName == "Address")
			IPAddress = entryValue;
		else if (entryName == "Port") {
			ss << entryValue; ss >> Port;
		} else if (entryName == "UpperLeftCorner_X") {
			ss << entryValue; ss >> upperLeftX;
		} else if (entryName == "UpperLeftCorner_Y") {
			ss << entryValue; ss >> upperLeftY;
		} else if (entryName == "UpperRightCorner_X") {
			ss << entryValue; ss >> upperRightX;
		} else if (entryName == "UpperRightCorner_Y") {
			ss << entryValue; ss >> upperRightY;
		} else if (entryName == "LowerLeftCorner_X") {
			ss << entryValue; ss >> lowerLeftX;
		} else if (entryName == "LowerLeftCorner_Y") {
			ss << entryValue; ss >> lowerLeftY;
		} else if (entryName == "LowerRightCorner_X") {
			ss << entryValue; ss >> lowerRightX;
		} else if (entryName == "LowerRightCorner_Y") {
			ss << entryValue; ss >> lowerRightY;
		}
	}

	fConfig.close();

	TCPConnector connector;
	//TCPStream stream = connector.connect(1234, "127.0.0.1");

	connector.addConnection(Port, IPAddress);
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