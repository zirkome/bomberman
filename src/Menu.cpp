#include <sstream>
#include "Menu.hpp"

Menu::Menu(PivotingCam *cam)
  : _cam(cam), _state(Running), _select(Start), _level(Medium), _map(0)
{

  _names[0] = "";
  _names[1] = "";

  _levelFile[Easy] = std::string("script/easy.lua");
  _levelFile[Medium] = std::string("script/medium.lua");
  _levelFile[Hard] = std::string("script/hard.lua");

  _mapFile.push_back(std::string("map/1.map"));
  _mapFile.push_back(std::string("map/2.map"));
  _mapFile.push_back(std::string("map/3.map"));
  _mapFile.push_back(std::string("map/4.map"));
  _mapFile.push_back(std::string("map/5.map"));
  _mapFile.push_back(std::string(""));

  _numberIa = 1;
  _numberPlayer = 1;
  _game = NULL;
  _font = new FontText(RES_TEXTURE "font.tga");

  _keyToChar[SDLK_a] = 'a';
  _keyToChar[SDLK_b] = 'b';
  _keyToChar[SDLK_c] = 'c';
  _keyToChar[SDLK_d] = 'd';
  _keyToChar[SDLK_e] = 'e';
  _keyToChar[SDLK_f] = 'f';
  _keyToChar[SDLK_g] = 'g';
  _keyToChar[SDLK_h] = 'h';
  _keyToChar[SDLK_i] = 'i';
  _keyToChar[SDLK_j] = 'j';
  _keyToChar[SDLK_k] = 'k';
  _keyToChar[SDLK_l] = 'l';
  _keyToChar[SDLK_m] = 'm';
  _keyToChar[SDLK_n] = 'n';
  _keyToChar[SDLK_o] = 'o';
  _keyToChar[SDLK_p] = 'p';
  _keyToChar[SDLK_q] = 'q';
  _keyToChar[SDLK_r] = 'r';
  _keyToChar[SDLK_s] = 's';
  _keyToChar[SDLK_t] = 't';
  _keyToChar[SDLK_u] = 'u';
  _keyToChar[SDLK_v] = 'v';
  _keyToChar[SDLK_w] = 'w';
  _keyToChar[SDLK_x] = 'x';
  _keyToChar[SDLK_y] = 'y';
  _keyToChar[SDLK_z] = 'z';

  _keyToChar[SDLK_SPACE] = ' ';

  init();
}

Menu::~Menu()
{
  delete _font;
}

void Menu::init()
{
  _ortho = glm::scale(glm::translate(glm::mat4(1), glm::vec3(-1.0, -1.0, -1.0)), glm::vec3(2.0, 2.0, 2.0));
}

Game *Menu::getGame(const glm::ivec2& dim)
{
  _state = Running;
  return new ::Game(dim, _numberPlayer, 1, _levelFile[Easy], _names, _mapFile[_map]);
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
	    {
	      _state = Name;
	      _select = Player1;
	      return true;
	    }
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
        {
          _select = (selected)(_select - 1);
          SoundManager::getInstance()->manageSound(SoundManager::SWITCH_MENU, SoundManager::PLAY);
        }
      else if (input.getKey(SDLK_DOWN, true))
        {
          _select = (selected)(_select + 1);
          SoundManager::getInstance()->manageSound(SoundManager::SWITCH_MENU, SoundManager::PLAY);
        }
      if (_select < Start)
        _select = Exit;
      if (_select > Exit)
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
        {
          _select = static_cast<selected>(_select - 1);
          SoundManager::getInstance()->manageSound(SoundManager::SWITCH_MENU, SoundManager::PLAY);
        }
      else if (input.getKey(SDLK_DOWN, true))
        {
          _select = static_cast<selected>(_select + 1);
          SoundManager::getInstance()->manageSound(SoundManager::SWITCH_MENU, SoundManager::PLAY);
        }
      else if (input.getKey(SDLK_RIGHT, true))
        {
          bool sound = false;

          if (_select == Player && _numberPlayer < 2 && (sound = true))
            _numberPlayer++;
          if (_select == Ia && (sound = true))
            _numberIa++;
          if (_select == IaFile && _level < 2 && (sound = true))
            _level = static_cast<level>(_level + 1);
          if (_select == MapFile &&  _map < 5 && (sound = true))
            _map++;
          if (sound)
            SoundManager::getInstance()->manageSound(SoundManager::SWITCH_MENU, SoundManager::PLAY);
        }
      else if (input.getKey(SDLK_LEFT, true))
        {
          bool sound = false;

          if (_select == Player && _numberPlayer > 1 && (sound = true))
            _numberPlayer--;
          if (_select == Ia && _numberIa > 0 && (sound = true))
            _numberIa--;
          if (_select == IaFile && _level > 0 && (sound = true))
            _level = static_cast<level>(_level - 1);
          if (_select == MapFile && _map > 0 && (sound = true))
            _map--;
          if (sound)
            SoundManager::getInstance()->manageSound(SoundManager::SWITCH_MENU, SoundManager::PLAY);
        }
      if (_select < Player)
        _select = Return;
      if (_select > Return)
        _select = Player;
    }
  else if (_state == Name)
    {
      if (input.getKey(SDLK_RETURN, true) && _select == Starting && validNames())
	_state = Finished;
      else if (input.getKey(SDLK_UP, true))
        {
          _select = static_cast<selected>(_select - (_numberPlayer != 2 ? 2 : 1));
          SoundManager::getInstance()->manageSound(SoundManager::SWITCH_MENU, SoundManager::PLAY);
        }
      else if (input.getKey(SDLK_DOWN, true))
        {
          _select = static_cast<selected>(_select + 1);
          SoundManager::getInstance()->manageSound(SoundManager::SWITCH_MENU, SoundManager::PLAY);
        }
      else if (_select == Player1 && _names[0].size() < 10)
	{
	  if (input.getKey(SDLK_BACKSPACE, true) && _names[0].size() > 0)
	    _names[0] = _names[0].substr(0, _names[0].size() - 1);
	  else
	    _names[0] += getAscii(input);
	}
      else if (_select == Player2 && _names[1].size() < 10)
	{
	  if (input.getKey(SDLK_BACKSPACE, true) && _names[1].size() > 0)
	    _names[1] = _names[1].substr(0, _names[1].size() - 1);
	  else
	    _names[1] += getAscii(input);
	}
      if (_select < Player1)
        _select = Starting;
      if (_select > Starting)
        _select = Player1;
      if (_select == Player2 && _numberPlayer != 2)
	_select = Starting;
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
  else if (_state == Name)
    {
      textMat = glm::translate(glm::mat4(1), glm::vec3(0.01, 0.59, 0.0));
      textMat = glm::scale(textMat, glm::vec3(0.5, 1.5, 0.0));
      _font->displayText(std::string("Player1 :") + _names[0], _select == Player1 ? glm::vec4(1.0f, 0.0f, 0.3f, 0.8f) : glm::vec4(0.3f, 0.0f, 1.0f, 0.8f), textMat, hudshader);
      if (_numberPlayer == 2)
	{
	  textMat = glm::translate(glm::mat4(1), glm::vec3(0.01, 0.39, 0.0));
	  textMat = glm::scale(textMat, glm::vec3(0.5, 1.0, 0.0));
	  _font->displayText(std::string("Player2 :") + _names[1], _select == Player2 ? glm::vec4(1.0f, 0.0f, 0.3f, 0.8f) : glm::vec4(0.3f, 0.0f, 1.0f, 0.8f), textMat, hudshader);
	}
      textMat = glm::translate(glm::mat4(1), glm::vec3(0.01, 0.19, 0.0));
      textMat = glm::scale(textMat, glm::vec3(0.5, 1.0, 0.0));
      _font->displayText(std::string("Start"), _select == Starting ? glm::vec4(1.0f, 0.0f, 0.3f, 0.8f) : glm::vec4(0.3f, 0.0f, 1.0f, 0.8f), textMat, hudshader);
    }
  /* TODO : draw the curent menu */
}

std::string Menu::getAscii(gdl::Input &input) const
{
  std::stringstream ss("");

  for (std::map<int, char>::const_iterator it = _keyToChar.begin(); it != _keyToChar.end(); ++it)
    {
      if (input.getKey(it->first, true))
	{
	  ss << it->second;
	}
    }
  return ss.str();
}

bool Menu::validNames()
{
  bool valid = false;

  for (int i = 0; i < _numberPlayer; ++i)
    {
      valid = false;
      for (unsigned int j = 0; j < _names[i].size(); ++j)
	{
	  if (_names[i][j] != ' ')
	    valid = true;
	}
      if (valid == false)
	return false;
    }
  if (_names[1] == _names[0])
    _names[1] = _names[0] + "1";
  return valid;
}
