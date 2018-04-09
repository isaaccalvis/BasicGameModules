#ifndef __FoW_H__
#define __FoW_H__

#include "Module.h"
#include "p2Point.h"
#include <vector>

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

	bool Awake();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	void AddCommands();

	void loadFoWMap(int mapWidth, int mapHeight);
	void unloadFowMap();
	void print();

public:
	std::vector<FoW_Tile*> fowTilesVector;
	bool printFoW = true;
};

#endif