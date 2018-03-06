#include "Player.h"
#include "App.h"
#include "ModuleInput.h"
#include "ModuleRender.h"

#define PLAYER_SPEED 1	// distance in pixels

// =============================================================================
// =================================  PLAYER  ==================================
// =============================================================================

player::player(SDL_Texture* texture) {
	this->texturePlayer = texture;
}

void player::Update() {}

void player::Draw()
{
	App->render->Blit(texturePlayer, coord.x, coord.y, &rectPlayer);
}

void player::Finish() {}

void player::Move()
{
	if (App->input->GetKey(SDL_SCANCODE_W) == KeyState::KEY_REPEAT) {
		coord.y -= PLAYER_SPEED;
	}
	else if (App->input->GetKey(SDL_SCANCODE_S) == KeyState::KEY_REPEAT) {
		coord.y += PLAYER_SPEED;
	}
	else if (App->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_REPEAT) {
		coord.x -= PLAYER_SPEED;
	}
	else if (App->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_REPEAT) {
		coord.x += PLAYER_SPEED;
	}
}

// =============================================================================
// =============================== MODULE PLAYER ===============================
// =============================================================================

ModulePlayer::ModulePlayer()
{}


ModulePlayer::~ModulePlayer()
{
	CleanUp();
}

bool ModulePlayer::Start()
{
	pj = new player(texturePlayer);
	pj->coord = iPoint(0, 0);

	return true;
}

bool ModulePlayer::PreUpdate()
{

	return true;
}

bool ModulePlayer::Update(float dt)
{
	
	return true;
}

bool ModulePlayer::PostUpdate()
{

	return true;
}

bool ModulePlayer::CleanUp()
{
	delete pj;
	return true;
}