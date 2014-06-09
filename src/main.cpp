#include <iostream>
#include <exception>
#include <stdexcept>

#include "GameEngine.hpp"

/* initialize the number of instance Player to know if it's the first player or not */
int Player::_nb = 0;

int main()
{
  try
    {
      GameEngine game;

      if (game.initialize() == false)
        throw std::runtime_error("Game initialization failed.");
      while (game.update() == true)
        game.draw();
      SoundManager::kill();
      PreLoader::kill();
      MediaManager::kill();
      ResourceManager::kill();
    }
  catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
      return (1);
    }
}
