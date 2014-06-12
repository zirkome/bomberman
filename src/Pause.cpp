#include "Pause.hpp"
#include "ColorManager.hpp"

Pause::Pause()
  : _selected(0), _nbLine(1)
{
  _text.push_back("Return to game");
  _text.push_back("Return to menu");
  _font_pan = new GameGeometry(ResourceManager::getInstance()->get<AGeometry>("pan.geo"));
  _font_pan->scale(glm::vec3(0.25, 0.15, 1.0));
  _font_pan->translate(glm::vec3(0.5, 0.5, 0.0));
  _transparent_texture = ResourceManager::getInstance()->get<Texture>(RES_TEXTURE "semi_transparent.tga");
  ColorManager color;
  color.newColor();
  _selectColor = color.newColor();
  _color = color.newColor();
}

Pause::~Pause()
{
  delete _font_pan;
}

// return selected line or -1 if no one selected
int Pause::update(gdl::Input &input)
{
  if (input.getKey(SDLK_UP, true))
    {
      if (_selected == 0)
        _selected = _nbLine;
      else
        _selected--;
    }
  if (input.getKey(SDLK_DOWN, true))
    {
      if (_selected == _nbLine)
        _selected = 0;
      else
        _selected++;
    }
  if (input.getKey(SDLK_RETURN, true))
    return _selected;
  return -1;
}

void Pause::draw(const FontText &font, const gdl::Clock &clock, gdl::AShader *shader) const
{
  glm::mat4 textMat;
  double line = 0.0f;

  _transparent_texture->bind();
  _font_pan->draw(shader, clock);

  textMat = glm::translate(glm::mat4(1), glm::vec3(0.335, 0.55, 0));
  textMat = glm::scale(textMat, glm::vec3(1.1, 1.2, 1.0));

  font.displayText("PAUSE", _color, textMat, shader);

  for (std::vector<std::string>::const_iterator it = _text.begin(); it != _text.end(); ++it)
    {
      textMat = glm::translate(glm::mat4(1), glm::vec3(0.35, 0.51f - line / 15.f - 0.04f, 0));
      textMat = glm::scale(textMat, glm::vec3(0.35, 0.55, 1.0));

      font.displayText((*it).c_str(), (line == _selected ? _selectColor : _color), textMat, shader);
      ++line;
    }

}
