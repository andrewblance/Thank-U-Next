#ifndef __CollisionManager__
#define __CollisionManager__

#include <iostream>
#include <vector>

class Player;
class GameObject;
class TileLayer;

class CollisionManager
{
public:
    void checkPlayerTileCollision(Player* pPlayer, 
                        const std::vector<TileLayer*>& collisionLayers);
};

#endif 
