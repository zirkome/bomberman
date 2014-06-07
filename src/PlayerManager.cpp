#include "PlayerManager.hpp"

#include "BasicCam.hpp"

PlayerManager::PlayerManager(const glm::vec2& pos, Map *map)
  : _player(pos, map)
{
  _score = 0;
  glm::vec2 playerPos = _player.getPos();
  _cam = new BasicCam(glm::vec3(playerPos.x, playerPos.y, 0), 10, 3);
}

PlayerManager::~PlayerManager()
{
  delete _cam;
}

void PlayerManager::update(const Map& map)
{
  glm::vec2 playerPos = _player.getPos();

  if (_player.getStatus() != IEntity::DESTROY)
    _cam->update(glm::vec3(playerPos.x, playerPos.y, 0));
  updateNearList(map);
}

void PlayerManager::updateNearList(const Map& map)
{
  _nearEntity.clear();

  glm::vec2 posPlayer = _player.getPos();
  glm::vec2 posObject(0, 0);
  int rayon = 9;

  for (Map::const_iterator it = map.begin(), end = map.end();
       it != end; ++it)
    {
      posObject = (*it)->getPos();
      if ((posObject.x < posPlayer.x + rayon && posObject.x > posPlayer.x - rayon && posObject.y < posPlayer.y + rayon && posObject.y > posPlayer.y - rayon))
        _nearEntity.push_front((*it));
    }

  for (Map::const_iterator it = map.playerBegin(), end = map.playerEnd();
       it != end; ++it)
    {
      posObject = (*it)->getPos();
      if ((posObject.x < posPlayer.x + rayon && posObject.x > posPlayer.x - rayon && posObject.y < posPlayer.y + rayon && posObject.y > posPlayer.y - rayon))
        _nearEntity.push_front((*it));
    }
}
