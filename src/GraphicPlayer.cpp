#include "GrapicPlayer.hpp"

GraphicPlayer::GraphicPlayer(std::string const &path)
{
  _model_path = path;
}

GraphicPlayer::~GraphicPlayer()
{

}

bool GraphicPlayer::initialize()
{
  if (_player.load(_path) == false)
    {
      std::cerr << "Can't load : " << _model_path << std::endl;
      return false;
    }
  return (true);
}

void GraphicPlayer::update(gdl::Clock const &clock, gdl::Input &input)
{
  // On multiplie par le temps ecoule depuis la derniere image pour que la vitesse ne depende pas
  //de la puissance de l'ordinateur

  if (input.getKey(SDLK_UP))
    translate(glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * _speed);
  if (input.getKey(SDLK_DOWN))
    translate(glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * _speed);
  if (input.getKey(SDLK_LEFT))
    translate(glm::vec3(-1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
  if (input.getKey(SDLK_RIGHT))
    translate(glm::vec3(1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
}

void GraphicPlayer::draw(gdl::AShader *shader)
{
  _player.draw(*shader, getTransformation());
}
