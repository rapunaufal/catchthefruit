#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <SDL/SDL_mixer.h>
#include "Texture.h"

class AudioManager
{
public:
	AudioManager();
	~AudioManager();
	void InitAudio();
	void PlayAudio();
	Texture teksture;
	
private:
	//Mix_Chunk *sound = NULL;
	Mix_Music *music = NULL;
	int sfx_channel = -1;
};

#endif

