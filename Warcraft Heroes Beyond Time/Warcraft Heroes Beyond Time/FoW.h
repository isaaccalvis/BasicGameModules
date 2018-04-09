#ifndef __FoW_H__
#define __FoW_H__

#include "Module.h"
#include "p2Point.h"
#include <list>

struct FoW_Tile
{
	iPoint pos;
	int size = 0;
	int alpha = 255;
};

class FoW : public Module
{
public:
	FoW();
	~FoW();

	bool Start();
	bool Update(float dt);
	bool CleanUp();

	void loadFoWMap(int mapWidth, int mapHeight);
	void printFoW();

public:
	std::list<FoW_Tile*> fowTilesList;
};

#endif