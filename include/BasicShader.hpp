#ifndef _BASIC_SHAD_H
# define _BASIC_SHAD_H

# include <AShader.hh>

class BasicShader : public gdl::AShader
{
public:
  BasicShader();
  ~BasicShader();

  virtual bool build();
};

#endif
