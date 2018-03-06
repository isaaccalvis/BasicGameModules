#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Module.h"
#include "iPoint.h"
#include "Animation.h"
#include "SDL_image\include\SDL_image.h"

#define PLAYER_SPEED 2	// distance in pixels
#define PLAYER_SIZE 34
#define PLAYER_Animation_SPEED 300

enum DIRECTION {
	UP,
	DOWN,
	RIGHT,
	LEFT
};

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
	player* pj;

private:
	SDL_Texture * texturePlayer;
};

#endif