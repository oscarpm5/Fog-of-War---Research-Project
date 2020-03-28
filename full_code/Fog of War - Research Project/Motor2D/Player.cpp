#include "Player.h"
#include "j1App.h"
#include "j1Input.h"
#include "SDL/include/SDL_scancode.h"

Player::Player(iPoint pos) :Entity(ENTITY_TYPE::PLAYER, pos)
{
	textureRect = {0,0,64,96};
	imgOffset.x = textureRect.w * 0.5f;
	imgOffset.y = textureRect.h - 16;
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

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT ||
		App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		pos.y -= floor(speed*dt);
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT ||
		App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		pos.y += floor(speed*dt);
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT ||
		App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		pos.x -= floor(speed*dt);
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT ||
		App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		pos.x += floor(speed*dt);
	}

}


bool Player::CleanUp()
{
	bool ret = true;

	return ret;
}
