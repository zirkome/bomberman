#include <iostream>
#include <exception>
#include <stdexcept>

#include "GameEngine.hpp"

int main()
{
  try
    {
      GameEngine game;

      if (game.initialize() == false)
        throw std::runtime_error("Game initialization failed.");
      while (game.update() == true)
        game.draw();
    }
  catch (std::exception& e)
    {
      std::cerr << e.what() << std::endl;
      return (1);
    }
}
