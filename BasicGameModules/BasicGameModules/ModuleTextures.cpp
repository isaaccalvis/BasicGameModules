#include "Defs.h"
#include "Log.h"
#include "App.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

ModuleTextures::ModuleTextures() : Module()
{
	name = "textures";
}

ModuleTextures::~ModuleTextures()
{}

bool ModuleTextures::Awake()
{
	bool ret = true;
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if((init & flags) != flags)
	{
		ret = false;
	}

	return ret;
}

bool ModuleTextures::Start()
{
	bool ret = true;
	return ret;
}

bool ModuleTextures::CleanUp()
{
	for(int i = 0; i < textures.size(); i++)
	{
		SDL_DestroyTexture(textures[i]);
	}

	textures.clear();
	IMG_Quit();
	return true;
}

bool ModuleTextures::FreeTextures()
{
	LOG("Freeing textures and Image library");

	for (int i = 0; i < textures.size(); i++)
	{
		SDL_DestroyTexture(textures[i]);
	}

	return true;
}

SDL_Texture* const ModuleTextures::Load(const char* path)
{
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = IMG_Load(path);

	if(surface == NULL)
	{
		LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
	}
	else
	{
		texture = LoadSurface(surface);
		SDL_FreeSurface(surface);
	}

	return texture;
}

bool ModuleTextures::UnLoad(SDL_Texture* texture)
{

	for (int i = 0; i < textures.size(); i++)
	{
		if(texture == textures[i])
		{
			SDL_DestroyTexture(textures[i]);
			delete textures[i];
			return true;
		}
	}

	return false;
}

SDL_Texture* const ModuleTextures::LoadSurface(SDL_Surface* surface)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(App->render->renderer, surface);

	if(texture == NULL)
	{
		LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		textures.push_back(texture);
	}

	return texture;
}

void ModuleTextures::GetSize(const SDL_Texture* texture, uint& width, uint& height) const
{
	SDL_QueryTexture((SDL_Texture*)texture, NULL, NULL, (int*) &width, (int*) &height);
}
