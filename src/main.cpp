#include <iostream>
#include "Intro.hpp"

int main()
{
  Intro  intro;

  if (intro.initialize() == false)
    return (EXIT_FAILURE);
  while (intro.update() == true)
    intro.draw();
  return (0);
}
