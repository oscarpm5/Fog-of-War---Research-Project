#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1EntityManager.h"
#include "FoWManager.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	if (App->map->Load("iso_walk.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;

		RELEASE_ARRAY(data);
	}

	debug_tex = App->tex->Load("textures/sprites.png");

	App->fowManager->CreateFoWMap(App->map->data.width, App->map->data.height);

	App->entityManager->AddNewEntity(ENTITY_TYPE::ENEMY, { 500,500 });
	App->entityManager->AddNewEntity(ENTITY_TYPE::ENEMY, { -350,750 });
	cameraFocusEntity = App->entityManager->AddNewEntity(ENTITY_TYPE::PLAYER, { 300,700 });
	App->entityManager->AddNewEntity(ENTITY_TYPE::FRIENDLY, { 250,500 });
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	FocusCameraOnTarget();
	App->map->Draw();

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if (App->input->GetMouseButtonDown(1) == KEY_REPEAT)
	{
		// Debug ally ------------------------------
		int x, y;
		App->input->GetMousePosition(x, y);
		iPoint p;
		App->render->ScreenToWorld(x, y, p.x, p.y);
		App->map->WorldToMap(p.x, p.y, p.x, p.y);
		App->map->MapToWorld(p.x, p.y, p.x, p.y);
		SDL_SetTextureAlphaMod(debug_tex, 128);
		SDL_Rect r = { 64,0,64,96 };
		App->render->Blit(debug_tex, p.x, p.y - 48, &r);
	}
	else if (App->input->GetMouseButtonDown(1) == KEY_UP)
	{
		int x, y;
		App->input->GetMousePosition(x, y);
		int pX;
		int pY;
		App->render->ScreenToWorld(x, y, pX, pY);
		App->map->WorldToMap(pX, pY, pX, pY);
		App->map->MapToWorld(pX, pY, pX, pY);
		App->entityManager->AddNewEntity(ENTITY_TYPE::FRIENDLY, {pX+32,pY+32});
	}


	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}


//focuses camera on the targeted entity
void j1Scene::FocusCameraOnTarget()
{
	SDL_Rect* camAux = &App->render->camera;
	if (cameraFocusEntity != nullptr)
	{
		camAux->x = -(cameraFocusEntity->pos.x - (camAux->w * 0.5f));
		camAux->y = -(cameraFocusEntity->pos.y - (camAux->h * 0.5f));
	}
}
