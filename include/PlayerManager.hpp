#ifndef PLAYERMANAGER_H
# define PLAYERMANAGER_H

# include <list>

# include <glm/glm.hpp>

# include "IEntity.hpp"
# include "ACamera.hpp"
# include "Player.hpp"

class PlayerManager
{
public:
  PlayerManager(const glm::vec2& pos, Map *map, bool first, const glm::vec4& color);
  ~PlayerManager();

  Player& getPlayer() {return _player;};
  ACamera& getCam() {return *_cam;};

  void update(const Map& map);

  const std::list<IEntity*>& getNearList() const {return _nearEntity;};

private:
  PlayerManager(const PlayerManager& p);
  void updateNearList(const Map& map);

private:
  Player _player;
  ACamera* _cam;
  int _score;
  std::list<IEntity*> _nearEntity;
};

#endif // PLAYERMANAGER_H
