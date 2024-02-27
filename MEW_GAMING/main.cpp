
#include"Common_Function.h"
#include<chrono>
#include<thread>


bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL could not initialize! Error: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow(" SDL Game ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			std::cout << "Window could not be created! Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(gWindow, -1, 0);
		}
	}
	return success;
}

void CallBG() 
{   
	bool clicked = false;
	SDL_Texture* background = NULL;
	background = SDLCommonFunc::loadTexture("OPEN_BACKGROUND.png", renderer);
	if (background == NULL) 
		std::cerr << "BG error: " << SDL_GetError() << std::endl;
	else SDL_RenderCopy(renderer, background, NULL, NULL);
	SDL_RenderPresent(renderer);
	while (!clicked) 
	{
		while(SDL_PollEvent(&g_even)!=NULL)
		{
			if (g_even.type == SDL_MOUSEBUTTONDOWN && g_even.button.button == SDL_BUTTON_LEFT)
			{
				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);
				if (mouseX > 200 && mouseX < 300 && mouseY>550 && mouseY < 650)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(700));
					SDL_RenderClear(renderer);
					background = SDLCommonFunc::loadTexture("PLAYLIST_BACKGROUND.png", renderer);
					SDL_RenderCopy(renderer, background, NULL, NULL);
					SDL_RenderPresent(renderer);
					clicked = true;
					//Choose song:

				}
			}
		}
	}
	
}

void StartPlay() {
	
}
int main(int argc, char* args[]) {
	bool is_quit = false;
	if (init() == false)
	{
		std::cerr << "Can not open the window!" <<SDL_GetError()<< std::endl; return 0;
	}
	CallBG();
	while (!is_quit)
		{
			while (SDL_PollEvent(&g_even))
			{
				if (g_even.type == SDL_QUIT)
				{
					is_quit = true;
					break;
				}
			}
    }
	SDLCommonFunc::close();
	return 0;
}