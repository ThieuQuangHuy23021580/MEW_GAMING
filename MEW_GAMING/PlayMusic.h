#ifndef PLAY_MUSIC_H_

#define PLAY_MUSIC_H_
#include"BaseObject.h"

class Graphics
{
public:
	Mix_Music* loadMusic(const char* path);

	void play(Mix_Music* gMusic);

	void closeMusic();

	Mix_Chunk* loadSound(const char* path);

	void playSound(Mix_Chunk* gChunk);



};


#endif
