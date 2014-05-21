#ifndef _ARMAGETROCAM_H_
#define _ARMAGETROCAM_H_

#include <list>
#include "ACamera.hpp"

class	ArmagetroCam : public ACamera
{
private:
  std::list<glm::vec2>	_follow_pos;
public:
  ArmagetroCam(const glm::vec2 &);
  virtual void	update(gdl::Input &input, const gdl::Clock &clock);
  void		update(const glm::vec2 &);
  virtual ~ArmagetroCam() {};
};

#endif /* _ARMAGETROCAM_H_ */
