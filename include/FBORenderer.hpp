#ifndef FBORENDERER_H
# define FBORENDERER_H

# include <OpenGL.hh>
# include <glm/glm.hpp>

# include "FBOShader.hpp"
# include "PanShader.hpp"
# include "Pan.hpp"
# include "config.h"
# include "Fault.hpp"

/*
** A Frame Buffer Object is used by OpenGL to render into a texture. Specifically this implementation assumes that the
** rendered model will provide color, position and normal at the same time in a MRT fashion
*/

class FBORenderer
{
public:
  FBORenderer(const glm::ivec2& win);
  virtual ~FBORenderer();

  void start() const;

  void process() const;

  gdl::AShader* getShader() const {return _fboshader;};

protected:
  GLuint _fbo_texture_color;
  GLuint _fbo_texture_position;
  GLuint _fbo_texture_normals;
  GLuint _rbo_depth;
  GLuint _fbo;

  gdl::AShader* _fboshader;
  gdl::AShader* _rendershader;
};

#endif // FBORENDERER_H
