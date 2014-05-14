#include <iostream>
#include <exception>
#include <stdexcept>

#include "GameEngine.hpp"

int main()
{
  try
    {
      GameEngine intro;

      if (intro.initialize() == false)
        throw std::runtime_error("Game initialization failed.");
      while (intro.update() == true)
        intro.draw();
    }
  catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
      return (1);
    }
  // Map	map(20, 20);
  // IEntity	*entity = new Bomb(2, 2);

  // map.addEntity(entity);
  // map.displayDebugMap();
  // if (map.getEntityAt(2, 2))
  //   std::cout << "There is an obstacle" << std::endl;
}
