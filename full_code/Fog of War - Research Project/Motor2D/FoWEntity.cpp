#include "FoWEntity.h"

FoWEntity::FoWEntity(bool providesVisibility):boundingBoxRadius(3),deleteEntity(false),providesVisibility(providesVisibility)
{

}


FoWEntity::~FoWEntity()
{
	CleanUp();
}


bool FoWEntity::CleanUp()
{
	bool ret = true;

	return ret;
}


void FoWEntity::SetNewPosition(iPoint pos)
{

}


void FoWEntity::SetNewVisionRadius(uint radius)
{

}
