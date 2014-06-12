#include <iostream>
#include <exception>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

#include "GameEngine.hpp"

int main()
{
  try
    {
      srand(time(NULL));
      GameEngine game;

      srand(time(NULL));
      if (game.initialize() == false)
        throw std::runtime_error("Game initialization failed.");
      while (game.update() == true)
        game.draw();
      SoundManager::kill();
      MediaManager::kill();
      ResourceManager::kill();
    }
  catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
      return (1);
    }
}
