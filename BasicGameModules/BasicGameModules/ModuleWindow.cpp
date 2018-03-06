#include "Defs.h"
#include "Log.h"
#include "App.h"
#include "ModuleWindow.h"

#include "SDL/include/SDL.h"


ModuleWindow::ModuleWindow() : Module()
{
	window = NULL;
	screen_surface = NULL;
	name = "window";
}

ModuleWindow::~ModuleWindow() {}

bool ModuleWindow::Awake()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		Uint32 flags = SDL_WINDOW_SHOWN;
		bool fullscreen = false;
		bool borderless = false;
		bool resizable = false;
		bool fullscreen_window = false;

		width = 1024;
		height = 600;
		scale = 1;

		if(fullscreen == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		if(borderless == true)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		if(resizable == true)
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}

		if(fullscreen_window == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		window = SDL_CreateWindow(App->GetTitle(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	if(window != NULL)
		SDL_DestroyWindow(window);

	SDL_Quit();
	return true;
}

void ModuleWindow::SetTitle(const char* new_title)
{
	SDL_SetWindowTitle(window, new_title);
}

void ModuleWindow::GetWindowSize(uint& width, uint& height) const
{
	width = this->width;
	height = this->height;
}

uint ModuleWindow::GetScale() const
{
	return scale;
}