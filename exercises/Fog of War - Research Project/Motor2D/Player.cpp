#include "Player.h"
#include "j1App.h"
#include "j1Input.h"
#include "SDL/include/SDL_scancode.h"
#include "FoWManager.h"

Player::Player(iPoint pos) :Entity(ENTITY_TYPE::PLAYER, pos)
{
	textureRect = {0,0,64,96};
	imgOffset.x = textureRect.w * 0.5f;
	imgOffset.y = textureRect.h - 16;

	//TODO 2.1: The player will need to have a FoWEntity assigned to him (the variable that you need is called "visionEntity")
	//Note that the player provides visibility to allies!
	//Extra: you can also set its vision radius once created calling the function SetNewVisionRadius(), you can choose between a radius of 2,3,4 and 5
	



}


Player::~Player()
{
	CleanUp();
}


bool Player::Update(float dt)
{
	bool ret = true;

	HandleInput(dt);

	return ret;
}


void Player::HandleInput(float dt)
{
	int speed = 200;

	iPoint auxPos = pos;

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		pos.y -= floor(speed*dt);
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		pos.y += floor(speed*dt);
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		pos.x -= floor(speed*dt);
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		pos.x += floor(speed*dt);
	}

	//TODO 4: don't forget to set the new FoWEntity position when needed!
	//Note that player HandleInput() function is called every frame, you do not need to update the FoWEntity position each frame, only when position changes


}


bool Player::CleanUp()
{
	bool ret = true;

	return ret;
}
