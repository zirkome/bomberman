#ifndef _SKYBOX_H_
# define _SKYBOX_H_

# include "Cube6Face.hpp"
# include "SharedPointer.hpp"
# include "Texture.hpp"

class SkyBox : public Cube6Face
{
public:
  explicit SkyBox();
  virtual ~SkyBox();

public:
  virtual void draw(gdl::AShader *shader, const gdl::Clock &clock);

private:
  SharedPointer<Texture> _texture;
};

#endif /* _SKYBOX_H_ */
