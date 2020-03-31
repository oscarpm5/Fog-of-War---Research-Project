#include "j1App.h"
#include "FoWManager.h"
#include "FoWEntity.h"
#include "FoWBitDefs.h"
#include "j1Map.h"

FoWEntity::FoWEntity(bool providesVisibility) :boundingBoxRadius(3), deleteEntity(false), providesVisibility(providesVisibility),posInMap({0,0}),isVisible(false)
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
	App->fowManager->MapNeedsUpdate();

}


void FoWEntity::SetNewVisionRadius(uint radius)
{
	//Changes the vision radius of the entity if there's a precomputed shape with that radius
	if (radius >= fow_MIN_CIRCLE_RADIUS && radius <= fow_MAX_CIRCLE_RADIUS)
	{
		boundingBoxRadius = radius;
		App->fowManager->MapNeedsUpdate();
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

//Applies the Mask to all tiles inside the radius
void FoWEntity::Update()
{
	if(providesVisibility)
	ApplyMaskToTiles(GetTilesInsideRadius());
}


iPoint FoWEntity::GetPos()const
{
	return posInMap;
}
