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
  if (!_interface.context.start(800, 600, "Bomberman!"))
    return false;
  glEnable(GL_DEPTH_TEST);
  return true;
}

bool Intro::update()
{
  _interface.context.updateClock(_interface.clock);
  _interface.context.updateInputs(_interface.input);
  if (_interface.input.getKey(SDLK_ESCAPE) || _interface.input.getInput(SDL_QUIT))
    return false;
  if (_show)
    return _menu->updateMenu(_interface);
  _interface.context.flush();
  return true;
}

void Intro::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (_show)
    return _menu->drawMenu(_interface);
}
