#ifndef _ISOUND_H_
# define _ISOUND_H_

# include <fmod.h>
# include <fmod_errors.h>
# include <string>
# include <exception>
# include <iostream>

# include "Fault.hpp"

class Sound
{
public:
  Sound(FMOD_SYSTEM *system, const std::string &path, int create_flags);
  virtual ~Sound();
  virtual bool play(bool loop);
  virtual bool pause();
  virtual bool stop();
  // virtual void fadeIn(int duration) = 0;
  // virtual void fadeOut(int duration) = 0;
  // virtual void fadeTo(float volume, int duration) = 0;
private:
  std::string	_path;
  FMOD_SOUND *_sound;
  FMOD_SYSTEM  *_system;
  FMOD_CHANNEL *_chan;
  bool	_playing, _paused;
};

#endif /* _ISOUND_H_ */
