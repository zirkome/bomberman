#ifndef _FONTTEXT_H_
#define _FONTTEXT_H_

# include <AShader.hh>
# include <Texture.hh>
# include <iostream>
# include <string>
# include <vector>
# include <exception>
# include <stdexcept>

class FontText
{
private:
  gdl::Texture	_texture;
  GLuint	_textureID;
  GLuint        _shaderID;
  GLuint        _uniformID;
  GLuint        _vertexBuffID;
  GLuint        _UVBuffID;

public:
  FontText(const std::string &path);
  ~FontText() {};
  void displayText(const std::string &str, glm::vec2 pos, int size, gdl::AShader *shader);

};

#endif /* _FONTTEXT_H_ */
