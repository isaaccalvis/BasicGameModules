#ifndef __j1AUDIO_H__
#define __j1AUDIO_H__

#include "Module.h"
#include <vector>

#define DEFAULT_MUSIC_FADE_TIME 2.0f

struct _Mix_Music;
struct Mix_Chunk;

class ModuleAudio : public Module
{
public:

	ModuleAudio();
	virtual ~ModuleAudio();

	bool Awake();
	bool CleanUp();
	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);
	unsigned int LoadFx(const char* path);
	bool PlayFx(unsigned int fx, int repeat = 0);

private:

	_Mix_Music*			music = NULL;
	std::vector<Mix_Chunk*>	fx;
};

#endif