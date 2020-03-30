#include "Friendly.h"
#include "j1App.h"
#include "FoWManager.h"
#include "j1Input.h"

Friendly::Friendly(iPoint pos) :Entity(ENTITY_TYPE::PLAYER, pos)
{
	textureRect = { 64,0,64,96 };
	imgOffset.x = textureRect.w * 0.5f;
	imgOffset.y = textureRect.h - 16;
	visionEntity = App->fowManager->CreateFoWEntity(pos, true);
	visionEntity->SetNewVisionRadius(3);
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

	if (auxPos != pos)
		visionEntity->SetNewPosition(pos);
}


bool Friendly::CleanUp()
{
	bool ret = true;

	return ret;
}