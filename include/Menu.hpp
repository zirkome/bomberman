/*
** Menu.hpp for bomberman in /home/max/projet/actu/bomberman
**
** Made by Maxime
** Login   <max@epitech.net>
**
** Started on  Mon May  5 11:28:53 2014 Maxime
** Last update Wed May  7 12:15:08 2014 Maxime
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include "Game.hpp"
#include "Graphics.hpp"

class Menu
{
private:
  bool _show;
  Game *_game;
public:
  Menu();
  ~Menu();
  bool updateMenu(Graphics &interface);
  void drawMenu(Graphics &interface);
};

#endif
