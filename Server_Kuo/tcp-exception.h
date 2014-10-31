#ifndef TCP_EXCEPTION_H
#define TCP_EXCEPTION_H

#include <exception>
#include <string>

class TCPException : public std::exception{
  public:
    explicit TCPException(std::string s);
    virtual ~TCPException() throw();
    virtual const char *what() throw();
  private:
    std::string d_err;
};

#endif
