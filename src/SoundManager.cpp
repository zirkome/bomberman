#include <exception>
#include <SDL2/SDL_mixer.h>

#include "SoundManager.hpp"
#include "Fault.hpp"

SoundManager::SoundManager()
  : _init(false)
{
  int ret = 0;

  ret = Mix_Init(MIX_INIT_OGG|MIX_INIT_MP3|MIX_INIT_FLAC);
  if (!ret)
    throw nFault("Mix_Init: " + std::string(Mix_GetError()));
  _init = true;
}

SoundManager::~SoundManager()
{
  Mix_Quit();
}
