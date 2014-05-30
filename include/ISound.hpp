#ifndef _ISOUND_H_
# define _ISOUND_H_

class ISound
{
public:
  virtual ~ISound() {}

public:
  virtual void play() = 0;
  virtual void stop() = 0;
  virtual void fadeIn(int duration) = 0;
  virtual void fadeOut(int duration) = 0;
  virtual void fadeTo(float volume, int duration) = 0;
};

#endif /* _ISOUND_H_ */
