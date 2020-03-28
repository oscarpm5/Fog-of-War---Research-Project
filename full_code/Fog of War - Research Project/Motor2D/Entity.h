#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "p2Point.h"

enum class ENTITY_TYPE
{
	ENEMY,
	PLAYER,
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
protected:
	ENTITY_TYPE type;
	iPoint imgOffset;
	SDL_Rect textureRect;
	bool isVisible;

};



#endif // !__ENTITY_H__
