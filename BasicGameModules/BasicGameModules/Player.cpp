#include "Player.h"
#include "App.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"


// =============================================================================
// =================================  PLAYER  ==================================
// =============================================================================

player::player(SDL_Texture* texture) {
	this->texturePlayer = texture;
	animationPlayer.generalSpeed = 500;
	animationPlayer.AddFrame({0,0,40,40});
	animationPlayer.AddFrame({ 40,0,40,40 });
	animationPlayer.AddFrame({ 80,0,40,40 });
	animationPlayer.AddFrame({ 120,0,40,40 });

}

void player::Update() {
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
		coord.y -= PLAYER_SPEED;
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KeyState::KEY_REPEAT) {
		coord.y += PLAYER_SPEED;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_REPEAT) {
		coord.x -= PLAYER_SPEED;
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_REPEAT) {
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
	pj->coord = iPoint(0, 0);

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