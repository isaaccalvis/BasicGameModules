#ifndef __MAP_H__
#define __MAP_H__

#include "Module.h"

class Map {

};

class ModuleMap : public Module{
public:

	ModuleMap();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

public:


};

#endif