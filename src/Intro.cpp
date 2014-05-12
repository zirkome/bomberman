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
  try
    {
      return _ogl.init();
    }
  catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
      return false;
    }
}

bool Intro::update()
{
  _clock.updateClock(_interface.clock);
  _input.updateInputs(_interface.input);
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
