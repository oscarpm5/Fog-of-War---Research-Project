#ifndef __FRIENDLY_H__
#define __FRIENDLY_H__
#include "Entity.h"

class Friendly: public Entity
{
public:
	Friendly(iPoint pos);
	~Friendly();
	bool Update(float dt);
	bool CleanUp();
private:
	void HandleInput(float dt);
};

#endif // !__FRIENDLY_H__
