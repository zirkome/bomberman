#include <iostream>
#include "LeaderScores.hpp"

LeaderScores::LeaderScores(const std::string &file)
  : _file(file)
{
  std::ifstream fin;
  std::string	line;

  fin.open(file.c_str());
  if (!fin.good())
    {
      throw nFault("Error while loading scores from file : " + file);
    }
  while (getline(fin, line))
    {
      std::string name, scores;
      int score_int;
      std::stringstream iss(line);

      getline(iss, name, ':');
      getline(iss, scores, '\n');

      std::stringstream ss;
      ss << scores;
      ss >> score_int;
      _leaders.push_back(Leader(name, score_int));
    }
  _leaders.sort(LeaderScores::compare);
  fin.close();
}

LeaderScores::~LeaderScores()
{
}

void LeaderScores::pushLeader(const std::string &name, int score)
{
  for (std::list<Leader>::iterator it = _leaders.begin(); it != _leaders.end(); ++it)
    {
      if ((*it)._name == name)
	{
	  _leaders.erase(it);
	}
    }
  _leaders.push_back(Leader(name, score));
  _leaders.sort(LeaderScores::compare);
}

const std::list<Leader> LeaderScores::getLeader() const
{
  return _leaders;
}

void LeaderScores::writeLeader() const
{
  std::ofstream fout;

  fout.open(_file.c_str(), std::ofstream::trunc);
  if (!fout.good())
    {
      throw nFault("Error while writing scores in file : " + _file);
    }
  for (std::list<Leader>::const_iterator it = _leaders.begin(); it != _leaders.end(); ++it)
    {
      fout << (*it)._name << ":" << (*it)._score << "\n";
    }
  fout.close();
}

bool LeaderScores::compare(const Leader &a, const Leader &b)
{
  return a._score > b._score;
}

void LeaderScores::display() const
{
  for (std::list<Leader>::const_iterator it = _leaders.begin(); it != _leaders.end(); ++it)
    {
      std::cout << (*it)._name << ":" << (*it)._score << std::endl;
    }
}
