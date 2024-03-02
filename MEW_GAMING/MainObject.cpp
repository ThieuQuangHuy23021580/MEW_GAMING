#include "MainObject.h"

MainObject::MainObject()
{
	rect_.x = 180;
	rect_.y = 600;
	rect_.w = WIDTH_MAIN;
	rect_.h = HEIGHT_MAIN;

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
			rect_.x -= WIDTH_MAIN / 4;
			break;
		case SDLK_RIGHT:
			if((rect_.x+WIDTH_MAIN)<SCREEN_WIDTH)
			rect_.x += WIDTH_MAIN / 4;
			break;
		}
	}
	
}



