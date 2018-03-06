#ifndef __MAP_H__
#define __MAP_H__

#include <vector>

#include "SDL_image\include\SDL_image.h"
#include "PugiXml\src\pugixml.hpp"

#include "Module.h"
#include "Globals.h"
#include "iPoint.h"
#include "Defs.h"

#define TILE_SIZE 64

enum TILE_TYPE {
	GRASS,
	COLLIDER
};

class Tile {
public:
	Tile(iPoint coord);
	Tile(int x, int y);
	Tile(iPoint coord, TILE_TYPE type);

	iPoint coord;
	TILE_TYPE type;
};

class ModuleMap : public Module{
public:

	ModuleMap();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	bool CollidingWithATile(iPoint point);
	void ChargeMap();		

private:
	std::vector<Tile*> tileVector;
	std::vector<iPoint*> colliderList;
	SDL_Texture* textureGrass = nullptr;
	SDL_Texture* textureCollider = nullptr;
	SDL_Rect tilesRect = { 0,0,64,64 };
};

#endif