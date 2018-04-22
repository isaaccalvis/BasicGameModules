 #include "Application.h"
#include "Entity.h"
#include "ModuleRender.h"
#include "ModulePrinter.h"
#include "FoW.h"
#include "Scene.h"
#include "ModuleMapGenerator.h"
#include "PlayerEntity.h"

Entity::Entity(fPoint coor, SDL_Texture* texture) : pos(coor), texture(texture) {}

bool Entity::Start() { return true; }

bool Entity::Update(float dt) { return true; }

bool Entity::PostUpdate() { return true; }

bool Entity::Finish() { return true; }

int Entity::distanceToPlayer()
{
	int totalX = pos.x / ORIGINAL_TILE - (int)App->scene->player->pos.x / ORIGINAL_TILE;
	if (totalX < 0)
		totalX *= -1;
	int totalY = pos.y / ORIGINAL_TILE - (int)App->scene->player->pos.y / ORIGINAL_TILE;
	if (totalY < 0)
		totalY *= -1;
	return sqrt(totalX*totalX + totalY*totalY);
}

bool Entity::Draw()
{
	bool ret = true;
	ret = App->printer->PrintSprite(iPoint(pos.x, pos.y), texture, anim->GetCurrentFrame(), 0, ModulePrinter::Pivots::CUSTOM_PIVOT, 0, anim->GetCurrentPivot());

	if (entityBasicType == ENTITY_TYPE::DINAMIC) {
		// TODO 4: DON'T PRINT UNITS IF THEY ARE OUT OF FOW RANGE. Use : RADIUS (fow radius), distanceToPlayer() to distance
		// USE spawn_archer TO SPAWN AN ENEMY ARCHER

	}
	return ret;
}

void Entity::Collision(COLLIDER_TYPE type) {}

void Entity::StopConcreteTime(int time)
{
	accountantPrincipal = SDL_GetTicks() + time;
	stop = true;
}