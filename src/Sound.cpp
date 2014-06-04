//
// Sound.cpp for Sound in /home/debas_e/Project/C++/bomberman
//
// Made by Etienne
// Login   <debas_e@epitech.net>
//
// Started on  Wed Jun  4 23:18:49 2014 Etienne
// Last update Thu Jun  5 00:25:16 2014 Etienne
//

#include "Sound.hpp"

Sound::Sound(FMOD_SYSTEM *system, const std::string &path, int create_flags)
  : _path(path), _system(system)
{
  FMOD_RESULT res = FMOD_System_CreateSound(system, path.c_str(), create_flags, 0, &_sound);
  if (res != FMOD_OK)
    {
      throw nFault("FMOD_System_CreateSound: " + std::string(FMOD_ErrorString(res)));
    }
}

bool	Sound::play(bool loop)
{
  FMOD_RESULT res;

  if (loop)
    FMOD_Sound_SetLoopCount(_sound, -1);
  res = FMOD_System_PlaySound(_system, FMOD_CHANNEL_FREE, _sound, 0, NULL);
  if (res != FMOD_OK)
    {
      std::cerr << "FMOD_System_PlaySound : " + std::string(FMOD_ErrorString(res)) << std::endl;
      return false;
    }
  return true;
}

void	Sound::stop()
{

}
