#include <iostream>
#include <exception>
#include <stdexcept>

#include "Intro.hpp"

int main()
{
  try
    {
      Intro  intro;

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
  return (0);
}
