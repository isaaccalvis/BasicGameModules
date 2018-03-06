#include "Map.h"
#include "App.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

#define TILE_SIZE 64

Tile::Tile(iPoint coord)
{
	this->coord = coord;
	this->type = GRASS;
}

Tile::Tile(int x, int y)
{
	this->coord.x = x;
	this->coord.y = y;
	this->type = GRASS;
}

Tile::Tile(iPoint coord, TILE_TYPE type)
{
	this->coord = coord;
	this->type = type;
}

ModuleMap::ModuleMap()
{}

bool ModuleMap::Start()
{
	textureGrass = App->textures->Load("Resources/TileGrassSprite.png");
	textureCollider  = App->textures->Load("Resources/TileColliderSprite.png");
	return true;
}

bool ModuleMap::PreUpdate()
{

	return true;
}

bool ModuleMap::Update(float dt)
{
	// PRINT_MAP
	for (int i = 0; i < tileVector.size(); i++) {
		switch (tileVector[i]->type) {
		case GRASS:
			App->render->Blit(textureGrass, tileVector[i]->coord.x * TILE_SIZE, tileVector[i]->coord.y * TILE_SIZE, &tilesRect);
			break;
		case COLLIDER:
			App->render->Blit(textureCollider, tileVector[i]->coord.x * TILE_SIZE, tileVector[i]->coord.y * TILE_SIZE, &tilesRect);
			break;
		}
	}
	return true;
}

bool ModuleMap::PostUpdate()
{

	return true;
}

bool ModuleMap::CleanUp()
{

	return true;
}

void ModuleMap::AddTile(Tile* tile) {
	tileVector.push_back(tile);
}

bool ModuleMap::ReturnConcretTileIfExist(Tile* tile)
{
	for (int i = 0; i < tileVector.size(); i++) {
		if (tileVector[i]->coord == tile->coord)
			return true;
	}
	return false;
}