#include "AObject.hpp"

AObject::AObject() :
  _position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1), _modified(false)
{
  calculate_matrix();
}

void AObject::translate(const glm::vec3& v)
{
  _position += v;
  _modified = true;
}

void AObject::rotate(const glm::vec3& axis, float angle)
{
  _rotation += axis * angle;
  _modified = true;
}

void AObject::scale(const glm::vec3& scale)
{
  _scale *= scale;
  _modified = true;
}

void AObject::setPosition(const glm::vec3& pos)
{
  _position = pos;
  _modified = true;
}

void AObject::setRotation(const glm::vec3& rot)
{
  _rotation = rot;
  _modified = true;
}

void AObject::setScale(const glm::vec3& scl)
{
  _scale = scl;
  _modified = true;
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
  if (_modified)
    {
      _modified = false;
      calculate_matrix();
    }
  return _matrix;
}
