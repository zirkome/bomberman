/*
** Intro.hpp for bomberman in /home/max/projet/actu/bomberman
**
** Made by Maxime
** Login   <max@epitech.net>
**
** Started on  Mon May  5 11:28:53 2014 Maxime
** Last update Wed May  7 12:14:16 2014 Maxime
*/

#ifndef INTRO_HPP_
#define INTRO_HPP_

#include "Menu.hpp"

class Intro/* : public gdl::Game*/
{
private:
  bool _show;
  Menu *_menu;
  Graphics _interface;
public:
  Intro();
  ~Intro();
  bool initialize();
  bool update();
  void draw();
};

#endif
