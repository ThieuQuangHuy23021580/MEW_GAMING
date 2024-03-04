#include "MainObject.h"

MainObject::MainObject()
{
	rect_.x = 180;
	rect_.y = 500;
	rect_.w = WIDTH_MAIN/1.2;
	rect_.h = HEIGHT_MAIN/1.2;

	objectTexture = NULL;
	
}
MainObject::~MainObject()
{

}

void MainObject::HandleInputAction(SDL_Event events)
{    
	if (events.type == SDL_KEYDOWN)
	{    
		
		switch (events.key.keysym.sym)
		{
		case SDLK_LEFT:
			if(rect_.x>0)
			rect_.x -= WIDTH_MAIN /27;
			break;
		case SDLK_RIGHT:
			if((rect_.x+WIDTH_MAIN)<SCREEN_WIDTH)
			rect_.x += WIDTH_MAIN / 27;
			break;
		}
	}
	/*if (events.type == SDL_KEYUP)
	{

		switch (events.key.keysym.sym)
		{
		case SDLK_LEFT:
			if (rect_.x > 0)
				rect_.x += WIDTH_MAIN / 30;
			break;
		case SDLK_RIGHT:
			if ((rect_.x + WIDTH_MAIN) < SCREEN_WIDTH)
				rect_.x -= WIDTH_MAIN / 30;
			break;
		}
		
	}*/
	
	
	
}



