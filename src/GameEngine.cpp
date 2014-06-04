#include "GameEngine.hpp"

GameEngine::GameEngine()
{
  _context = new gdl::SdlContext;
  _show = false;
  _init = false;
  _game = NULL;
  _menu = NULL;
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
  const int width = 1024;
  const int heigth = 900;

  if (!_context->start(width, heigth, "Bomberman", SDL_INIT_VIDEO, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL))
    return false;
  SDL_SetRelativeMouseMode(SDL_TRUE);
  _init = true;
  std::vector<std::string> tmp;
  tmp.push_back("sdf");
  AssetsManager::createAssets();
  SoundManager::getInstance()->loadSounds();
  SoundManager::getInstance()->playSound(SoundManager::GAME, true);
  _game = new ::Game(glm::ivec2(width, heigth), 1, 0, tmp, "map2.map");
  return true;
}

bool GameEngine::update()
{
  _context->updateClock(_clock);
  _context->updateInputs(_input);
  if (_input.getInput(SDL_BUTTON_LEFT))
    SDL_SetRelativeMouseMode(SDL_TRUE);
  if (_input.getKey(SDLK_LCTRL) && _input.getInput(SDLK_LALT))
    SDL_SetRelativeMouseMode(SDL_FALSE);
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
    _menu->drawMenu(_clock);
  else
    _game->drawGame(_input, _clock);
  _context->flush();
}
