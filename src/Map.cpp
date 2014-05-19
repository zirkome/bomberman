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

Map::Map(std::string const &mapFileName) : _x(0), _y(0), _mutex(new PMutex)
{
  this->loadMapFromFile(mapFileName);
}

Map::~Map()
{
  IEntity	*entity;

  while (!_map.empty()) {
    entity = *(_map.begin());
    delete entity;
    _map.pop_front();
  }
  delete _mutex;
}

/*
** Private Methods
*/

IEntity::Type	Map::getType(const std::string::const_iterator &it) const
{
  if (*it == IEntity::S_BOX)
    return IEntity::BOX;
  if (*it == IEntity::S_WALL)
    return IEntity::WALL;
  return IEntity::GROUND;
}

bool		Map::loadMapFromFile(std::string const &fileName)
{
  std::ifstream	file(fileName.c_str());

  if (!file.is_open())
    {
      std::cerr << "Unable to load from file : " + fileName << std::endl;
      return false;
    }

  std::string	line;
  int		x = 0, y = 0;
  IEntity	*entity;

  while (std::getline(file, line)) {
    y = 0;
    for (std::string::const_iterator it = line.begin(), end = line.end();
	 it != end; ++it) {
      if ((entity = this->getEntityForMap(x, y, this->getType(it))))
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
	  entity = this->getEntityForMap(i, j, ((rand() % 10) - 3) % 10);
	  if (entity)
	    _map.push_back(entity);
	}
      }
  }
}

IEntity		*Map::getEntityForMap(const int x, const int y, const int i) const
{
  IEntity	*entity = NULL;

  entity = EntitiesFactory::getInstance()->create(static_cast<IEntity::Type>(i), x, y);
  return entity;
}

/*
** Debug methods
*/

void	Map::displayDebugMap() const
{
  // bool	check;

  // if (_map.size() > 0) {
  //   for (int i = 0; i < _x; ++i) {
  //     for (int j = 0; j < _y; ++j) {
  // 	check = false;
  // 	for (LMap::const_iterator it = _map.begin(); it != _map.end(); ++it) {
  // 	  if ((*(*it)).getPos().x == i && (*(*it)).getPos().y == j) {
  // 	    if (dynamic_cast<Box *>(*it) != NULL)
  // 	      std::cout << "o";
  // 	    else if (dynamic_cast<Wall *>(*it) != NULL)
  // 	      std::cout << "#";
  // 	    else if (dynamic_cast<Ground *>(*it) != NULL)
  // 	      std::cout << "#";
  // 	    else
  // 	      std::cout << "*";
  // 	    check = true;
  // 	  }
  // 	}
  // 	if (check == false)
  // 	  std::cout << " ";
  //     }
  //     std::cout << std::endl;
  //   }
  // }
}

/*
** Public methods
*/

Map::LMap	&Map::getMap()
{
  return _map;
}

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
  ScopeLock	lk(*_mutex);

  for (LMap::const_iterator it = _map.begin(), end = _map.end(); it != end; ++it)
    if ((*(*it)).getPos().x == x && (*(*it)).getPos().y == y)
      return *it;
  return NULL;
}

/*
** Return the Type of an Entity at coor(x, y)
*/

IEntity::Type	Map::getTypeAt(const int x, const int y) const
{
  for (LMap::const_iterator it = _map.begin(), end = _map.end(); it != end; ++it)
    if ((*(*it)).getPos().x == x && (*(*it)).getPos().y == y) {

      //TODO Get better this shit (linard_f)
      if (dynamic_cast<Box *>(*it))
	return IEntity::BOX;
      else if (dynamic_cast<Bomb *>(*it))
	return IEntity::BOMB;
      else
	return IEntity::WALL;
    }
  return IEntity::NONE;
}

/*
** Add an entity in the map if it's possible, else return false
*/

bool		Map::addEntity(IEntity *entity)
{
  ScopeLock	lk(*_mutex);

  for (LMap::const_iterator it = _map.begin(), end = _map.end(); it != end; ++it)
    if ((*(*it)).getPos().x == (*entity).getPos().x &&
	(*(*it)).getPos().y == (*entity).getPos().y)
      return false;
  _map.push_back(entity);
  return true;
}

/*
** Delete an entity in the map at coord(x, y) if it's possible, else return false
*/

bool	Map::deleteEntityAt(const int x, const int y)
{
  ScopeLock	lk(*_mutex);
  IEntity	*entity;

  for (LMap::iterator it = _map.begin(); it != _map.end(); ++it)
    if ((*(*it)).getPos().x == x && (*(*it)).getPos().y == y) {
      entity = *it;
      delete entity;
      _map.erase(it);
      return true;
    }
  return false;
}

//TODO method to get enum Type for an IEntity at (x, y)
