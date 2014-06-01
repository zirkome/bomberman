#ifndef PANSHADER_H
# define PANSHADER_H

# include <AShader.hh>

class PanShader : public gdl::AShader
{
public:
  PanShader();
  virtual ~PanShader();

  virtual bool build();
protected:
};

#endif // PANSHADER_H
