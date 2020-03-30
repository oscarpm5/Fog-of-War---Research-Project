#include "j1App.h"
#include "FoWManager.h"
#include "FoWEntity.h"
#include "FoWBitDefs.h"
#include "j1Map.h"

FoWEntity::FoWEntity(bool providesVisibility) :boundingBoxRadius(3), deleteEntity(false), providesVisibility(providesVisibility),posInMap({0,0})
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
	App->map->WorldToMap(pos.x, pos.y, posInMap.x, posInMap.y);
	App->fowManager->UpdateFoWMap();

}


void FoWEntity::SetNewVisionRadius(uint radius)
{
	if (radius >= fow_MIN_CIRCLE_RADIUS && radius <= fow_MAX_CIRCLE_RADIUS)
	{
		boundingBoxRadius = radius;
	}
}

std::vector<iPoint> FoWEntity::GetTilesInsideRadius()const
{
	std::vector<iPoint> ret;
	int length = (boundingBoxRadius * 2) + 1;
	iPoint startingPos = posInMap - boundingBoxRadius;
	iPoint finishingPos = startingPos + length;

	//Creates a vector with all the tiles inside a bounding box delimited by the radius
	for (int i = startingPos.y; i < finishingPos.y; i++)
	{
		for (int j = startingPos.x; j < finishingPos.x; j++)
		{
				ret.push_back({ j,i });
		}
	}

	return ret;
}


void FoWEntity::ApplyMaskToTiles(std::vector<iPoint>tilesAffected)
{

	//We first take the correct precomputed mask
	unsigned short* precMask = &App->fowManager->circleMasks[boundingBoxRadius - fow_MIN_CIRCLE_RADIUS][0];

	for (int i = 0; i < tilesAffected.size(); i++)
	{
		//We then take the fog & shroud values of each affected tile
		FoWDataStruct* tileValue = App->fowManager->GetFoWTileState(tilesAffected[i]);

		//And bitwise AND them with the mask
		if (tileValue != nullptr)
		{
			tileValue->tileShroudBits &= *precMask;
			tileValue->tileFogBits &= *precMask;
		}
		precMask++;
	}

}

//Applies the Mask to all tiles inside teh radius
void FoWEntity::Update()
{
	ApplyMaskToTiles(GetTilesInsideRadius());
}


//TODO FOR ME: consider puting this function as a FoW manager one (less cache miss)
//TODO Complete the following function: it shoud update the entity visibility accordingly (there is a bool variable for it)
void FoWEntity::UpdateEntityVisibility()
{
	//First check if the entity is inside the map
	//& get the tile fog information to check if player is visible. 
	//Note that the function that you need does both things for you, it is recommended to check and understand what the needed function does
	
	FoWDataStruct* tileState = App->fowManager->GetFoWTileState(posInMap);

	if (tileState != nullptr)
	{
		//Entity will only be visible in visible areas (no fog nor shroud)
		//Think about what happens with the smooth borders, are the considered visble or fogged?
		if (tileState->tileFogBits != fow_ALL)
			isVisible = true;
		else isVisible = false;
	}

}


