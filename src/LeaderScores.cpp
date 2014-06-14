#include <iostream>
#include "LeaderScores.hpp"

LeaderScores::LeaderScores(const std::string &file)
  : _file(file)
{
  std::ifstream fin;
  std::string	line;

  fin.open(file.c_str());
  if (fin.good())
    {
      while (getline(fin, line))
	{
	  std::string name, scores;
	  std::stringstream iss(line);

	  getline(iss, name, ':');
	  getline(iss, scores, '\n');

	  _leaders.push_back(Leader(name, scores));
	}
      _leaders.sort(LeaderScores::compare);
      fin.close();
    }
}

LeaderScores::~LeaderScores()
{
}

void LeaderScores::pushLeader(const std::string &name, int score)
{
  std::stringstream iss("");

  iss << score;
  for (std::list<Leader>::iterator it = _leaders.begin(); it != _leaders.end(); ++it)
    {
      if ((*it)._name == name)
	{
	  _leaders.erase(it);
	  break;
	}
    }
  std::string score_str = iss.str();
  _leaders.push_back(Leader(name, score_str));
  _leaders.sort(LeaderScores::compare);
}

const std::list<Leader> &LeaderScores::getLeader() const
{
  return _leaders;
}

bool LeaderScores::writeLeader() const
{
  std::ofstream fout;

  fout.open(_file.c_str(), std::ofstream::trunc);
  if (!fout.good())
    {
      return false;
    }
  for (std::list<Leader>::const_iterator it = _leaders.begin(); it != _leaders.end(); ++it)
    {
      fout << (*it)._name << ":" << (*it)._score << "\n";
    }
  fout.close();
  return true;
}

bool LeaderScores::compare(const Leader &a, const Leader &b)
{
  std::istringstream buffer(a._score);
  int value;
  buffer >> value;
  std::istringstream buffer2(b._score);
  int value2;
  buffer2 >> value2;
  return value > value2;
}

void LeaderScores::display() const
{
  for (std::list<Leader>::const_iterator it = _leaders.begin(); it != _leaders.end(); ++it)
    {
      std::cout << (*it)._name << ":" << (*it)._score << std::endl;
    }
}
