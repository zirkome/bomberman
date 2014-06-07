#ifndef _AOBJECT_H_
# define _AOBJECT_H_

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <SdlContext.hh>
# include <Clock.hh>
# include <Input.hh>
# include <AShader.hh>

class AObject
{
public:
  AObject();
  virtual ~AObject() {};

  virtual void draw(gdl::AShader* shader, const gdl::Clock& clock) = 0;

  void translate(const glm::vec3& v);
  void rotate(const glm::vec3& axis, float angle);
  void scale(const glm::vec3& scale);

  void setPosition(const glm::vec3& pos);
  void setRotation(const glm::vec3& rot);
  void setScale(const glm::vec3& scl);

  void resetTransformation();

  const glm::mat4 &getTransformation();

private:
  void calculate_matrix();
protected:
  bool _modified;
  glm::vec3 _position;
  glm::vec3 _rotation;
  glm::vec3 _scale;

  glm::mat4 _matrix;
};

#endif /* _AOBJECT_H_ */
