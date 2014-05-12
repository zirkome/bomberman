#include "GameEngine.hpp"

GameEngine::GameEngine()
{
  _context = new gdl::SdlContext;
  _show = false;
  _init = false;
  _game = NULL;
}

GameEngine::~GameEngine()
{
  if (_init)
    {
      delete _game;

      _context->stop();
      delete _context;
    }
}

bool GameEngine::initialize()
{
  if (!_context->start(1024, 900, "Bomberman", SDL_INIT_VIDEO, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL))
    return false;
  _init = true;
  if (!_ogl.init())
    return false;
  std::vector<std::string> tmp;
  tmp.push_back("sdf");
  _game = new ::Game(2, 2, tmp, "dsf");
  return true;
}

bool GameEngine::update()
{
  _context->updateClock(_clock);
  _context->updateInputs(_input);
  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return false;
  if (_show)
    return _menu->updateMenu(_input, _clock);
  else
    _game->updateGame(_input, _clock);
  return true;
}

void GameEngine::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (_show)
    _menu->drawMenu(_ogl, _clock);
  else
    _game->drawGame(_ogl, _clock);
  _context->flush();
}
