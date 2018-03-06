#include "Map.h"
#include "App.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

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
	ChargeMap();

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

bool ModuleMap::CollidingWithATile(iPoint point)
{
	for (int i = 0; i < tileVector.size(); i++) {
		if (!((tileVector[i]->coord.x * TILE_SIZE + TILE_SIZE < point.x || tileVector[i]->coord.x * TILE_SIZE > point.x)&&
			(tileVector[i]->coord.y * TILE_SIZE + TILE_SIZE < point.y || tileVector[i]->coord.y * TILE_SIZE > point.y)))
			return true;
	}
	return false;
}

void ModuleMap::ChargeMap()
{

	pugi::xml_document mapXML;
	mapXML.load_file("Resources/mapaBasic1.tmx");
	pugi::xml_node layer = mapXML.child("map").child("layer");
	std::string nullLayerString = "";
	pugi::xml_node layer_data = layer.child("data");
	pugi::xml_node tile = layer_data.child("tile");

	for (int y = 0; y < mapXML.child("map").attribute("height").as_uint(); ++y)
		for (int x = 0; x < mapXML.child("map").attribute("width").as_int(); ++x)
		{
			Tile* aux;
			iPoint coord(x, y);
			switch (tile.attribute("gid").as_int() - 1) {
			case 0:
				aux = new Tile(coord, GRASS);
				tileVector.push_back(aux);
				break;
			case 1:
				aux = new Tile(coord, COLLIDER);
				tileVector.push_back(aux);
				iPoint* point = new iPoint(x, y);
				colliderList.push_back(point);
				printf_s("%i %i \n", point->x, point->y);
				break;
			}
			tile = tile.next_sibling("tile");
		}
	layer = layer.next_sibling("layer");
}