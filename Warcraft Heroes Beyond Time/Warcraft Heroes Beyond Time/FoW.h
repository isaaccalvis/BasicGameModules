#ifndef __FoW_H__
#define __FoW_H__

#include "Module.h"
#include "p2Point.h"
#include <vector>
#include <list>

// defines 1
#define ORIGINAL_TILE App->map->getTileSize()				// TILES FROM MAP
#define FOW_TILE_MULTIPLIER 1								// MULTIPLIER (FOW TILES CAN BE BIGGER)
#define FOW_TILE (ORIGINAL_TILE * FOW_TILE_MULTIPLIER)		// FOW OF WAR TILES
#define TILE_PARTITIONS 4									// PARTITIONS FOR ART OPTIMIZATION

#define RADIUS 4											// FOW TRANSPARENT RADIUS FROM PLAYER
#define TRANSLUCID_ALPHA 125								// WHEN A FOW TILES HAVE BEEN DISCOVERED BUT IS NOT SEEN

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

	bool Start();
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
	void TilesNearPlayer();

	// Problem 3
	int TotalDistanceToPlayer(int tile);

	// Problem 4
	// Not resolved here !! is an entity problem
	// Entity.h & .cpp

	// Problem 5  :Art Problem
	void SmallerTilesNearPlayer();
	int TotalDistanceToPlayerSmallers(iPoint pos);

public:
	std::vector<FoW_Tile*> fowTilesVector;
	std::vector<FoW_Tile*> fowSmallerTilesVector;
};

#endif