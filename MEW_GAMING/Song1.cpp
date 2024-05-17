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
	song1 = SDLCommonFunc::loadTexture("06_apple_pie_dish.png",renderer);
	if (song1 == NULL) std::cerr << "SONG1_BG undefined!" << SDL_GetError() << std::endl;
	else
	{
		SDL_RenderCopy(renderer, SDLCommonFunc::loadTexture("06_apple_pie_dish.png", renderer), NULL, NULL);
		SDL_RenderPresent(renderer);
	}
}
void Meow::HandleMove(int m, int first_y)
{   
	
	if (is_move) {
		rect_.x = m;
		rect_.y = first_y;
		is_move = false;
	}
		if (rect_.y < SCREEN_HEIGHT - 90&&is_lose==false) {
			
			rect_.y += 3;
			
		}
		else if (is_lose == true) {
			rect_.y = -60;
			/*rect_.x = rand() % 270+120;
			if (rect_.x < 100 && rect_.x>390)
				rect_.x = 120;
			is_lose = false;*/
		}
		/*else {
			rect_.y = n;
			rect_.x = rand() % 480;
			if (rect_.x < 30 && rect_.x>450)
				rect_.x = 100;
		}*/
		
	
}

void Meow::CloudMove()
{
	SDL_Delay(8);
	if (rect_.x < SCREEN_WIDTH+300) rect_.x++;
	else if (rect_.x == SCREEN_WIDTH + 300) {
		rect_.x = -300;
		rect_.y = rand() % 151 -50;
	}
}

