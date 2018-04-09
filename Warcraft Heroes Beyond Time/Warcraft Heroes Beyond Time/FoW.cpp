#include "FoW.h"
#include "Application.h"
#include "ModuleRender.h"

#include "Console.h"
#include "ModuleMapGenerator.h"
//#include "ModulePrinter.h"

#define ORIGINAL_TILE App->map->getTileSize()
#define FOW_TILE_MULTIPLIER 2
#define FOW_TILE ORIGINAL_TILE * FOW_TILE_MULTIPLIER

class ConsoleFoWOrder : public ConsoleOrder
{
		std::string orderName()
		{
			return "fow";
		}

		void Exec(std::string parameter, int parameterNumeric)
		{
			if (parameter == "print")
			{
				if (parameterNumeric == 1)
					App->fow->printFoW = true;
				else
					App->fow->printFoW = false;
			}
			else if (parameter == "load")
			{
				uint w, h;
				App->map->getSize(w, h);
				App->fow->loadFoWMap((int)w, (int)h);

			}
			else if (parameter == "unload")
				App->fow->unloadFowMap();
		}
};

FoW::FoW() : Module()
{
	name = "fow";
}

FoW::~FoW()
{

}

bool FoW::Awake()
{

	return true;
}

bool FoW::Update(float dt)
{

	return true;
}

bool FoW::PostUpdate()
{
	if (printFoW)
		print();
	return true;
}

bool FoW::CleanUp()
{

	return true;
}

void FoW::AddCommands()
{
	ConsoleOrder* order = new ConsoleFoWOrder;
	App->console->AddConsoleOrderToList(order);
}

void FoW::loadFoWMap(int mapWidth, int mapHeight)
{
	for (int x = 0; x < mapWidth / FOW_TILE_MULTIPLIER; x++)
		for (int y = 0; y < mapHeight / FOW_TILE_MULTIPLIER; y++)
		{
			FoW_Tile* aux = new FoW_Tile;
			aux->pos = iPoint(x, y);
			fowTilesVector.push_back(aux);
		}
}

void FoW::unloadFowMap()
{
	for (int i = 0; i < fowTilesVector.size(); i++)
		delete fowTilesVector[i];
	fowTilesVector.clear();
}

void FoW::print()
{
	for (int i = 0; i < fowTilesVector.size(); i++)
	{
		App->render->DrawQuad({ fowTilesVector[i]->pos.x * FOW_TILE, fowTilesVector[i]->pos.y * FOW_TILE, FOW_TILE, FOW_TILE }, 0, 0, 0, fowTilesVector[i]->alpha);
	}
}