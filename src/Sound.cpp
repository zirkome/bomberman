#include "Sound.hpp"

Sound::Sound(FMOD_SYSTEM *system, const std::string &path, int create_flags)
  : _path(path), _system(system), _chan(0), _playing(false), _paused(false)
{
  FMOD_RESULT res = FMOD_System_CreateSound(system, path.c_str(), create_flags, 0, &_sound);
  if (res != FMOD_OK)
    {
      throw nFault("FMOD_System_CreateSound: " + std::string(FMOD_ErrorString(res)));
    }
}

Sound::~Sound()
{
  FMOD_Sound_Release(_sound);
}

bool	Sound::play(bool loop)
{
  FMOD_RESULT res;

  /* is not playing ? */
  if (!_playing)
    {
      if (loop)
	{
	  res = FMOD_Sound_SetLoopCount(_sound, -1);
	  if (res != FMOD_OK)
	    {
	      std::cerr << "FMOD_System_SetLoopCount : " +
		std::string(FMOD_ErrorString(res)) << std::endl;
	      return false;
	    }
	}
      res = FMOD_System_PlaySound(_system, FMOD_CHANNEL_REUSE, _sound, 0, &_chan);
      if (res != FMOD_OK)
	{
	  std::cerr << "FMOD_System_PlaySound : " + std::string(FMOD_ErrorString(res)) << std::endl;
	  return false;
	}
      return true;
    }
  return false;

  /* is paused ? */
  if (_paused)
    {
      res = FMOD_Channel_SetPaused(_chan, 0);
      if (res != FMOD_OK)
	{
	  std::cerr << "FMOD_System_SetPaused : " + std::string(FMOD_ErrorString(res)) << std::endl;
	  return false;
	}
      return true;
    }
}

bool	Sound::pause()
{
  FMOD_RESULT res;

  if (!_paused)
    {
      res = FMOD_Channel_SetPaused(_chan, 1);
      if (res != FMOD_OK)
	{
	  std::cerr << "FMOD_Channel_SetPaused : " + std::string(FMOD_ErrorString(res)) << std::endl;
	}
    }
  return true;
}

bool	Sound::stop()
{
  FMOD_RESULT res;

  res = FMOD_Channel_Stop(_chan);
  if (res != FMOD_OK)
    {
      std::cerr << "FMOD_Channel_Stop : " + std::string(FMOD_ErrorString(res)) << std::endl;
      return false;
    }
  _playing = false;
  return true;
}
