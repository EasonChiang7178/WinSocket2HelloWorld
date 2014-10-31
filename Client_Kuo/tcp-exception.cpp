#include <string>
#include "tcp-exception.h"

TCPException::TCPException(std::string s){
    d_err = s;
}
TCPException::~TCPException() throw(){}
const char *TCPException::what() throw(){
    return d_err.c_str();
}

