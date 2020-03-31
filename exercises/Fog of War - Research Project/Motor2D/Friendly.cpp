#include "Friendly.h"
#include "j1App.h"
#include "FoWManager.h"
#include "j1Input.h"

Friendly::Friendly(iPoint pos) :Entity(ENTITY_TYPE::PLAYER, pos)
{
	textureRect = { 64,0,64,96 };
	imgOffset.x = textureRect.w * 0.5f;
	imgOffset.y = textureRect.h - 16;

	//TODO 2.2: Same as before!


	
}


Friendly::~Friendly()
{
	CleanUp();
}


bool Friendly::Update(float dt)
{
	bool ret = true;

	HandleInput(dt);

	return ret;
}


void Friendly::HandleInput(float dt)
{
	int speed = 200;

	iPoint auxPos = pos;

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		pos.y -= floor(speed * dt);
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		pos.y += floor(speed * dt);
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		pos.x -= floor(speed * dt);
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		pos.x += floor(speed * dt);
	}


	//TODO 4.1: same as with the player, don't forget to set the new FoWEntity position when needed!
	//Note that friendly unit HandleInput() function is called every frame, you do not need to update the FoWEntity position each frame, only when position changes
	
}


bool Friendly::CleanUp()
{
	bool ret = true;

	return ret;
}