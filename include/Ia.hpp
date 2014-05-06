/*
** Ia.hpp for bomberman in /home/max/projet/actu/bomberman
**
** Made by Maxime
** Login   <max@epitech.net>
**
** Started on  Mon May  5 11:28:53 2014 Maxime
** Last update Mon May  5 11:37:15 2014 Maxime
*/

#ifndef IA_HPP_
#define IA_HPP_

#include <string>

class Ia
{
public:
  Ia();
  ~Ia();
  bool parse(std::string const &);
  void exec();
};

#endif
