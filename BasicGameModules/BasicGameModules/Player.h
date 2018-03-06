#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Module.h"
#include "iPoint.h"
#include "Animation.h"
#include "SDL_image\include\SDL_image.h"

class player {
public:
	player(SDL_Texture* texture);

	void Update();
	void Draw();
	void Finish();

	void Move();
public:
	iPoint coord;
	AdvancedAnimation animationPlayer;
	SDL_Texture* texturePlayer;
};

class ModulePlayer : public Module {
public:

	ModulePlayer();
	~ModulePlayer();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

private:
	player* pj;
	SDL_Texture * texturePlayer;
};

#endif