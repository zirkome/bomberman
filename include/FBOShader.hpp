#ifndef FBOSHADER_HPP
# define FBOSHADER_HPP

# include <AShader.hh>

/*
** Class used to compile the FBO shaders
*/

class FBOShader : public gdl::AShader
{
public:
  FBOShader();
  virtual ~FBOShader();

  virtual bool build();
protected:
};

#endif // FBOSHADER_HPP
