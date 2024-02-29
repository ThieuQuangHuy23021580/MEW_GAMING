#include "Song1.h"

Meow::Meow()
{
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = WIDTH_MEOW;
	rect_.h = HEIGHT_MEOW;
	x_val_ = 0;
	y_val_ = 0;
}
Meow::~Meow()
{

}
void Song1::Song1_BG(SDL_Renderer* renderer)
{   
	SDL_Texture* song1 = NULL;
	song1 = SDLCommonFunc::loadTexture("SONG1.png",renderer);
	if (song1 == NULL) std::cerr << "SONG1_BG undefined!" << SDL_GetError() << std::endl;
	else
	{
		SDL_RenderCopy(renderer, SDLCommonFunc::loadTexture("SONG1.png", renderer), NULL, NULL);
		SDL_RenderPresent(renderer);
	}
}
void Meow::HandleMove(const int& x_boder, const int& y_boder) 
{
	//todo
}


