#ifndef PLAY_MUSIC_H_

#define PLAY_MUSIC_H_
#include"BaseObject.h"

class Graphics
{
public:
	Mix_Music* loadMusic(const char* path);

	void play(Mix_Music* gMusic);

	void closeMusic();

	void playSong(Mix_Music* gMusic);

	Mix_Chunk* loadSound(const char* path);

	void playSound(Mix_Chunk* gChunk);
    
	TTF_Font* loadFont(const char* path, int size);

	void* renderText(SDL_Renderer* renderer, std::string text, TTF_Font* font, SDL_Color textColor,int x, int y);


};


#endif
