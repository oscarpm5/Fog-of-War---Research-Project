#ifndef __FOW_ENTITY_H__
#define __FOW_ENTITY_H__
#include "p2Point.h"

class FoWEntity
{
	//FUNCTIONS
public:
	//TODO FOR ME: the costructor will be given a radius in the future to generate the mask
	FoWEntity(bool providesVisibility);
	~FoWEntity();

	bool CleanUp();
	//Changes the position to the given one in world coordinates
	void SetNewPosition(iPoint pos);

	void SetNewVisionRadius(uint radius);

	//VARIABLES
public:
	bool deleteEntity;
private:
	iPoint posInMap;

	bool providesVisibility;

	//Max radius from the entity at which tiles are affected (square to be checked)
	uint boundingBoxRadius;
};

#endif // !__FOW_ENTITY_H__
