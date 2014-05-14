#ifndef MAP_HPP_
# define MAP_HPP_

# include <string>
# include <list>
# include <iostream>
# include <cstdlib>
# include <ctime>
# include "IEntity.hpp"
# include "Wall.hpp"
# include "Box.hpp"
# include "Bomb.hpp"

class Map
{
  typedef std::list<IEntity *> LMap;

private:
  int	_x;
  int	_y;
  LMap	_map;

public:
  Map(const int x, const int y);
  Map(std::string const &mapFileName);
  ~Map();
  int		getWidth() const;
  int		getLength() const;
  IEntity	*getEntityAt(const int x, const int y) const;
  bool		addEntity(IEntity *entity);

private:
  bool		loadMapFromFile(std::string const &fileName);
  void		loadRandomMap();
  IEntity	*getEntityForMap(const int x, const int y) const;

  //Debug methods
public:
  void	displayDebugMap() const;
};

#endif /* !MAP_HPP_ */
