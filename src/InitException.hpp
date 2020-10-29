#pragma once

#include <exception>
#include <string>

class InitException : virtual public std::exception {
protected:
  std::string err_msg;

public:
  explicit InitException(const std::string &err_msg) : err_msg{err_msg} {};
  virtual ~InitException(){};
  virtual const char *what() const throw() { return err_msg.c_str(); }
};
