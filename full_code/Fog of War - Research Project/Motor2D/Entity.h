#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "p2Point.h"
#include "FoWEntity.h"

enum class ENTITY_TYPE
{
	ENEMY,
	PLAYER,
	FRIENDLY,
	UNKNOWN
};

class Entity
{
	//FUNCTIONS
public:
	Entity(ENTITY_TYPE type,iPoint pos);
	virtual ~Entity();

	virtual bool Update(float dt);
	virtual bool CleanUp();

	bool DrawEntity();
	
	//VARIABLES
public:
	bool deleteEntity;
	iPoint pos;
	FoWEntity* visionEntity=nullptr;
protected:
	ENTITY_TYPE type;
	iPoint imgOffset;
	SDL_Rect textureRect;
	

};



#endif // !__ENTITY_H__
