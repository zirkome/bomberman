#include "BasicShader.hpp"

BasicShader::BasicShader()
{
}

BasicShader::~BasicShader()
{
}

bool BasicShader::build()
{
  bool ret;
  _build();
  _bindAttribLocation(0, "vPosition");
  _bindAttribLocation(1, "vColor");
  _bindAttribLocation(2, "vNormal");
  _bindAttribLocation(3, "vTexCoord");
  ret = _linkProgram();
  if (ret)
  {
    _bindTextureUnit(0, "fTexture0");
    _bindTextureUnit(1, "fTexture1");
  }
  return (ret);
}
