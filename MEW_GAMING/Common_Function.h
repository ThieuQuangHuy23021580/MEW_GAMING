#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNTION_H_

#include<windows.h>
#include<SDL.h>
#include<iostream>
#include<string>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>


const int SCREEN_WIDTH = 529;
const int SCREEN_HEIGHT = 748;

static SDL_Window* gWindow = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Event g_even;



namespace SDLCommonFunc
{
	SDL_Texture* loadTexture(std::string file_path,SDL_Renderer* renderer);
	void renderTexture(SDL_Texture* texture,SDL_Renderer*  renderer, int x, int y, int w, int h);
	void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Rect& srcrect );
	void close();
}

#endif
