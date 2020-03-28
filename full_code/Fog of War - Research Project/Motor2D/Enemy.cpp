#include "Enemy.h"
#include "SDL/include/SDL_scancode.h"

Enemy::Enemy(iPoint pos) :Entity(ENTITY_TYPE::ENEMY, pos)
{
	textureRect = { 128,0,64,96 };
	imgOffset.x = textureRect.w * 0.5f;
	imgOffset.y = textureRect.h - 16;
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
