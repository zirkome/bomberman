#include "Intro.hpp"

Intro::Intro()
{
  _context = new gdl::SdlContext;
  _show = true;
  _init = false;
  _game = NULL;
}

Intro::~Intro()
{
  if (_init)
    {
      delete _game;

      _context->stop();
      delete _context;
    }
}

bool Intro::initialize()
{
  if (!_context->start(1024, 900, "Bomberman"))
    return false;
  _init = true;
  if (!_ogl.init())
    return false;
  std::vector<std::string> tmp;
  tmp.push_back("sdf");
  _game = new ::Game(2, 2, tmp, "dsf");
  return true;
}

bool Intro::update()
{
  _context->updateClock(_clock);
  _context->updateInputs(_input);
  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return false;
  if (_show)
    return _menu->updateMenu(_input);
  else
    _game->updateGame(_input);
  return true;
}

void Intro::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (_show)
    _menu->drawMenu(_ogl);
  else
    _game->drawGame(_ogl);
  _context->flush();
}
