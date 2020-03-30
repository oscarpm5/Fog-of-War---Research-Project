#include "FoWManager.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Render.h"
#include "j1Input.h"

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
	debugFoWtexture = App->tex->Load("maps/fogTilesDebug.png");

	if (smoothFoWtexture == nullptr || debugFoWtexture == nullptr);
	ret = false;

	// Initialize the map being used to translate bits to texture ID
	//Straight-forward cases
	bitToTextureTable.insert(std::pair<unsigned short, int>(fow_ALL, 0));
	bitToTextureTable.insert(std::pair<unsigned short, int>(fow_NNN, 1));
	bitToTextureTable.insert(std::pair<unsigned short, int>(fow_WWW, 2));
	bitToTextureTable.insert(std::pair<unsigned short, int>(fow_EEE, 3));
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
	bitToTextureTable.insert(std::pair<unsigned short, int>(273, 13));
	bitToTextureTable.insert(std::pair<unsigned short, int>(84, 14));
	//lines
	bitToTextureTable.insert(std::pair<unsigned short, int>(23, 1));
	bitToTextureTable.insert(std::pair<unsigned short, int>(308, 3));
	bitToTextureTable.insert(std::pair<unsigned short, int>(89, 2));
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

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		ResetFoWMap();
	}
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		debugMode = !debugMode;
		UpdateFoWMap();
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
		for (int i = 0; i < width * height; i++)
		{
			fowMap[i].tileFogBits = fow_ALL;
		}

		for (int i = 0; i < fowEntities.size(); i++)
		{
			fowEntities[i]->Update();
		}



		if (!debugMode)
		{
			for (int i = 0; i < fowEntities.size(); i++)
			{
				if (CheckTileVisibility(fowEntities[i]->GetPos()))
				{
					fowEntities[i]->isVisible = true;
				}
				else fowEntities[i]->isVisible = false;

			}
		}
		else
		{
			for (int i = 0; i < fowEntities.size(); i++)
			{
				fowEntities[i]->isVisible = true;
			}
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
			App->map->MapToWorld(x, y, worldDrawPos.x, worldDrawPos.y);

			SDL_Texture* displayFogTexture = nullptr;
			if (debugMode)
			{
				displayFogTexture = debugFoWtexture;
			}
			else displayFogTexture = smoothFoWtexture;

			//draw fog
			if (fogId != -1)
			{
				SDL_SetTextureAlphaMod(displayFogTexture, 128);//set the alpha of the texture to half to reproduce fog
				SDL_Rect r = { fogId * 64,0,64,64 }; //this rect crops the desired fog Id texture from the fogTiles spritesheet
				App->render->Blit(displayFogTexture, worldDrawPos.x, worldDrawPos.y, &r);
			}
			if (shroudId != -1)
			{
				SDL_SetTextureAlphaMod(displayFogTexture, 255);//set the alpha to white again
				SDL_Rect r = { shroudId * 64,0,64,64 }; //this rect crops the desired fog Id texture from the fogTiles spritesheet
				App->render->Blit(displayFogTexture, worldDrawPos.x, worldDrawPos.y, &r);
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


//TODO Complete the following function: it shoud return the tile visibility (true if visible, otherwise false)
bool FoWManager::CheckTileVisibility(iPoint mapPos)const
{
	bool ret = false;
	//First check if the entity is inside the map
	//& get the tile fog information to check if is visible. 
	//Note that the function that you need does both things for you, it is recommended to check and understand what the needed function does

	FoWDataStruct* tileState = GetFoWTileState(mapPos);

	if (tileState != nullptr)
	{
		//Entity will only be visible in visible areas (no fog nor shroud)
		//Think about what happens with the smooth borders, are the considered visble or fogged?
		//Also, do you need to check both the fog and shroud states?
		if (tileState->tileFogBits != fow_ALL)
			ret = true;
	}

	return ret;
}
