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
	visionEntity = App->fowManager->CreateFoWEntity(pos, true);
	visionEntity->SetNewVisionRadius(4);
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

	if(auxPos!=pos)
	visionEntity->SetNewPosition(pos);

}


bool Player::CleanUp()
{
	bool ret = true;

	return ret;
}
