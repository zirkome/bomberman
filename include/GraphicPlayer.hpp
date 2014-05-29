#ifndef _GRAPHICPLAYER_H_
#define _GRAPHICPLAYER_H_

#include "AObject.hpp"
#include <string>

class GraphicPlayer : public AObject
{
private:
  gdl::Model	_player;
  float		_speed;
  std::string	_model_path;

public:
  GraphicPlayer(std::string const &path);
  virtual ~GraphicPlayer();
  virtual bool	initialize();

  virtual void	draw(gdl::AShader *shader);
};

#endif /* _GRAPHICPLAYER_H_ */
