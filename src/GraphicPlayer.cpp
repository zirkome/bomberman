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

void GraphicPlayer::draw(gdl::AShader *shader)
{
  _player.draw(*shader, getTransformation());
}
