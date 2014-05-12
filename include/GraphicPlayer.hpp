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
  // La fonction update sert a gerer le comportement de l'objet
  virtual void	update(gdl::Clock const &clock, gdl::Input &input);
  // La fonction draw sert a dessiner l'objet
  virtual void	draw(gdl::AShader *shader);
};
