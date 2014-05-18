#ifndef GRAPHICS_HPP
# define GRAPHICS_HPP

# include <iostream>
# include <exception>

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <Geometry.hh>
# include <Texture.hh>
# include <BasicShader.hh>
# include <Model.hh>

# include "FBORenderer.hpp"
# include "config.h"

/*
** Stock all the information needed to display
*/

class Graphics
{
public:
  virtual ~Graphics() {};

  virtual bool init(const glm::ivec2& win) = 0;
  virtual void startFrame() const = 0;

  virtual gdl::AShader *getShader() const = 0;
};



class MenuGraphics : public Graphics
{
public:
  MenuGraphics();
  virtual ~MenuGraphics();

  virtual bool init(const glm::ivec2& win);
  virtual void startFrame() const;

  gdl::AShader *getShader() const {return _shader;};

private:
  glm::mat4 _ortho;
  gdl::AShader *_shader;
};


class GameGraphics : public Graphics
{
public:
  GameGraphics();
  virtual ~GameGraphics();

  virtual bool init(const glm::ivec2& win);
  virtual void startFrame() const;

  void processFrame() const;

  gdl::AShader *getShader() const {return _fbo ? _fbo->getShader() : NULL;};

protected:
  float _fov;
  glm::mat4 _proj;
  FBORenderer* _fbo;
};

#endif
