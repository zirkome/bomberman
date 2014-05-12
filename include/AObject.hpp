#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SdlContext.hh>
#include <Clock.hh>
#include <Input.hh>
#include <AShader.hh>

// La classe abstraite representant un objet avec sa position, sa rotation et son echelle

class AObject
{
private:
  glm::vec3 _position;
  glm::vec3 _rotation;
  glm::vec3 _scale;
public:
  AObject();
  virtual ~AObject() {}

  // La fonction initialize charge l'objet ou le construit
  virtual bool	initialize() = 0;

  // La fonction update sert a gerer le comportement de l'objet
  virtual void	update(gdl::Clock const &clock, gdl::Input &input) = 0;

  // La fonction draw sert a dessiner l'objet
  virtual void	draw(gdl::AShader *shader) = 0;

  void		translate(glm::vec3 const &v);
  void		rotate(glm::vec3 const &axis, float angle);
  void		scale(glm::vec3 const &scale);
  glm::mat4	getTransformation();
};
