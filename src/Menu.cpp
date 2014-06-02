#include <sstream>
#include "Menu.hpp"

Menu::Menu(PivotingCam *cam)
  : _cam(cam), _state(Running), _select(Start), _level(Medium), _map(0)
{
  _levelFile[Easy] = std::string("script/easy.lua");
  _levelFile[Medium] = std::string("script/medium.lua");
  _levelFile[Hard] = std::string("script/hard.lua");

  _mapFile.push_back(std::string("map/1.map"));
  _mapFile.push_back(std::string("map/2.map"));
  _mapFile.push_back(std::string("map/3.map"));
  _mapFile.push_back(std::string("map/4.map"));
  _mapFile.push_back(std::string("map/5.map"));
  _mapFile.push_back(std::string(""));

  _numberIa = 0;
  _numberPlayer = 1;
  _game = NULL;
  _font = new FontText(RES_TEXTURE "font.tga");
  init();
}

Menu::~Menu()
{
}

void Menu::init()
{
  _ortho = glm::scale(glm::translate(glm::mat4(1), glm::vec3(-1.0, -1.0, -1.0)), glm::vec3(2.0, 2.0, 2.0));
}

Game *Menu::getGame()
{
  return new ::Game(glm::ivec2(1024, 900), _numberPlayer, _numberIa, _levelFile[_level], _mapFile[_map]);

}

bool Menu::finish() const
{
  if (_state == Finished)
    return true;
  return false;
}

bool Menu::updateMenu(gdl::Input &input, UNUSED const gdl::Clock &clock)
{
  if (_state == Running)
    {
      if (input.getKey(SDLK_RETURN, true))
	{
	  if (_select == Start)
	    _state = Finished;
	  else if (_select == Exit)
	    return false;
	  else if (_select == Options)
	    {
	      _select = Player;
	      _state = Option;
	      return true;
	    }
	}
      else if (input.getKey(SDLK_UP, true))
	_select = (selected)(_select - 1);
      else if (input.getKey(SDLK_DOWN, true))
	_select = (selected)(_select + 1);
      if (_select < 0)
	_select = Exit;
      if (_select > 2)
	_select = Start;
    }
  else if (_state == Option)
    {
      if (input.getKey(SDLK_RETURN, true) && _select == Return)
	{
	  _select = Options;
	  _state = Running;
	  return true;
	}
      else if (input.getKey(SDLK_UP, true))
	_select = static_cast<selected>(_select - 1);
      else if (input.getKey(SDLK_DOWN, true))
	_select = static_cast<selected>(_select + 1);
      else if (input.getKey(SDLK_RIGHT, true))
	{
	  if (_select == Player)
	    _numberPlayer++;
	  if (_select == Ia)
	    _numberIa++;
	  if (_select == IaFile && _level < 2)
	    _level = static_cast<level>(_level + 1);
	  if (_select == MapFile &&  _map < 5)
	    _map++;
	}
      else if (input.getKey(SDLK_LEFT, true))
	{
	  if (_select == Player && _numberPlayer > 0)
	    _numberPlayer--;
	  if (_select == Ia && _numberIa > 0)
	    _numberIa--;
	  if (_select == IaFile && _level > 0)
	    _level = static_cast<level>(_level - 1);
	  if (_select == MapFile && _map > 0)
	    _map--;
	}
      if (_select < 3)
	_select = Return;
      if (_select > 7)
	_select = Player;
    }
  return true;
}

void Menu::drawMenu(UNUSED gdl::Clock const &clock, gdl::AShader* hudshader) const
{
  glm::mat4 textMat = glm::translate(glm::mat4(1), glm::vec3(0.01f, 0.6f, 0.0f));
  std::stringstream ss;

  hudshader->setUniform("view", _ortho);
  hudshader->setUniform("projection", glm::mat4(1));
  if (_state == Running)
    {
      textMat = glm::translate(glm::mat4(1), glm::vec3(0.3, 0.59, 0.0));
      textMat = glm::scale(textMat, glm::vec3(1.5, 1.5, 0.0));
      _font->displayText(std::string("Start"), _select == Start ? glm::vec4(1.0f, 0.0f, 0.3f, 0.8f) : glm::vec4(0.3f, 0.0f, 1.0f, 0.8f), textMat, hudshader);
      textMat = glm::translate(glm::mat4(1), glm::vec3(0.3, 0.39, 0.0));
      textMat = glm::scale(textMat, glm::vec3(1.5, 1.0, 0.0));
      _font->displayText(std::string("Options"), _select == Options ? glm::vec4(1.0f, 0.0f, 0.3f, 0.8f) : glm::vec4(0.3f, 0.0f, 1.0f, 0.8f), textMat, hudshader);
      textMat = glm::translate(glm::mat4(1), glm::vec3(0.3, 0.19, 0.0));
      textMat = glm::scale(textMat, glm::vec3(1.5, 1.0, 0.0));
      _font->displayText(std::string("Exit"), _select == Exit ? glm::vec4(1.0f, 0.0f, 0.3f, 0.8f) : glm::vec4(0.3f, 0.0f, 1.0f, 0.8f), textMat, hudshader);
    }
  else if (_state == Option)
    {
      textMat = glm::translate(glm::mat4(1), glm::vec3(0.3, 0.59, 0.0));
      textMat = glm::scale(textMat, glm::vec3(1.5, 1.5, 0.0));
      _font->displayText(std::string("Options"), glm::vec4(0.3f, 0.0f, 1.0f, 0.8f), textMat, hudshader);
      ss << "Number of Player :\t<" << _numberPlayer << ">";
      textMat = glm::translate(glm::mat4(1), glm::vec3(0.15, 0.39, 0.0));
      textMat = glm::scale(textMat, glm::vec3(0.5, 1.0, 0.0));
      _font->displayText(ss.str(), _select == Player ? glm::vec4(1.0f, 0.0f, 0.3f, 0.8f) : glm::vec4(0.3f, 0.0f, 1.0f, 0.8f), textMat, hudshader);
      ss.str("");
      ss << "Number of IA :\t\t\t\t\t<" << _numberIa << ">";
      textMat = glm::translate(glm::mat4(1), glm::vec3(0.15, 0.30, 0.0));
      textMat = glm::scale(textMat, glm::vec3(0.5, 1.0, 0.0));
      _font->displayText(ss.str(), _select == Ia ? glm::vec4(1.0f, 0.0f, 0.3f, 0.8f) : glm::vec4(0.3f, 0.0f, 1.0f, 0.8f), textMat, hudshader);
      ss.str("");
      ss << "IA Level :\t\t\t\t\t\t\t\t\t<" << (_level == 0 ? "Easy" : _level == 1 ? "Medium" : "Hard") << ">";
      textMat = glm::translate(glm::mat4(1), glm::vec3(0.15, 0.21, 0.0));
      textMat = glm::scale(textMat, glm::vec3(0.5, 1.0, 0.0));
      _font->displayText(ss.str(), _select == IaFile ? glm::vec4(1.0f, 0.0f, 0.3f, 0.8f) : glm::vec4(0.3f, 0.0f, 1.0f, 0.8f), textMat, hudshader);
      ss.str("");
      if (_map == 5)
	ss << "Map :\t\t\t\t\t\t\t\t\t\t\t\t\t\t<" << "Random" << ">";
      else
	ss << "Map :\t\t\t\t\t\t\t\t\t\t\t\t\t\t<" << _map + 1 << ">";
      textMat = glm::translate(glm::mat4(1), glm::vec3(0.15, 0.12, 0.0));
      textMat = glm::scale(textMat, glm::vec3(0.5, 1.0, 0.0));
      _font->displayText(ss.str(), _select == MapFile ? glm::vec4(1.0f, 0.0f, 0.3f, 0.8f) : glm::vec4(0.3f, 0.0f, 1.0f, 0.8f), textMat, hudshader);
      textMat = glm::translate(glm::mat4(1), glm::vec3(0.15, 0.03, 0.0));
      textMat = glm::scale(textMat, glm::vec3(0.5, 1.0, 0.0));
      _font->displayText(std::string("Return"), _select == Return ? glm::vec4(1.0f, 0.0f, 0.3f, 0.8f) : glm::vec4(0.3f, 0.0f, 1.0f, 0.8f), textMat, hudshader);
    }
  /* TODO : draw the curent menu */
}
