#include "MainObject.h"

MainObject::MainObject()
{
	rect_.x = 190;
	rect_.y = 600;
	rect_.w = WIDTH_MAIN/2.5;
	rect_.h = HEIGHT_MAIN/2.5;
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
			rect_.x -= WIDTH_MAIN /20;
			break;
		case SDLK_RIGHT:
			if((rect_.x+rect_.w)<SCREEN_WIDTH)
			rect_.x += WIDTH_MAIN / 20;
			break;
		}
	}
}
void MainObject::StartState()
{
	rect_.x = 190;
	rect_.y = 600;
}


