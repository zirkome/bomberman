#ifndef GRAPHICS_HPP
# define GRAPHICS_HPP

# include <iostream>
# include <exception>
# include <stdexcept>

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <Geometry.hh>
# include <Texture.hh>
# include <BasicShader.hpp>
# include <Model.hh>

# include "config.h"

/*
** Stock all the information needed to display
*/

class GameGraphics
{
public:
  GameGraphics();
  virtual ~GameGraphics();

  virtual bool init(const glm::ivec2& win);

  const glm::mat4 &getPerspectiveProj() const;

  gdl::AShader *getShader() const;

protected:
  float _fov;
  glm::mat4 _proj;
  gdl::AShader* _shader;
};

#endif
