#ifndef _SOUNDMANAGER_H_
# define _SOUNDMANAGER_H_

# include <map>
# include <iostream>

# include "Singleton.hpp"
# include "Sound.hpp"

class SoundManager : public Singleton<SoundManager>
{
  friend SoundManager* Singleton<SoundManager>::getInstance();
  friend void Singleton<SoundManager>::kill();

public:

  enum Sample
    {
      INTRO = 0,
      SWITCH_MENU,
      GAME,
      BOMB_EXPLOSION,
      GET_ITEM,
      TIC_TAC,
    };

  enum ManageType
    {
      PLAY = 0,
      PAUSE,
      STOP,
    };

  virtual bool manageSound(Sample sample,
			   ManageType type,
			   bool loop = false);

  // virtual void stopMusic(bool fadeOut = false);

  // virtual void playSound(int id,
  // 			 bool loop = false,
  // 			 bool fadeIn = false);
  // virtual void stopSound(bool fadeOut = false);

  virtual bool	loadSounds();
private:
  bool	_init;
  FMOD_SYSTEM *_system;
  std::map<Sample, Sound *> _music;
private:
  SoundManager();
  virtual ~SoundManager();
};

#endif /* !_SOUNDMANAGER_H_ */
