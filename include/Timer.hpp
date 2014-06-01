#ifndef TIMER_HPP_
# define TIMER_HPP_

# include <Texture.hh>
# include <AssetsManager.hpp>

class Timer
{
private:
  float _time;

public:
  Timer(float time);
  ~Timer();
  bool update(gdl::Clock const &clock);
  void reset(float time);
};

#endif /* !TIMER_HPP_ */
