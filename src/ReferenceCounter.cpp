#include "ReferenceCounter.hpp"

ReferenceCounter::ReferenceCounter()
{
}

ReferenceCounter::~ReferenceCounter()
{
}

void ReferenceCounter::addReference()
{
  _count++;
}

int ReferenceCounter::release()
{
  return --_count;
}
