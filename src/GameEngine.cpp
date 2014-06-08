#include <config.h>
#include <glm/core/type.hpp>
#include <glm/core/type_vec2.hpp>
#include <GameEngine.hpp>
#include <GL/glew.h>
#include <ResourceManager.hpp>
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_mouse.h>
#include <SDL_stdinc.h>
#include <SDL_video.h>
#include <SharedPointer.hpp>
#include <Singleton.hpp>
#include <Texture.hpp>
#include <string>
#include <vector>

GameEngine::GameEngine()
  : _state(Intro), _init(false), _intro(NULL), _game(NULL), _context(new gdl::SdlContext)
{
}

GameEngine::~GameEngine()
{
  if (_init)
    {
      if (_state == Game)
        delete _game;
      else
        delete _intro;
      _context->stop();
      delete _context;
    }
}

bool GameEngine::initialize()
{
  const int width = 1024;
  const int heigth = 900;

  if (!_context->start(width, heigth, "Bomberman", SDL_INIT_VIDEO, /*SDL_WINDOW_FULLSCREEN |*/ SDL_WINDOW_OPENGL))
    return false;
  SDL_SetRelativeMouseMode(SDL_TRUE);
  _init = true;
  std::vector<std::string> tmp;
  tmp.push_back("sdf");

  SoundManager::getInstance()->loadSounds();
  SoundManager::getInstance()->manageSound(SoundManager::INTRO, SoundManager::PLAY);
  // SoundManager::getInstance()->manageSound(SoundManager::GAME, SoundManager::PLAY, true);
  // _game = new ::Game(glm::ivec2(width, heigth), 1, 0, tmp, "map2.map");
  _intro = new ::Intro(glm::ivec2(width, heigth));
  //_game = new ::Game(glm::ivec2(width, heigth), 1, 0, "script/medium.lua", "map/2.map");
  return true;
}

bool GameEngine::update()
{
  if (_state == Intro && _intro->finish() == true)
    {
      SoundManager::getInstance()->manageSound(SoundManager::INTRO, SoundManager::STOP);
      SoundManager::getInstance()->manageSound(SoundManager::GAME, SoundManager::PLAY);
      _state = Game;
      _game = _intro->getGame();
      _context->updateClock(_clock);
      delete _intro;
    }
  _context->updateClock(_clock);
  _context->updateInputs(_input);
  if (_input.getInput(SDL_BUTTON_LEFT))
    SDL_SetRelativeMouseMode(SDL_TRUE);
  if (_input.getKey(SDLK_LCTRL) && _input.getInput(SDLK_LALT))
    SDL_SetRelativeMouseMode(SDL_FALSE);
  if (_input.getKey(SDLK_ESCAPE, true))
    {
      if (_state == Game)
        {
	  SoundManager::getInstance()->manageSound(SoundManager::GAME, SoundManager::STOP);
	  SoundManager::getInstance()->manageSound(SoundManager::INTRO, SoundManager::PLAY);
          _state = Intro;
          _intro = new ::Intro(glm::ivec2(1024, 900), true);
        }
      else
        return false;
    }
  if (_input.getInput(SDL_QUIT))
    return false;
  switch (_state)
    {
    case Intro:
      return _intro->updateIntro(_input, _clock);
    case Game:
    default:
      return _game->updateGame(_input, _clock);
    }
}

void GameEngine::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  switch (_state)
    {
    case Intro:
      _intro->drawIntro(_clock);
      break;
    case Game:
    default:
      _game->drawGame(_clock);
      break;
    }
  _context->flush();
}
