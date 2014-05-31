#ifndef ACAMERA_H
# define ACAMERA_H

# include <Input.hh>
# include <Clock.hh>

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>

# include "config.h"

class ACamera
{
public:
  ACamera(const glm::vec3& pos = glm::vec3(0.0, 0.0, -10.0), const glm::vec3& forward = glm::vec3(0.0, 0.0, 0.0));
  virtual ~ACamera();

  virtual void update(UNUSED gdl::Input& input, UNUSED const gdl::Clock& clock) {};

  virtual void update(UNUSED const glm::vec3 &toFollow) {};

  virtual const glm::mat4& project();

  void translate(const glm::vec3& pos);

  void setPosition(const glm::vec3& pos);
  void setForward(const glm::vec3& forw);
  void setUp(const glm::vec3& up);

  const glm::vec3& getPosition() const {return _pos;};
  const glm::vec3& getForward() const {return _forward;};
  const glm::vec3& getUp() const {return _up;};

protected:
  glm::mat4 _proj;
  glm::vec3 _pos;
  glm::vec3 _forward;
  glm::vec3 _up;
};

#endif // ACAMERA_H
