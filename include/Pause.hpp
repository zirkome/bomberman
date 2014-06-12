#ifndef _PAUSE_H_
#define _PAUSE_H_

# include "config.h"
# include "FontText.hpp"
# include "Clock.hh"
# include "GameGeometry.hpp"
# include "SharedPointer.hpp"

class Pause
{
public:
  Pause();
  virtual ~Pause();
  int update(gdl::Input &input);
  void draw(const FontText &font, const gdl::Clock &clock, gdl::AShader *shader);
private:
  int _selected;
  int _nbLine;
  GameGeometry *_font_pan;
  SharedPointer<Texture> _transparent_texture;
  std::vector<std::string> _text;
  glm::vec4 _selectColor;
  glm::vec4 _color;
};

#endif /* _PAUSE_H_ */
