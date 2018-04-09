#include "FoW.h"
#include "Application.h"
#include "ModuleRender.h"
//#include "ModulePrinter.h"

#define FOW_TILE_SIZE 100

FoW::FoW() : Module()
{
	name = "fow";
}

FoW::~FoW()
{

}

bool FoW::Start()
{

	return true;
}

bool FoW::Update(float dt)
{
	return true;
}

bool FoW::CleanUp()
{

	return true;
}

void FoW::loadFoWMap(int mapWidth, int mapHeight)
{
	for (int x = 0; x * FOW_TILE_SIZE < mapWidth; x++)
		for (int y = 0; y * FOW_TILE_SIZE < mapHeight; y++)
		{
			FoW_Tile* aux = new FoW_Tile;
			aux->pos = iPoint(x, y);
			fowTilesList.push_back(aux);
		}
}

void FoW::printFoW()
{
	std::list<FoW_Tile*>::iterator it = fowTilesList.begin();
	for (; it != fowTilesList.end(); it++)
	{
		App->render->DrawQuad({ (*it)->pos.x * FOW_TILE_SIZE, (*it)->pos.y * FOW_TILE_SIZE, FOW_TILE_SIZE, FOW_TILE_SIZE },0,0,0, (*it)->alpha);
	}
}