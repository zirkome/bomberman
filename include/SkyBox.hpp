#ifndef _SKYBOX_H_
# define _SKYBOX_H_

# include <Clock.hh>

# include "Cube6Face.hpp"

class SkyBox : public Cube6Face
{
public:
  explicit SkyBox();
  virtual ~SkyBox();

public:
  virtual void draw(gdl::AShader *shader, const gdl::Clock &clock);
};

#endif /* _SKYBOX_H_ */
