#ifndef GRAPHICS_HPP
# define GRAPHICS_HPP

# include <iostream>
# include <exception>
# include <stdexcept>

# include <Clock.hh>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <Geometry.hh>
# include <Texture.hh>
# include <BasicShader.hpp>
# include <Model.hh>

# include "Map.hpp"
# include "Pan.hpp"
# include "SkyBox.hpp"
# include "FontText.hpp"
# include "PlayerManager.hpp"

# include "config.h"

/*
** Stock all the information needed to display
*/

class GameGraphics
{
public:
  GameGraphics();
  ~GameGraphics();

  bool init(const glm::ivec2& win, const glm::ivec2& mapSize, bool splitScreen);

  void updateGraphic(gdl::Clock const &clock);

  void drawGame(gdl::Clock const &clock, const std::vector<PlayerManager*>& players) const;

  const FontText& getTextWriter() const;
  gdl::AShader *getShader() const;

  void setHudProj() const;

protected:
  bool _init;

  float _fov;
  bool  _splitScreen;
  glm::ivec2 _win;

  glm::mat4 _proj;
  gdl::AShader* _shader;
  GameGeometry *_ground;
  SkyBox _skybox;
  FontText *_font;
  glm::mat4 _ortho;
  SharedPointer<Texture> _groundTex;
};

#endif
