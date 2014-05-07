#include "Intro.hpp"

Intro::Intro()
{
  /* TODO : init interface */
  _show = true;
}

Intro::~Intro()
{
}

bool Intro::initialize()
{
  return true;
}

bool Intro::update()
{
  if (_show)
    return _menu->updateMenu(_interface);
  return true;
}

void Intro::draw()
{
  if (_show)
    return _menu->drawMenu(_interface);
}
