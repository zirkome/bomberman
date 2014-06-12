#ifndef _LEADERSCORES_H_
#define _LEADERSCORES_H_

#include <string>
#include <list>
#include <sstream>
#include <fstream>
#include "Fault.hpp"

struct Leader
{
  Leader(const std::string &name, int score) {
    _name = name;
    _score = score;
  }
  std::string _name;
  int _score;
};

class LeaderScores
{
private:
  std::string _file;
  std::list<Leader> _leaders;
public:
  LeaderScores(const std::string &file);
  virtual ~LeaderScores();
  void pushLeader(const std::string &name, int score);
  const std::list<Leader> getLeader() const;
  void writeLeader() const;
  void display() const;
private:
  static bool compare(const Leader &a, const Leader &b);
};

#endif /* _LEADERSCORES_H_ */
