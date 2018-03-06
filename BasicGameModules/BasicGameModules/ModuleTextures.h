#ifndef __j1TEXTURES_H__
#define __j1TEXTURES_H__

#include "Module.h"
#include "Globals.h"
#include <vector>

struct SDL_Texture;
struct SDL_Surface;

class ModuleTextures : public Module
{
public:

	ModuleTextures();
	virtual ~ModuleTextures();

	bool Awake();
	bool Start();
	bool CleanUp();

	SDL_Texture* const	Load(const char* path);
	bool				UnLoad(SDL_Texture* texture);
	SDL_Texture* const	LoadSurface(SDL_Surface* surface);
	void				GetSize(const SDL_Texture* texture, uint& width, uint& height) const;
	bool				FreeTextures();

public:

	std::vector<SDL_Texture*>	textures;
};


#endif