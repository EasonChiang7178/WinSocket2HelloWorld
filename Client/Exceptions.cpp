#include "Exceptions.h"

ExecuteWinSocketFailed::ExecuteWinSocketFailed(const std::string& info, const int& code) {
	error_info = info;
	error_code = code;
}

const char* ExecuteWinSocketFailed::what() const {
	std::string error_code_str;
	std::stringstream ss;
	ss << error_code; ss >> error_code_str;

	return (error_info + " (Error code:" + error_code_str + ")").c_str();
}

const char* CreateSocketFailed::what() const {
	return "Create Socket Failed";
}