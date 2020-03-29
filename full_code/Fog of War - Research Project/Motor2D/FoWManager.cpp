#include "FoWManager.h"
#include "j1App.h"
#include "j1Textures.h"

FoWManager::FoWManager()
{

}


FoWManager::~FoWManager()
{

}


bool FoWManager::Awake(pugi::xml_node&)
{
	bool ret = true;

	return ret;
}


bool FoWManager::Start()
{
	bool ret = true;

	smoothFoWtexture= App->tex->Load("maps/fogTiles.png");
	if (smoothFoWtexture == nullptr);
	ret = false;




	return ret;
}


bool FoWManager::PreUpdate()
{
	bool ret = true;

	for (int i = 0; i < fowEntities.size(); i++)
	{
		if (fowEntities[i]->deleteEntity)
		{
			delete fowEntities[i];
			fowEntities[i] = nullptr;
			fowEntities.erase(fowEntities.begin() + i);
			i--;
		}

	}

	return ret;
}


bool FoWManager::Update(float dt)
{
	bool ret = true;

	return ret;
}


bool FoWManager::PostUpdate()
{
	bool ret = true;

	return ret;
}


bool FoWManager::CleanUp()
{
	bool ret = true;

	return ret;
}


void FoWManager::ResetFoWMap()
{

}


FoWDataStruct* FoWManager::GetFoWTileState(iPoint mapPos)const
{
	FoWDataStruct* ret = nullptr;

	return ret;
}