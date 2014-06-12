#include "Placement.hpp"

Placement::Placement(Map *cmap)
{
  _map = cmap;
  _mapSize = _map->getDimension();
  _div = 2;
}

Placement::~Placement()
{
}

glm::ivec2 Placement::genNewPos()
{
  return(glm::ivec2(rand() % _mapSize.x, rand() % _mapSize.y));
}

bool Placement::checkSpace(glm::ivec2 const &pos, glm::ivec2 const &back, int rec)
{
  if (pos.x < 0 || pos.y < 0 || pos.x >= _mapSize.x || pos.y >= _mapSize.y || _map->getTypeAt(pos.x, pos.y) != IEntity::NONE || _map->getPlayersAt(pos.x, pos.y).size() != 0)
    return false;
  if (rec == 0)
    return true;
  if (back != glm::ivec2(pos.x, pos.y - 1) && checkSpace(glm::ivec2(pos.x, pos.y - 1), pos, rec - 1))
    return true;
  if (back != glm::ivec2(pos.x, pos.y + 1) && checkSpace(glm::ivec2(pos.x, pos.y + 1), pos, rec - 1))
    return true;
  if (back != glm::ivec2(pos.x - 1, pos.y) && checkSpace(glm::ivec2(pos.x - 1, pos.y), pos, rec - 1))
    return true;
  if (back != glm::ivec2(pos.x + 1, pos.y) && checkSpace(glm::ivec2(pos.x + 1, pos.y), pos, rec - 1))
    return true;
  return false;
}

glm::ivec2 Placement::foundCloserGoodPlace(glm::ivec2 const &pos)
{
  int rayon = 1;

  if (checkSpace(pos, pos, 2) == true)
    return pos;
  while (rayon < _mapSize.x || rayon < _mapSize.y)
    {
      if (checkSpace(glm::ivec2(pos.x - rayon, pos.y - rayon), glm::ivec2(pos.x - rayon, pos.y - rayon), 2))
        return glm::ivec2(pos.x - rayon, pos.y - rayon);
      if (checkSpace(glm::ivec2(pos.x, pos.y - rayon), glm::ivec2(pos.x, pos.y - rayon), 2))
        return glm::ivec2(pos.x, pos.y - rayon);
      if (checkSpace(glm::ivec2(pos.x + rayon, pos.y - rayon), glm::ivec2(pos.x + rayon, pos.y - rayon), 2))
        return glm::ivec2(pos.x + rayon, pos.y - rayon);
      if (checkSpace(glm::ivec2(pos.x - rayon, pos.y), glm::ivec2(pos.x - rayon, pos.y), 2))
        return glm::ivec2(pos.x - rayon, pos.y);
      if (checkSpace(glm::ivec2(pos.x + rayon, pos.y), glm::ivec2(pos.x + rayon, pos.y), 2))
        return glm::ivec2(pos.x + rayon, pos.y);
      if (checkSpace(glm::ivec2(pos.x - rayon, pos.y + rayon), glm::ivec2(pos.x - rayon, pos.y + rayon), 2))
        return glm::ivec2(pos.x - rayon, pos.y + rayon);
      if (checkSpace(glm::ivec2(pos.x, pos.y + rayon), glm::ivec2(pos.x, pos.y + rayon), 2))
        return glm::ivec2(pos.x, pos.y + rayon);
      if (checkSpace(glm::ivec2(pos.x + rayon, pos.y + rayon), glm::ivec2(pos.x + rayon, pos.y + rayon), 2))
        return glm::ivec2(pos.x + rayon, pos.y + rayon);
      rayon++;
    }
  throw nFault("No space available on the map for all players");
}

glm::vec2 Placement::getNewPos()
{
  glm::ivec2 new_pos = genNewPos();
  new_pos = foundCloserGoodPlace(new_pos);
  return glm::vec2(new_pos.x, new_pos.y);
}
