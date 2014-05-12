#include "Map.hpp"

/*
** constructor random map
*/

Map::Map(const int x, const int y)
{
  srand(time(NULL));
  this->loadRandomMap(x, y);
}

/*
** constructor map with fileName
*/

Map::Map(std::string const &mapFileName)
{
  this->loadMapFromFile(mapFileName);
}

Map::~Map()
{
  //TODO : delete map
}

/*
** Private Methods
*/

/* TODO : Load map in file mapFileName */
bool	Map::loadMapFromFile(std::string const &fileName)
{
  return true;
}

void	Map::loadRandomMap(const int x, const int y)
{
  Line	line;

  for (int i = 0; i < x; ++i) {
    if (!i || (i == x - 1))
      for (int j = 0; j < y; ++j)
	line.push_back(NULL);
    else
      for (int j = 0; j < y; ++j) {
	if (j && (j != y - 1))
	  line.push_back(this->getEntityForMap(i, j));
	else
	  line.push_back(NULL);
      }
    _map.push_back(line);
    line.clear();
  }
}

IEntity		*Map::getEntityForMap(const int x, const int y) const
{
  IEntity	*entity = NULL;
  int		i = ((rand() % 10) - 3) % 10;

  if (i == BOX)
    entity = new Box(x, y);
  else if (i == WALL)
    entity = new Wall(x, y);
  return entity;
}

/*
** Public methods
*/

void	Map::displayDebugMap() const
{
  Line	cpy;

  for (VMap::const_iterator it = _map.begin(); it != _map.end(); ++it) {
    cpy = *it;
    for (Line::const_iterator it2 = cpy.begin(); it2 != cpy.end(); ++it2) {
      if (dynamic_cast<Box *>(*it2) != NULL)
  	std::cout << "o";
      else if (dynamic_cast<Wall *>(*it2) != NULL)
  	std::cout << "#";
      else if (dynamic_cast<Bomb *>(*it2) != NULL)
  	std::cout << "*";
      else
  	std::cout << " ";
    }
    cpy.clear();
    std::cout << std::endl;
  }
}

