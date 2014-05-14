#include <Texture.hh>
#include <iostream>
#include <string>

class FontText
{
private:
  const gdl::Texture	_texture;
  GLuint		_img_width;
  GLuint		_img_height;
  GLuint		_c_width;
  GLuint		_c_height;
  GLint  		_c_by_row;
public:
  FontText(const gdl::Texture &texture, int c_width, int c_height);
  virtual ~FontText() {}
  void drawText(int x, int y, int w, int h, std::string const &text);
};
