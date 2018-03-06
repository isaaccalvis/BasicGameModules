#ifndef __APP_H__
#define __APP_H__

#include "Module.h"
#include <list>
#include <string>

class ModuleWindow;
class ModuleInput;
class ModuleRender;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;
class ModuleMap;

class Application
{
public:

	Application(int argc, char* args[]);
	virtual ~Application();

	bool Awake();
	bool Start();
	bool Update();
	bool CleanUp();

	void AddModule(Module* module);

	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

private:

	void PrepareUpdate();
	void FinishUpdate();
	bool PreUpdate();
	bool DoUpdate();
	bool PostUpdate();

public:

	ModuleWindow*					window = nullptr;
	ModuleInput*					input = nullptr;
	ModuleRender*					render = nullptr;
	ModuleTextures*					textures = nullptr;
	ModuleAudio*					audio = nullptr;
	ModulePlayer*					mPlayer = nullptr;
	ModuleMap*						mMap = nullptr;

public:

	float dt = 0.0f;

private:

	std::list<Module*> modules;
	int					argc;
	char**				args;

	std::string			title;
	std::string			organization;

};

extern Application* App;

#endif