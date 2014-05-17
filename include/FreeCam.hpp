#ifndef FREECAM_H
# define FREECAM_H

# include "ACamera.hpp"
# include <SdlContext.hh>

class FreeCam : public ACamera
{
public:
  FreeCam();
  virtual ~FreeCam();

  virtual void update(gdl::Input& input, const gdl::Clock& clock);

protected:
  virtual void moveCam(gdl::Input& input, float delta);
  void vectorsFromAngles();

private:
  glm::vec3 _target;
  glm::vec3 _left;
  float _speed;
  float _sensivity;
  float _phi;
  float _theta;
};

#endif // FREECAM_H
