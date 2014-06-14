#ifndef TIMER_HPP_
# define TIMER_HPP_

# include <Texture.hh>

class Timer
{
private:
  double _time;
  double _startTime;
public:
  Timer(double time);
  ~Timer();
  bool update(double clock);
  void reset(double time);
  double getTime() const;
  void	addTime(double time);
  double getRemainingTime() const;
};

#endif /* !TIMER_HPP_ */
