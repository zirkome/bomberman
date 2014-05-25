#include "FBORenderer.hpp"

FBORenderer::FBORenderer(const glm::ivec2& win)
{
  _fbo_texture_normals = 0;
  _fbo_texture_color = 0;
  _fbo_texture_position = 0;
  _rbo_depth = 0;
  _fbo = 0;

  _fboshader = new FBOShader;

  if (!_fboshader->load(RES_SHADERS "fbo.fp", GL_FRAGMENT_SHADER)
      || !_fboshader->load(RES_SHADERS "fbo.vp", GL_VERTEX_SHADER)
      || !_fboshader->build())
    {
      throw nFault("Shader failed to init");
    }
  _fboshader->bind();

  /* Texture color*/
  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, &_fbo_texture_color);
  glBindTexture(GL_TEXTURE_2D, _fbo_texture_color);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, win.x, win.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

  /* Texture Position*/
  glActiveTexture(GL_TEXTURE1);
  glGenTextures(1, &_fbo_texture_position);
  glBindTexture(GL_TEXTURE_2D, _fbo_texture_position);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, win.x, win.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

  /* Texture Normal*/
  glActiveTexture(GL_TEXTURE2);
  glGenTextures(1, &_fbo_texture_normals);
  glBindTexture(GL_TEXTURE_2D, _fbo_texture_normals);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, win.x, win.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

  glBindTexture(GL_TEXTURE_2D, 0);

  /* Depth buffer */
  glGenRenderbuffers(1, &_rbo_depth);
  glBindRenderbuffer(GL_RENDERBUFFER, _rbo_depth);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, win.x, win.y);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);

  /* Framebuffer to link everything together */
  glGenFramebuffers(1, &_fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _fbo_texture_color, 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, _fbo_texture_position, 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, _fbo_texture_normals, 0);

  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _rbo_depth);

  GLenum buffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
  glDrawBuffers(3, buffers);

  if ((glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE)
    {
      throw nFault("Opengl Framebuffer Deffered failed to init");
    }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glActiveTexture(GL_TEXTURE0);

  _rendershader = new PanShader;

  if (!_rendershader->load(RES_SHADERS "pan.fp", GL_FRAGMENT_SHADER)
      || !_rendershader->load(RES_SHADERS "pan.vp", GL_VERTEX_SHADER)
      || !_rendershader->build())
    {
      throw nFault("Shader failed to init");
    }
  _pan = new Pan;
  _pan->initialize();
}

FBORenderer::~FBORenderer()
{
  glDeleteRenderbuffers(1, &_rbo_depth);
  glDeleteTextures(1, &_fbo_texture_color);
  glDeleteTextures(1, &_fbo_texture_position);
  glDeleteTextures(1, &_fbo_texture_normals);
  glDeleteFramebuffers(1, &_fbo);

  delete _fboshader;
}

void FBORenderer::start() const
{
  _fboshader->bind();
  glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FBORenderer::process(const glm::vec3& camPos) const
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  _rendershader->bind();

  _rendershader->setUniform("camPos", camPos);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _fbo_texture_color);
  _rendershader->setUniform("tColor", 0);

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, _fbo_texture_position);
  _rendershader->setUniform("tPosition", 1);

  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, _fbo_texture_normals);
  _rendershader->setUniform("tNormals", 2);

  glActiveTexture(GL_TEXTURE0);
  _pan->draw(_rendershader);
}
