#ifndef _SOUNDMANAGER_H_
# define _SOUNDMANAGER_H_

# include "Singleton.hpp"
# include "ISound.hpp"

class SoundManager : public Singleton<SoundManager>
{
public:
  // virtual void playMusic(int id,
  // 			 bool loop = false,
  // 			 bool fadeIn = false);
  // virtual void stopMusic(bool fadeOut = false);

  // virtual void playSound(int id,
  // 			 bool loop = false,
  // 			 bool fadeIn = false);
  // virtual void stopSound(bool fadeOut = false);

private:
  bool _init;
  std::list<ISound*> _music;

private:
  SoundManager();
  virtual ~SoundManager();
};

#endif /* !_SOUNDMANAGER_H_ */
