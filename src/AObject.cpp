#include "AObject.hpp"

AObject::AObject() :
  _position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1)
{
  calculate_matrix();
}

void AObject::translate(const glm::vec3& v)
{
  _position += v;
  calculate_matrix();
}

void AObject::rotate(const glm::vec3& axis, float angle)
{
  _rotation += axis * angle;
  calculate_matrix();
}

void AObject::scale(const glm::vec3& scale)
{
  _scale *= scale;
  calculate_matrix();
}

void AObject::setPosition(const glm::vec3& pos)
{
  _position = pos;
  calculate_matrix();
}

void AObject::setRotation(const glm::vec3& rot)
{
  _rotation = rot;
  calculate_matrix();
}

void AObject::setScale(const glm::vec3& scl)
{
  _scale = scl;
  calculate_matrix();
}

void AObject::calculate_matrix()
{
  _matrix = glm::mat4(1);

  _matrix = glm::translate(_matrix, _position);

  _matrix = glm::rotate(_matrix, _rotation.x, glm::vec3(1, 0, 0));
  _matrix = glm::rotate(_matrix, _rotation.y, glm::vec3(0, 1, 0));
  _matrix = glm::rotate(_matrix, _rotation.z, glm::vec3(0, 0, 1));

  _matrix = glm::scale(_matrix, _scale);
}

const glm::mat4 &AObject::getTransformation()
{
  return _matrix;
}
