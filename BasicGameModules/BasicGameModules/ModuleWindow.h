#ifndef __j1WINDOW_H__
#define __j1WINDOW_H__

#include "Module.h"

struct SDL_Window;
struct SDL_Surface;

class ModuleWindow : public Module
{
public:

	ModuleWindow();
	virtual ~ModuleWindow();

	bool Awake();
	bool CleanUp();

	void SetTitle(const char* new_title);
	void GetWindowSize(uint& width, uint& height) const;
	uint GetScale() const;

public:

	SDL_Window* window;
	SDL_Surface* screen_surface;

private:
	char*		title;
	uint		width;
	uint		height;
	uint		scale;
};

#endif