#include "Song1.h"

Meow::Meow()
{
	rect_.x = 230;
	rect_.y = -30;
	rect_.w = WIDTH_MEOW;
	rect_.h = HEIGHT_MEOW;
	is_move = true;
	is_lose = false;
	drop_effect = false;
	delay = false;
}
Meow::~Meow()
{

}
void Song1::Song1_BG(SDL_Renderer* renderer)
{   
	SDL_Texture* song1 = NULL;
	song1 = SDLCommonFunc::loadTexture("song1bg.png",renderer);
	if (song1 == NULL) std::cerr << "SONG1_BG undefined!" << SDL_GetError() << std::endl;
	else
	{
		SDL_RenderCopy(renderer, SDLCommonFunc::loadTexture("song1bg.png", renderer), NULL, NULL);
		SDL_RenderPresent(renderer);
	}
}
void Meow::HandleMove( )
{   
	SDL_Delay(3);

	if (is_move == true) {
		if (rect_.y < SCREEN_HEIGHT - 200&&is_lose==false) {
			

			rect_.y += 1;
			
		}
		else if (is_lose == true) {
			rect_.y = 0;
			rect_.x = rand() % 480;
			if (rect_.x < 0 && rect_.x>450)
				rect_.x = 100;
			is_lose = false;
		}
		else {
			rect_.y = 0;
			rect_.x = rand() % 480;
			if (rect_.x < 0 && rect_.x>450)
				rect_.x = 100;
		}
		
	}
}


