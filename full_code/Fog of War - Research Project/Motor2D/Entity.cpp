#include "Entity.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1EntityManager.h"

Entity::Entity(ENTITY_TYPE type, iPoint pos) :type(type), pos(pos),deleteEntity(false),imgOffset({0,0}),textureRect({0,0,0,0}),isVisible(true)
{

}


Entity::~Entity()
{

}


bool Entity::CleanUp()
{
	return true;
}


bool Entity::Update(float dt)
{
	return true;
}

bool Entity::DrawEntity()
{
	//TODO FOR ME: Complete the blit function with the texture from the manager
	if (isVisible)
	{
		App->render->Blit(App->entityManager->textures, pos.x - imgOffset.x, pos.y - imgOffset.y, &textureRect);
	}
	return true;
}