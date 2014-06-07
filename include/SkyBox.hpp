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
  void update(gdl::Clock const &clock);
  void draw(gdl::AShader *shader, const gdl::Clock &clock,
            const glm::vec3& pos) const;

protected:
  SharedPointer<Texture> _texture;
  Cube6Face _cube;
};

#endif /* _SKYBOX_H_ */
