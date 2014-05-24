#include "Placement.hpp"

Placement::Placement(Map *cmap)
{
  _map = cmap;
  _mapSize = glm::vec2(_map->getWidth(), _map->getLength());
  _numberPlayer = 0;
  _div = 2;
}

Placement::~Placement()
{
}

glm::vec2 const Placement::genNewPos()
{
  _numberPlayer++;
  switch (_numberPlayer)
    {
    case 1:
      return glm::vec2(0, 0);
    case 2:
      return glm::vec2(_mapSize);
    case 3:
      return glm::vec2(_mapSize.x, 0);
    case 4:
      return glm::vec2(0, _mapSize.y);
    default:
      switch (_numberPlayer % 5)
	{
	case 0:
	  return glm::vec2(_mapSize.x / _div, 0);
	case 1:
	  return glm::vec2(0, _mapSize.y / _div);
	case 2:
	  return glm::vec2(_mapSize.x / _div, _mapSize.y);
	case 3:
	  return glm::vec2(_mapSize.x, _mapSize.y / _div);
	default:
	  {
	    return glm::vec2(_mapSize.x / _div, _mapSize.y / _div);
	    _div *= 2;
	  }
	}
    }
}

bool Placement::checkSpace(glm::vec2 const &pos, glm::vec2 const &back, int rec)
{
  if (pos.x < 0 || pos.y < 0 || _map->getTypeAt(pos.x, pos.y) != IEntity::NONE)
    return false;
  if (rec == 0)
    return true;
  if (back != glm::vec2(pos.x, pos.y - 1) && checkSpace(glm::vec2(pos.x, pos.y - 1), pos, rec - 1))
    return true;
  if (back != glm::vec2(pos.x, pos.y + 1) && checkSpace(glm::vec2(pos.x, pos.y + 1), pos, rec - 1))
    return true;
  if (back != glm::vec2(pos.x - 1, pos.y) && checkSpace(glm::vec2(pos.x - 1, pos.y), pos, rec - 1))
    return true;
  if (back != glm::vec2(pos.x + 1, pos.y) && checkSpace(glm::vec2(pos.x + 1, pos.y), pos, rec - 1))
    return true;
  return false;
}

glm::vec2 const Placement::foundCloserGoodPlace(glm::vec2 const &pos)
{
  int rayon = 1;

  if (checkSpace(pos, pos, 2) == true)
    return pos;
  while (rayon < _mapSize.x || rayon < _mapSize.y)
    {
      if (checkSpace(glm::vec2(pos.x - rayon, pos.y - rayon), glm::vec2(pos.x - rayon, pos.y - rayon), 2))
	return glm::vec2(pos.x - rayon, pos.y - rayon);
      if (checkSpace(glm::vec2(pos.x, pos.y - rayon), glm::vec2(pos.x, pos.y - rayon), 2))
	return glm::vec2(pos.x, pos.y - rayon);
      if (checkSpace(glm::vec2(pos.x + rayon, pos.y - rayon), glm::vec2(pos.x + rayon, pos.y - rayon), 2))
	return glm::vec2(pos.x + rayon, pos.y - rayon);
      if (checkSpace(glm::vec2(pos.x - rayon, pos.y), glm::vec2(pos.x - rayon, pos.y), 2))
	return glm::vec2(pos.x - rayon, pos.y);
      if (checkSpace(glm::vec2(pos.x + rayon, pos.y), glm::vec2(pos.x + rayon, pos.y), 2))
	return glm::vec2(pos.x + rayon, pos.y);
      if (checkSpace(glm::vec2(pos.x - rayon, pos.y + rayon), glm::vec2(pos.x - rayon, pos.y + rayon), 2))
	return glm::vec2(pos.x - rayon, pos.y + rayon);
      if (checkSpace(glm::vec2(pos.x, pos.y + rayon), glm::vec2(pos.x, pos.y + rayon), 2))
	return glm::vec2(pos.x, pos.y + rayon);
      if (checkSpace(glm::vec2(pos.x + rayon, pos.y + rayon), glm::vec2(pos.x + rayon, pos.y + rayon), 2))
	return glm::vec2(pos.x + rayon, pos.y + rayon);
      rayon++;
    }
  throw nFault("No space available on the map for all players");
}

glm::vec2 const Placement::getNewPos()
{
  return foundCloserGoodPlace(genNewPos());
}
