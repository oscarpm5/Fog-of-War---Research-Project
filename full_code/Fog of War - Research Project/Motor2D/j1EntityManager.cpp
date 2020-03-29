#include "j1EntityManager.h"
#include "j1App.h"
#include "j1Textures.h"
#include "p2Log.h"
#include "Player.h"
#include "Enemy.h"


j1EntityManager::j1EntityManager()
{

}


j1EntityManager::~j1EntityManager()
{
	CleanUp();
}


bool j1EntityManager::Awake(pugi::xml_node&)
{
	bool ret = true;
	return ret;
}


bool j1EntityManager::Start()
{
	bool ret = true;
	textures = App->tex->Load("textures/sprites.png");
	if (textures == NULL)
		ret = false;

	return ret;
}


bool j1EntityManager::PreUpdate()
{
	bool ret = true;

	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i]->deleteEntity)
		{
			delete entities[i];
			entities[i] = nullptr;
			entities.erase(entities.begin() + i);
			i--;
		}

	}


	return ret;
}


bool j1EntityManager::Update(float dt)
{
	bool ret = true;

	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->Update(dt);
	}


	return ret;
}


bool j1EntityManager::PostUpdate()
{
	bool ret = true;

	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->DrawEntity();
	}

	return ret;
}


bool j1EntityManager::CleanUp()
{
	bool ret = true;

	//clean the entites
	int i = 0;
	while (entities.size()>0)
	{

	
		if (entities[i]!=nullptr)
		{
			delete entities[i];
			//entities[i] = nullptr;
			entities.erase(entities.begin() + i);
			i--;
		}
		i++;
	}
	entities.clear();

	//this is in case entities are not unloaded correctly
	if (entities.size() != 0)
	{
		ret = false;
		LOG("ERROR WHEN UNLOADING ENTITIES, SOME ENTITIES HAVE NOT UNLOADED CORRECTLY");
	}
	
	//clean the textures
	if (textures != nullptr)
	{
		if (App->tex->UnLoad(textures))
			textures = nullptr;
		else ret = false;
	}

	return ret;
}

Entity* j1EntityManager::AddNewEntity(ENTITY_TYPE type, iPoint pos)
{
	Entity* entity = nullptr;
	//TODO FOR ME: whenever i add a new entity type, change this switch, also complete the cases
	switch (type)
	{
	case ENTITY_TYPE::ENEMY:
		entity = new Enemy(pos);
		break;
	case ENTITY_TYPE::PLAYER:
		entity = new Player(pos);
		break;
	case ENTITY_TYPE::UNKNOWN:

		break;
	}

	entities.push_back(entity);

	return entity;
}
