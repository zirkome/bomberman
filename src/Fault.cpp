/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/
#include "Fault.hpp"

Fault::Fault(std::string const& err, std::string const& file, std::string const& func) throw()
  : m_err(err + std::string(" (in file ") + file + std::string(" ,in function: ") + func + std::string(")"))
{
}

const char* Fault::what() const throw()
{
  return m_err.c_str();
}
