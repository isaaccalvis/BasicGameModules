#ifndef __FoW_H__
#define __FoW_H__

#include "Module.h"
#include "p2Point.h"
#include <vector>

// defines 1
#define ORIGINAL_TILE App->map->getTileSize()
#define FOW_TILE_MULTIPLIER 1
#define FOW_TILE (ORIGINAL_TILE * FOW_TILE_MULTIPLIER)

// defines 2
#define RADIUS 5
#define TRANSLUCID_ALPHA 125

struct FoW_Tile
{
	iPoint pos;
	int size = 0;
	int alpha = 255;
	int normalAlpha = 255;
};

class FoW : public Module
{
public:
	FoW();
	~FoW();

	bool Awake();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	void AddCommands();

	// Utilities
	void print();

	// Problem 1
	void loadFoWMap(int mapWidth, int mapHeight);
	void unloadFowMap();

	// Problem 2
	void TilesNearPlayer(int radius);

	// Problem 3
	int TotalDistanceToPlayer(int tile);

	// Problem 4
	// Not resolved here !! is an entity problem
	// Entity.h & .cpp

public:
	std::vector<FoW_Tile*> fowTilesVector;
	bool printFoW = true;
};

#endif