#include <stddef.h>
#include <string>
#include <vector>

#include "Helper.hpp"

void split(const std::string& str, const std::string& delim,
           std::vector<std::string>& parts)
{
  size_t start, end = 0;

  while (end < str.size())
    {
      start = end;
      while (start < str.size()
             && (delim.find(str[start]) != std::string::npos))
        {
          start++;  // skip initial whitespace
        }
      end = start;
      while (end < str.size() && (delim.find(str[end]) == std::string::npos))
        {
          end++; // skip to end of word
        }
      if (end - start != 0)
        {
          parts.push_back(std::string(str, start, end - start));
        }
    }
}
