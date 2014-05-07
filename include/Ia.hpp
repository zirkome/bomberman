/*
** Ia.hpp for bomberman in /home/max/projet/actu/bomberman
**
** Made by Maxime
** Login   <max@epitech.net>
**
** Started on  Mon May  5 11:28:53 2014 Maxime
** Last update Wed May  7 12:10:32 2014 Maxime
*/

#ifndef IA_HPP_
#define IA_HPP_

#include <string>
#include "Map.hpp"

class Ia
{
public:
  Ia(std::string const &fileName, Map *currentMap);
  Ia(Map *currentMap);// ia basic if we have no files
  ~Ia();
};

#endif
