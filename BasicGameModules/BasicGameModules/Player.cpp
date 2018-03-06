#include "Player.h"
#include "App.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "Map.h"


// =============================================================================
// =================================  PLAYER  ==================================
// =============================================================================

player::player(SDL_Texture* texture) {
	this->texturePlayer = texture;
	animationPlayer.generalSpeed = PLAYER_SPEED;
	animationPlayer.AddFrame({0,0,PLAYER_SIZE,PLAYER_SIZE });
}

void player::Update()
{
	Move();
}

void player::Draw()
{
	App->render->Blit(texturePlayer, coord.x, coord.y, &animationPlayer.GetCurrentFrame());
}

void player::Finish() {}

void player::Move()
{
	if (App->input->GetKey(SDL_SCANCODE_W) == KeyState::KEY_REPEAT) {
		if (!App->mMap->CollidingWithATile(iPoint(this->coord.x, this->coord.y)))
			coord.y -= PLAYER_SPEED;
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KeyState::KEY_REPEAT) {
		if (!App->mMap->CollidingWithATile(iPoint(this->coord.x, this->coord.y + PLAYER_SIZE)))
			coord.y += PLAYER_SPEED;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_REPEAT) {
		if (!App->mMap->CollidingWithATile(iPoint(this->coord.x, this->coord.y + PLAYER_SIZE / 2)))
			coord.x -= PLAYER_SPEED;
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_REPEAT) {
		if (!App->mMap->CollidingWithATile(iPoint(this->coord.x + PLAYER_SIZE, this->coord.y + PLAYER_SIZE / 2)))
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
	texturePlayer = App->textures->Load("Resources/protaSprite.png");
	pj = new player(texturePlayer);
	pj->coord = iPoint(1 * TILE_SIZE + PLAYER_SIZE / 2 , 1 * TILE_SIZE + PLAYER_SIZE / 2);

	return true;
}

bool ModulePlayer::PreUpdate()
{

	return true;
}

bool ModulePlayer::Update(float dt)
{
	pj->Draw();
	pj->Update();
	return true;
}

bool ModulePlayer::PostUpdate()
{

	return true;
}

bool ModulePlayer::CleanUp()
{
	delete pj;
	App->textures->UnLoad(texturePlayer);
	return true;
}