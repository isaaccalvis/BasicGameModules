#ifndef __MAP_H__
#define __MAP_H__

#include "Module.h"
#include "Globals.h"
#include "iPoint.h"
#include <vector>
#include "SDL_image\include\SDL_image.h"

enum TILE_TYPE {
	GRASS,
	COLLIDER
};

class Map {
public:
	Map();

private:
	uint numberOfChambers;
	uint terrainTiles;

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

	bool ReturnConcretTileIfExist(Tile* tile);

private:
	std::vector<Tile*> tileVector;
	SDL_Texture* textureGrass = nullptr;
	SDL_Texture* textureCollider = nullptr;
	SDL_Rect tilesRect = { 0,0,64,64 };
};

#endif