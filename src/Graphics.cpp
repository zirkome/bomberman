#include "Graphics.hpp"

Graphics::Graphics()
{
  _shader = NULL;
}

Graphics::~Graphics()
{
  delete _shader;
}

bool Graphics::init()
{
  _shader = new gdl::BasicShader;
  // pour creer un shader :
  // (un shader est un programe exectue par la carte graphique pour dessiner les pixels a l'ecan
  if (!_shader->load("./shaders/basic.fp", GL_FRAGMENT_SHADER) // le fragment shader se charge de dessiner les pixels
      || !_shader->load("./shaders/basic.vp", GL_VERTEX_SHADER) // le vertex shader s'occupe de projeter les points sur l'ecran
      || !_shader->build()) // il faut ensuite builder son shader
    {
      std::cout << "load shader fail" << std::endl;
      return false;
    }
  // pour utiliser un shader (pour que ce soit ce dernier qui dessine la geometrie) il faut le binder.
  // Un seul shader peut etre actif en mm temps
  _shader->bind();


  glEnable(GL_DEPTH_TEST);
  glClearDepth(1.0f);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  return true;
}

gdl::AShader	*Graphics::getShader() const
{
  return _shader;
}
