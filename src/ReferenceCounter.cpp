#include "ReferenceCounter.hpp"

ReferenceCounter::ReferenceCounter()
  : _count(0)
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
