#include "Pan.hpp"

Pan::Pan(IEntity::Type assetsType)
{
  // on load la texture depuis le singleton
  _texture = AssetsManager::getInstance()->getAssets<gdl::Texture>(assetsType);
}

Pan::~Pan()
{

}

bool Pan::initialize()
{

  _speed = 10.0f;
  // on set la color d'une premiere face
  // _geometry.setColor(glm::vec4(1, 0, 0, 1));

  // tout les pushVertex qui suivent seront de cette couleur
  // On y push les vertices d une premiere face
  // _geometry.setColor(glm::vec4(0, 0, 1, 1));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, -0.5));
  _geometry.pushVertex(glm::vec3(0.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, 0.5));
  _geometry.pushVertex(glm::vec3(-0.5, -0.5, -0.5));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  // Tres important, on n'oublie pas de build la geometrie pour envoyer ses informations a la carte
  //graphique
  _geometry.build();
  return (true);
}

void Pan::update(gdl::Clock const &clock, gdl::Input &input)
{
	(void) clock;
	(void) input;
}

void Pan::draw(gdl::AShader *shader)
{
  // On bind la texture pour dire que l'on veux l'utiliser
  _texture->bind();
  // Et on dessine notre cube
  _geometry.draw(*shader, getTransformation(), GL_QUADS);
}
