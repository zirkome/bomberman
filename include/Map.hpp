#ifndef MAP_HPP_
# define MAP_HPP_

# include <string>
# include <vector>
# include <iostream>
# include <cstdlib>
# include <ctime>
# include "IEntity.hpp"
# include "Wall.hpp"
# include "Box.hpp"
# include "Bomb.hpp"

class Map
{
  typedef std::vector<IEntity *> Line;
  typedef std::vector<Line> VMap;

  enum Type
    {
      BOX = 0,
      WALL = 1
    };

private:
  VMap	_map;

public:
  Map(const int x, const int y);
  Map(std::string const &mapFileName);
  ~Map();

private:
  bool		loadMapFromFile(std::string const &fileName);
  void		loadRandomMap(const int x, const int y);
  IEntity	*getEntityForMap(const int x, const int y) const;

  //Debug methods
public:
  void	displayDebugMap() const;
};

#endif /* !MAP_HPP_ */
