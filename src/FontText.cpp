#include "FontText.hpp"

FontText::FontText(const gdl::Texture &texture, int c_width, int c_height) : _texture(texture)
{
  _img_height = texture.getWidth();
  _img_width = texture.getHeight();
  _c_height = c_height;
  _c_width = c_width;
  _c_by_row = _img_width / _c_width;
}

void FontText::drawText(int x, int y, int w, int h, std::string const &text)
{
  glLoadIdentity();
  glTranslatef(x, y, 0.0f);
  _texture.bind();
  glBegin(GL_QUADS);

  //character location and dimensions
  GLfloat cx = 0.0f;
  GLfloat cy = 0.0f;
  GLfloat cw = float(w);
  GLfloat ch = float(h);

  //calculate how wide each character is in term of texture coords
  GLfloat dtx = float(_c_width)/float(_img_width);
  GLfloat dty = float(_c_height)/float(_img_height);

  const char *str = text.c_str();
  for (int i = 0; char c = str[i]; i++, cx += cw) {
    // subtract the value of the first char in the character map
    // to get the index in our map
    int index = c - '0';
    int row = index / _c_by_row;
    int col = index % _c_by_row;

    // if (index < 0)
    //   throw GameException(__FILE__, __LINE__, "Character outside of font");

    // find the texture coords
    GLfloat tx = float(col * _c_width) / float(_img_width);
    GLfloat ty = float(row * _c_height) / float(_img_height);

    glTexCoord2d(tx,ty); glVertex2f(cx,cy);
    glTexCoord2d(tx+dtx,ty); glVertex2f(cx+cw,cy);
    glTexCoord2d(tx+dtx,ty+dty); glVertex2f(cx+cw,cy+ch);
    glTexCoord2d(tx,ty+dty); glVertex2f(cx,cy+ch);
  }
  glEnd();
}
