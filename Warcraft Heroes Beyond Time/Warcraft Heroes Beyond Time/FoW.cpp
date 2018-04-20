#include "FoW.h"
#include "Application.h"
#include "ModuleRender.h"

#include "Console.h"
#include "Scene.h"
#include "PlayerEntity.h"
#include "ModuleMapGenerator.h"
//#include "ModulePrinter.h"

class ConsoleFoWOrder : public ConsoleOrder
{
		std::string orderName()
		{
			return "fow";
		}

		void Exec(std::string parameter, int parameterNumeric)
		{
			if (parameter == "load")
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
	TilesNearPlayer(RADIUS);
	return true;
}

bool FoW::PostUpdate()
{
	print();
	ArtPartition();
	return true;
}

bool FoW::CleanUp()
{
	unloadFowMap();
	return true;
}

void FoW::AddCommands()
{
	ConsoleOrder* order = new ConsoleFoWOrder;
	App->console->AddConsoleOrderToList(order);
}

void FoW::print()
{
	for (int i = 0; i < fowTilesVector.size(); i++)
	{
		App->render->DrawQuad({ fowTilesVector[i]->pos.x * FOW_TILE, fowTilesVector[i]->pos.y * FOW_TILE, FOW_TILE, FOW_TILE }, 0, 0, 0, fowTilesVector[i]->alpha);
	}
}

void FoW::loadFoWMap(int mapWidth, int mapHeight)
{
	// TODO 1: WE HAVE TO COVER THE MAP WITH FOW TILES
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

	for (int i = 0; i < fowSmallerTilesVector.size(); i++)
		delete fowSmallerTilesVector[i];
	fowSmallerTilesVector.clear();
}

int FoW::TotalDistanceToPlayer(int tile)
{
	int totalX = (fowTilesVector[tile]->pos.x * FOW_TILE + (FOW_TILE / 2)) / FOW_TILE - ((int)App->scene->player->pos.x + 40) / FOW_TILE;
	if (totalX < 0)
		totalX *= -1;
	int totalY = (fowTilesVector[tile]->pos.y * FOW_TILE + (FOW_TILE / 2)) / FOW_TILE - (int)App->scene->player->pos.y / FOW_TILE;
	if (totalY < 0)
		totalY *= -1;
	return sqrt(totalX * totalX + totalY * totalY);
}

void FoW::TilesNearPlayer(int radius)
{
	int contador = 0;
	for (int i = 0; i < fowTilesVector.size(); i++)
	{
		if (TotalDistanceToPlayer(i) == radius)
		{
			for (int x = 0; x < TILE_PARTITIONS; x++)
				for (int j = 0; j < TILE_PARTITIONS; j++)
				{
					if (contador < fowSmallerTilesVector.size())
					{
						fowSmallerTilesVector[contador]->pos.x = fowTilesVector[i]->pos.x * FOW_TILE + (x * FOW_TILE / TILE_PARTITIONS);
						fowSmallerTilesVector[contador]->pos.y = fowTilesVector[i]->pos.y * FOW_TILE + (j * FOW_TILE / TILE_PARTITIONS);
						fowSmallerTilesVector[contador]->normalAlpha = fowTilesVector[i]->normalAlpha;
					}
					else
					{
						FoW_Tile* aux = new FoW_Tile();
						aux->pos.x = fowTilesVector[i]->pos.x * FOW_TILE + (x * FOW_TILE / TILE_PARTITIONS);
						aux->pos.y = fowTilesVector[i]->pos.y * FOW_TILE + (j * FOW_TILE / TILE_PARTITIONS);
						aux->normalAlpha = fowTilesVector[i]->normalAlpha;
						fowSmallerTilesVector.push_back(aux);
					}
					contador++;

				}
			fowTilesVector[i]->alpha = 0;
		}
		else if (TotalDistanceToPlayer(i) < radius)
		{
			fowTilesVector[i]->alpha = 0;
			fowTilesVector[i]->normalAlpha = TRANSLUCID_ALPHA;
		}
		else
			// Problem 3
			fowTilesVector[i]->alpha = fowTilesVector[i]->normalAlpha;
	}
}

int FoW::TotalDistanceToPlayerSmallers(iPoint pos)
{
	int totalX = pos.x + (FOW_TILE / TILE_PARTITIONS / 2) - ((int)App->scene->player->pos.x + 50);
	if (totalX < 0)
		totalX *= -1;
	int totalY = pos.y + (FOW_TILE / TILE_PARTITIONS / 2) - (int)App->scene->player->pos.y;
	if (totalY < 0)
		totalY *= -1;
	return sqrt(totalX * totalX + totalY * totalY);
}

void FoW::ArtPartition()
{
	for (int i = 0; i < fowSmallerTilesVector.size(); i++)
	{
		if (TotalDistanceToPlayerSmallers(fowSmallerTilesVector[i]->pos) < RADIUS * FOW_TILE)
			fowSmallerTilesVector[i]->alpha = 0;
		else
			fowSmallerTilesVector[i]->alpha = fowSmallerTilesVector[i]->normalAlpha;
	}

	for (int i = 0; i < fowSmallerTilesVector.size(); i++)
	{
		App->render->DrawQuad({ fowSmallerTilesVector[i]->pos.x, fowSmallerTilesVector[i]->pos.y, FOW_TILE / TILE_PARTITIONS, FOW_TILE / TILE_PARTITIONS }, 0, 0, 0, fowSmallerTilesVector[i]->alpha);
	}
}