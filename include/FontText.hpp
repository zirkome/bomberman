#ifndef _FONTTEXT_H_
# define _FONTTEXT_H_

# include <iostream>
# include <string>
# include <vector>
# include <exception>
# include <stdexcept>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>

# include <AShader.hh>
# include <Texture.hh>

class FontText
{
private:
  gdl::Texture	_texture;
  GLuint	_textureID;
  GLuint        _shaderID;
  GLuint        _uniformID;
  GLuint        _vertexBuffID;
  GLuint        _UVBuffID;
  const int	_sizeCharPix;

public:
  FontText(const std::string &path, int sizeCharPix = 16);
  ~FontText() {};
  void displayText(const std::string &str, const glm::vec4& color,
                   const glm::mat4 &matrice, gdl::AShader *shader) const;

};

#endif /* _FONTTEXT_H_ */
