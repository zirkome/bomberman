#ifndef _SAVEMANAGER_H_
# define _SAVEMANAGER_H_

# include <fstream>
# include <boost/archive/binary_oarchive.hpp>
# include <boost/archive/binary_iarchive.hpp>

# include "Game.hpp"

class SaveManager
{
public:
  static void save(Game *game)
  {
    std::ofstream ofs(std::string("save_" + getDate()).c_str());

    boost::archive::binary_oarchive oa(ofs);
    oa << *game;
  }

  static void load(const std::string& filename, Game *game)
  {
    std::ifstream ifs(filename.c_str());

    boost::archive::binary_iarchive ia(ifs);
    ia >> *game;
  }
};

#endif /* _SAVEMANAGER_H_ */
