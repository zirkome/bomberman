#include <iostream>
#include <exception>
#include <stdexcept>
#include <stdlib.h>
#include <time.h>

#include "GameEngine.hpp"

int main()
{
  try
    {
      GameEngine game;

      srand(time(NULL));
      if (game.initialize() == false)
        throw std::runtime_error("Game initialization failed.");
      SharedPointer<Model> _obj = ResourceManager::getInstance()->get<Model>(RES_MODEL "bomb.fbx");
      SharedPointer<Texture> _ = ResourceManager::getInstance()->get<Texture>(RES_TEXTURE "fire.tga");
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
