#ifndef MAP_HPP_
# define MAP_HPP_

# include <stdexcept>
# include <string>
# include <list>
# include <iostream>
# include <cstdlib>
# include <ctime>
# include <map>
# include <fstream>

# include <boost/archive/text_oarchive.hpp>
# include <boost/archive/text_iarchive.hpp>
# include <boost/serialization/list.hpp>
# include <boost/serialization/vector.hpp>

# include "config.h"
# include "IEntity.hpp"
# include "Wall.hpp"
# include "Box.hpp"

# include "ScopeLock.hpp"
# include "IMutex.hpp"

class APlayer;

class Map
{
  friend class boost::serialization::access;

public:
  typedef std::list<IEntity *> LMap;
  typedef std::list<IEntity *>::iterator iterator;
  typedef std::list<IEntity *>::const_iterator const_iterator;

private:
  IMutex* _mut;

  glm::vec2	_dim;
  LMap		_map;
  LMap		_playerList;
  LMap		_updateList;
  std::map<char, IEntity::Type>	_charToIEntity;

public:
  Map(const int x, const int y);
  Map(std::string const &mapFileName);
  ~Map();

  IMutex* getMutex() const {return _mut;};
  Map::LMap	&getMap();
  Map::LMap	&getUpdateMap();
  const glm::vec2 &getDimension() const;
  IEntity	*getEntityAt(const int x, const int y) const;
  std::vector<APlayer *> const getPlayersAt(const int x, const int y) const;
  bool		addEntity(IEntity *entity);
  bool		deleteEntityAt(const int x, const int y);
  IEntity::Type	getTypeAt(const int x, const int y) const;
  Map::LMap	&getPlayerList();
  Map::iterator	begin();
  Map::const_iterator	begin() const;
  Map::iterator	playerBegin();
  Map::const_iterator	playerBegin() const;
  Map::iterator	updateBegin();
  Map::const_iterator	updateBegin() const;
  Map::iterator	end();
  Map::const_iterator	end() const;
  Map::iterator	playerEnd();
  Map::const_iterator	playerEnd() const;
  Map::iterator	updateEnd();
  Map::const_iterator	updateEnd() const;

public:
  template<class Archive>
  void serialize(Archive & ar, UNUSED const unsigned int version)
  {
    ar & _dim.x;
    ar & _dim.y;
  }

private:
  bool		loadMapFromFile(std::string const &fileName);
  void		loadRandomMap();
  IEntity::Type	getType(const char c) const;
  IEntity	*getEntityForMap(const int x, const int y, const IEntity::Type i) const;

  //Debug methods
public:
  void	displayDebugMap() const;
};

#endif /* !MAP_HPP_ */
