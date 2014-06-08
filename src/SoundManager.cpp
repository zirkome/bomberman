#include <exception>
#include <fmod.h>
#include <fmod_errors.h>

#include "SoundManager.hpp"
#include "Fault.hpp"
#include "config.h"

SoundManager::SoundManager()
  : _init(false)
{
  FMOD_RESULT res;
  if ((res = FMOD_System_Create(&_system)) != FMOD_OK ||
      (res = FMOD_System_Init(_system, 32, FMOD_INIT_NORMAL, NULL)) != FMOD_OK)
    {
      throw nFault("FMOD_init: " + std::string(FMOD_ErrorString(res)));
    }
  _init = true;
}

SoundManager::~SoundManager()
{
  if (_init)
    {
      for (std::map<Sample, Sound *>::iterator it = _music.begin(); it !=  _music.end(); it++)
        {
          delete it->second;
        }
      FMOD_System_Close(_system);
      FMOD_System_Release(_system);
    }
}

bool	SoundManager::loadSounds()
{
  if (_init)
    {
      try
        {
          _music[GAME] = new Sound(_system, RES_SOUND "game.mp3",
                                   FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL);
          _music[INTRO] = new Sound(_system, RES_SOUND "intro.mp3",
                                    FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL);
          _music[BOMB_EXPLOSION] = new Sound(_system, RES_SOUND "bomb.wav",
                                             FMOD_CREATESAMPLE | FMOD_LOOP_NORMAL);
          _music[SWITCH_MENU] = new Sound(_system, RES_SOUND "switch_menu.wav",
                                          FMOD_CREATESAMPLE | FMOD_LOOP_NORMAL);
        }
      catch (std::exception& e)
        {
          std::cerr << e.what() << std::endl;
          return false;
        }
      return true;
    }
  return false;
}

bool	SoundManager::manageSound(Sample sample, ManageType type, bool loop)
{
  std::map<Sample, Sound *>::iterator it = _music.find(sample);

  if (_init)
    {
      if (it != _music.end())
        {
          Sound *sound = it->second;
          switch (type)
            {
            case PLAY:
              return sound->play(loop);
              break;
            case PAUSE:
              return sound->pause();
              break;
            case STOP:
              return sound->stop();
              break;
            }
        }
      else
        {
          std::cerr << "Unable to find sample " << sample << "to play" << std::endl;
          return false;
        }
    }
  return false;
}
