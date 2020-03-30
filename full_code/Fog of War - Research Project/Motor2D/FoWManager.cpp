#include "FoWManager.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Render.h"

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

	smoothFoWtexture = App->tex->Load("maps/fogTiles.png");
	if (smoothFoWtexture == nullptr);
	ret = false;

	// Initialize the map being used to translate bits to texture ID
	//Straight-forward cases
	bitToTextureTable.insert(std::pair<unsigned short, int>(fow_ALL, 0));
	bitToTextureTable.insert(std::pair<unsigned short, int>(fow_NNN, 1));

	bitToTextureTable.insert(std::pair<unsigned short, int>(fow_EEE, 2));
	bitToTextureTable.insert(std::pair<unsigned short, int>(fow_WWW, 3));
	bitToTextureTable.insert(std::pair<unsigned short, int>(fow_SSS, 4));
	bitToTextureTable.insert(std::pair<unsigned short, int>(fow_CNW, 5));
	bitToTextureTable.insert(std::pair<unsigned short, int>(fow_CSE, 6));
	bitToTextureTable.insert(std::pair<unsigned short, int>(fow_CNE, 7));
	bitToTextureTable.insert(std::pair<unsigned short, int>(fow_CSW, 8));
	bitToTextureTable.insert(std::pair<unsigned short, int>(fow_JNE, 9));
	bitToTextureTable.insert(std::pair<unsigned short, int>(fow_JSW, 10));
	bitToTextureTable.insert(std::pair<unsigned short, int>(fow_JNW, 11));
	bitToTextureTable.insert(std::pair<unsigned short, int>(fow_JSE, 12));

	//more complicated cases (combinations)
	//diagonals
	bitToTextureTable.insert(std::pair<unsigned short, int>(20, 9));
	bitToTextureTable.insert(std::pair<unsigned short, int>(80, 10));
	bitToTextureTable.insert(std::pair<unsigned short, int>(17, 11));
	bitToTextureTable.insert(std::pair<unsigned short, int>(272, 12));
	bitToTextureTable.insert(std::pair<unsigned short, int>(84, 13));
	bitToTextureTable.insert(std::pair<unsigned short, int>(273, 14));
	//lines
	bitToTextureTable.insert(std::pair<unsigned short, int>(23, 1));
	bitToTextureTable.insert(std::pair<unsigned short, int>(308, 2));
	bitToTextureTable.insert(std::pair<unsigned short, int>(89, 3));
	bitToTextureTable.insert(std::pair<unsigned short, int>(464, 4));
	//joints
	bitToTextureTable.insert(std::pair<unsigned short, int>(6, 9));
	bitToTextureTable.insert(std::pair<unsigned short, int>(36, 9));
	bitToTextureTable.insert(std::pair<unsigned short, int>(72, 10));
	bitToTextureTable.insert(std::pair<unsigned short, int>(192, 10));
	bitToTextureTable.insert(std::pair<unsigned short, int>(3, 11));
	bitToTextureTable.insert(std::pair<unsigned short, int>(9, 11));
	bitToTextureTable.insert(std::pair<unsigned short, int>(384, 12));
	bitToTextureTable.insert(std::pair<unsigned short, int>(288, 12));
	//corners
	bitToTextureTable.insert(std::pair<unsigned short, int>(4, 9));
	bitToTextureTable.insert(std::pair<unsigned short, int>(64, 10));
	bitToTextureTable.insert(std::pair<unsigned short, int>(1, 11));
	bitToTextureTable.insert(std::pair<unsigned short, int>(256, 12));
	//end of map initialization



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
	DrawFoWMap();
	return ret;
}


bool FoWManager::CleanUp()
{
	bool ret = true;

	return ret;
}


void FoWManager::ResetFoWMap()
{
	memset(fowMap, NULL, width * height);

	for (int i = 0; i < width * height; i++)
	{
		fowMap[i].tileShroudBits = fow_ALL;
		fowMap[i].tileFogBits = fow_ALL;
	}

}


FoWDataStruct* FoWManager::GetFoWTileState(iPoint mapPos)const
{
	FoWDataStruct* ret = nullptr;
	if (CheckFoWTileBoundaries(mapPos))
	{
		ret = &fowMap[(mapPos.y * width) + mapPos.x];
	}

	return ret;
}


bool FoWManager::CheckFoWTileBoundaries(iPoint mapPos)const
{
	bool ret = false;
	if (mapPos.x >= 0 && mapPos.x < width && mapPos.y >= 0 && mapPos.y < height)
		ret = true;

	return ret;
}

void FoWManager::CreateFoWMap(uint w, uint h)
{
	width = w;
	height = h;

	DeleteFoWMap();

	fowMap = new FoWDataStruct[width * height];

	ResetFoWMap();
}


void FoWManager::DeleteFoWMap()
{
	if (fowMap != nullptr)
	{
		RELEASE_ARRAY(fowMap);
		fowMap = nullptr;
	}
}


void FoWManager::UpdateFoWMap()
{
	if (fowMap != nullptr)
	{
		EraseVisibleFoW();
		for (int i = 0; i < fowEntities.size(); i++)
		{
			fowEntities[i]->Update();
		}
	}
}

void FoWManager::DrawFoWMap()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			FoWDataStruct* tileInfo = GetFoWTileState({ x, y });
			int fogId = -1;
			int shroudId = -1;

			if (tileInfo != nullptr)
			{

				if (bitToTextureTable.find(tileInfo->tileFogBits) != bitToTextureTable.end())
				{
					fogId = bitToTextureTable[tileInfo->tileFogBits];
				}

				if (bitToTextureTable.find(tileInfo->tileShroudBits) != bitToTextureTable.end())
				{
					shroudId = bitToTextureTable[tileInfo->tileShroudBits];
				}

			}

			iPoint worldDrawPos;
			App->map->MapToWorld(x,y,worldDrawPos.x,worldDrawPos.y);

			//draw fog
			if (fogId != -1)
			{
				SDL_SetTextureAlphaMod(smoothFoWtexture, 128);//set the alpha of the texture to half to reproduce fog
				SDL_Rect r = { fogId * 64,0,64,64 }; //this rect crops the desired fog Id texture from the fogTiles spritesheet
				App->render->Blit(smoothFoWtexture, worldDrawPos.x, worldDrawPos.y, &r);
			}
			if (shroudId != -1)
			{
				SDL_SetTextureAlphaMod(smoothFoWtexture, 255);//set the alpha to white again
				SDL_Rect r = { shroudId * 64,0,64,64 }; //this rect crops the desired fog Id texture from the fogTiles spritesheet
				App->render->Blit(smoothFoWtexture, worldDrawPos.x, worldDrawPos.y, &r);
			}



		}
	}
}


FoWEntity* FoWManager::CreateFoWEntity(iPoint pos, bool providesVisibility)
{
	FoWEntity* entity = nullptr;

	entity = new FoWEntity(providesVisibility);

	if (entity != nullptr)
	{
		fowEntities.push_back(entity);
		entity->SetNewPosition(pos);
	}

	return entity;
}


void FoWManager::EraseVisibleFoW()
{
	for (int i = 0; i < fowEntities.size(); i++)
	{
		std::vector<iPoint> toErase = fowEntities[i]->GetTilesInsideRadius();
		for (int j = 0; j < toErase.size(); j++)
		{
			GetFoWTileState(toErase[j])->tileFogBits = fow_ALL;
		}
	}
}

