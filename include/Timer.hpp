#ifndef TIMER_HPP_
# define TIMER_HPP_

# include <Texture.hh>
# include <AssetsManager.hpp>

class Timer
{
private:
  double _time;

public:
  Timer(double time);
  ~Timer();
  bool update(double clock);
  void reset(double time);
};

#endif /* !TIMER_HPP_ */
