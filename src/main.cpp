#include <iostream>
#include <exception>
#include <stdexcept>
#include <stdlib.h>
#include <time.h>
#include "LeaderScores.hpp"
#include "GameEngine.hpp"

int main()
{
  try
    {
      GameEngine game;

      LeaderScores leader("scores.txt");
      leader.pushLeader("Delafuck", 90);
      leader.writeLeader();

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
