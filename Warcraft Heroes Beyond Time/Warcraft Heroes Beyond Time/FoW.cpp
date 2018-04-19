#include "FoW.h"
#include "Application.h"
#include "ModuleRender.h"

#include "Console.h"
#include "Scene.h"
#include "PlayerEntity.h"
#include "ModuleMapGenerator.h"
#include "Pathfinding.h"
//#include "ModulePrinter.h"

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
	TilesNearPlayer(RADIUS);
	return true;
}

bool FoW::PostUpdate()
{
	if (printFoW)
	{
		print();
		ArtPartition();

		//std::list<FoW_Tile*>::iterator temp = temporalSmallerTiles.begin();
		//for (; temp != temporalSmallerTiles.end(); temp++)
		//	delete (*temp);
		//temporalSmallerTiles.clear();
	}
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

void FoW::print()
{
	for (int i = 0; i < fowTilesVector.size(); i++)
	{
		App->render->DrawQuad({ fowTilesVector[i]->pos.x * FOW_TILE, fowTilesVector[i]->pos.y * FOW_TILE, FOW_TILE, FOW_TILE }, 0, 0, 0, fowTilesVector[i]->alpha);
	}
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

int FoW::TotalDistanceToPlayer(int tile)
{
	int totalX = (fowTilesVector[tile]->pos.x * FOW_TILE + (FOW_TILE / 2)) / FOW_TILE - ((int)App->scene->player->pos.x + (App->scene->player->anim->GetCurrentRect().w / 2)) / FOW_TILE;
	if (totalX < 0)
		totalX *= -1;
	int totalY = (fowTilesVector[tile]->pos.y * FOW_TILE + (FOW_TILE / 2)) / FOW_TILE - ((int)App->scene->player->pos.y + (App->scene->player->anim->GetCurrentRect().h / 2)) / FOW_TILE;
	if (totalY < 0)
		totalY *= -1;
	return sqrt(totalX * totalX + totalY * totalY);
}

void FoW::TilesNearPlayer(int radius)
{
	for (int i = 0; i < fowTilesVector.size(); i++)
	{
		int smallerTileTemp = 0;
		if (TotalDistanceToPlayer(i) == radius)
		{	// ART PROBLEM !!
			for (int x = 0; x < TILE_PARTITIONS; x++)
				for (int j = 0; j < TILE_PARTITIONS; j++)
				{
					//FoW_Tile* aux = new FoW_Tile();	// AQUESTS TILES NO ESTAN EN COORDS LOCALS ! ESTAN EN GLOBALS !
					//aux->pos.x = fowTilesVector[i]->pos.x * FOW_TILE + (x * FOW_TILE / TILE_PARTITIONS);
					//aux->pos.y = fowTilesVector[i]->pos.y * FOW_TILE + (j * FOW_TILE / TILE_PARTITIONS);
					//aux->normalAlpha = fowTilesVector[i]->normalAlpha;
					//temporalSmallerTiles.push_back(aux);
					temporalSmallerTilesStatic[smallerTileTemp].pos = iPoint(fowTilesVector[i]->pos.x * FOW_TILE + (x * FOW_TILE / TILE_PARTITIONS), fowTilesVector[i]->pos.y * FOW_TILE + (j * FOW_TILE / TILE_PARTITIONS));
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

//int FoW::TotalDistanceToPlayerSmallers(std::list<FoW_Tile*>::iterator temp)
//{
//	int totalX = (*temp)->pos.x + (FOW_TILE / TILE_PARTITIONS / 2) - ((int)App->scene->player->pos.x + (App->scene->player->anim->GetCurrentRect().w / 2));
//	if (totalX < 0)
//		totalX *= -1;
//	int totalY = (*temp)->pos.y + (FOW_TILE / TILE_PARTITIONS / 2) - ((int)App->scene->player->pos.y + (App->scene->player->anim->GetCurrentRect().h / 2));
//	if (totalY < 0)
//		totalY *= -1;
//	return sqrt(totalX * totalX + totalY * totalY);
//}

int FoW::TotalDistanceToPlayerSmallers(iPoint pos)
{
	int totalX = pos.x + (FOW_TILE / TILE_PARTITIONS / 2) - ((int)App->scene->player->pos.x + (App->scene->player->anim->GetCurrentRect().w / 2));
	if (totalX < 0)
		totalX *= -1;
	int totalY = pos.y + (FOW_TILE / TILE_PARTITIONS / 2) - ((int)App->scene->player->pos.y + (App->scene->player->anim->GetCurrentRect().h / 2));
	if (totalY < 0)
		totalY *= -1;
	return sqrt(totalX * totalX + totalY * totalY);
}

void FoW::ArtPartition()
{
	//std::list<FoW_Tile*>::iterator temp = temporalSmallerTiles.begin();
	//for (; temp != temporalSmallerTiles.end() ; temp++)
	//{
	//	if (TotalDistanceToPlayerSmallers(temp) < RADIUS * FOW_TILE + FOW_TILE / TILE_PARTITIONS)
	//		(*temp)->alpha = 0;
	//	else
	//		(*temp)->alpha = (*temp)->normalAlpha;
	//}

	//temp = temporalSmallerTiles.begin();
	//for (; temp != temporalSmallerTiles.end(); temp++)
	//{
	//	App->render->DrawQuad({ (*temp)->pos.x, (*temp)->pos.y, FOW_TILE / TILE_PARTITIONS, FOW_TILE / TILE_PARTITIONS }, 0, 0, 0, (*temp)->alpha);
	//}
	
	for (int i = 0; i < RADIUS * 2 ; i++)
	{
		if (TotalDistanceToPlayerSmallers(temporalSmallerTilesStatic[i].pos) < RADIUS * FOW_TILE + FOW_TILE / TILE_PARTITIONS)
			temporalSmallerTilesStatic[i].alpha = 0;
		else
			temporalSmallerTilesStatic[i].alpha = temporalSmallerTilesStatic[i].normalAlpha;
	}

	for (int i = 0; i < RADIUS * 2; i++)
	{
		App->render->DrawQuad({ temporalSmallerTilesStatic[i].pos.x, temporalSmallerTilesStatic[i].pos.y, FOW_TILE / TILE_PARTITIONS, FOW_TILE / TILE_PARTITIONS }, 0, 0, 0, temporalSmallerTilesStatic[i].alpha);
	}

}