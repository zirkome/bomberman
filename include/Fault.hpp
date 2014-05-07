#ifndef FAULT_H
#define FAULT_H

#include <exception>
#include <string>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT_HERE __FILE__ ":" TOSTRING(__LINE__)

class Fault: public std::exception
{
public:
  Fault(std::string const& err = "", std::string const& file = "", std::string const& func = "") throw();

  virtual const char* what() const throw();
  virtual ~Fault() throw() {};

private:
  std::string m_err;
};

#define nFault(x) Fault((x), (AT_HERE), std::string(__FUNCTION__));

#endif // FAULT_H
