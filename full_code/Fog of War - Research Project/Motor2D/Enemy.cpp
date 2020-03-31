#include "Enemy.h"
#include "SDL/include/SDL_scancode.h"
#include "j1App.h"
#include "FoWManager.h"

Enemy::Enemy(iPoint pos) :Entity(ENTITY_TYPE::ENEMY, pos)
{
	textureRect = { 128,0,64,96 };
	imgOffset.x = textureRect.w * 0.5f;
	imgOffset.y = textureRect.h - 16;
	
	//TODO 2.3: Same as before! BUT, this unit is an enemy, it does not provide visibility! As a consequence, it doesn't matter if you change its radius of vision as it sees nothing :)
	visionEntity = App->fowManager->CreateFoWEntity(pos, false);
}


Enemy::~Enemy()
{
	CleanUp();
}


bool Enemy::Update(float dt)
{
	bool ret = true;

	return ret;
}


bool Enemy::CleanUp()
{
	bool ret = true;

	return ret;
}
