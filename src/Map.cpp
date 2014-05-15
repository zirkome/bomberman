#include "EntitiesFactory.hpp"
#include "Map.hpp"

/*
** constructor random map
*/

Map::Map(const int x, const int y) : _x(x), _y(y), _mutex(new PMutex)
{
  srand(time(NULL));
  this->loadRandomMap();
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
  for (LMap::const_iterator it = _map.begin(); it != _map.end(); ++it)
    delete *it;
  delete _mutex;
}

/*
** Private Methods
*/

/* TODO : Load map in file mapFileName */
bool		Map::loadMapFromFile(std::string const &fileName)
{
  std::ifstream	file(fileName.c_str());

  if (!file.is_open())
    return false;

  std::string	line;
  int		x = 0, y = 0;
  IEntity	*entity;

  while (std::getline(file, line)) {
    y = 0;
    for (std::string::const_iterator it = line.begin(); it != line.end(); ++it) {
      if ((entity = this->getEntityForMap(x, y)))
	_map.push_back(entity);
      ++y;
    }
    ++x;
  }
  _y = y;
  _x = x;
  file.close();
  return true;
}

void		Map::loadRandomMap()
{
  IEntity	*entity;

  for (int i = 0; i < _x; ++i) {
    if (i && (i != _x - 1))
      for (int j = 0; j < _y; ++j) {
	if (j && (j != _y - 1)) {
	  entity = this->getEntityForMap(i, j);
	  if (entity)
	    _map.push_back(entity);
	}
      }
  }
}

IEntity		*Map::getEntityForMap(const int x, const int y) const
{
  IEntity	*entity = NULL;
  int		i = ((rand() % 10) - 3) % 10;

  if (i == IEntity::BOX)
    entity = EntitiesFactory::getInstance()->create<Box>(x, y);
  else if (i == IEntity::WALL)
    entity = EntitiesFactory::getInstance()->create<Wall>(x, y);
  return entity;
}

/*
** Debug methods
*/

void	Map::displayDebugMap() const
{
  bool	check;

  for (int i = 0; i < _x; ++i) {
    for (int j = 0; j < _y; ++j) {
      check = false;
      for (LMap::const_iterator it = _map.begin(); it != _map.end(); ++it) {
	if ((*(*it)).getPosX() == i && (*(*it)).getPosY() == j) {
	  if (dynamic_cast<Box *>(*it) != NULL)
	    std::cout << "o";
	  else if (dynamic_cast<Wall *>(*it) != NULL)
	    std::cout << "#";
	  else
	    std::cout << "*";
	  check = true;
	}
      }
      if (check == false)
	std::cout << " ";
    }
    std::cout << std::endl;
  }
}

/*
** Public methods
*/

int	Map::getWidth() const
{
  return _x;
}

int	Map::getLength() const
{
  return _y;
}

/*
** Return a pointer, or not, on an IEntity if there is one at coord(x, y)
*/

IEntity		*Map::getEntityAt(const int x, const int y) const
{
  ScopeLock	lock(*_mutex);

  for (LMap::const_iterator it = _map.begin(); it != _map.end(); ++it)
    if ((*(*it)).getPosX() == x && (*(*it)).getPosY() == y)
      return *it;
  return NULL;
}

/*
** Add an entity in the map if it's possible, else return false
*/

bool		Map::addEntity(IEntity *entity)
{
  ScopeLock	lock(*_mutex);

  for (LMap::const_iterator it = _map.begin(); it != _map.end(); ++it)
    if ((*(*it)).getPosX() == (*entity).getPosX() &&
	(*(*it)).getPosY() == (*entity).getPosY())
      return false;
  _map.push_back(entity);
  return true;
}
