#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "Entity.h"

class Player : public Entity
{
public:
	Player(iPoint pos);
	~Player();
	bool Update(float dt);
	bool CleanUp();
private:
	void HandleInput(float dt);
};

#endif // !__PLAYER_H__
