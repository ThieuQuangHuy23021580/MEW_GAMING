
//#include"Common_Function.h"
#include<chrono>
#include<thread>
#include"MainObject.h"
#include"Song1.h"

bool song1_played = false;




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
			std::cout << "could not be created! Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(gWindow, -1, 0);
		}
	}
	return success;
}
void ChooseSong() {
	song1_played = false;
	bool song_clicked = false;
	while (!song_clicked)
	{
		while (SDL_PollEvent(&g_even) != NULL)
		{
			if (g_even.type == SDL_MOUSEBUTTONDOWN && g_even.button.button == SDL_BUTTON_LEFT)
			{
				int mouseX_song, mouseY_song;
				SDL_GetMouseState(&mouseX_song, &mouseY_song);
				if (mouseY_song > 300 && mouseY_song < 400)
				{
					SDL_RenderClear(renderer);
					Song1::Song1_BG(renderer);
					song1_played = true;
					song_clicked = true;
				}
				else if (mouseY_song > 400 && mouseY_song < 500) {}
				else if (mouseY_song > 500 && mouseY_song < 600) {}
			}
		}
	}
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
					
					//Choose song:
					ChooseSong();

					clicked = true;
				
				}
			}
		}
	}
	
}



int main(int argc, char* args[]) {
	bool is_quit = false;
	if (init() == false)
	{
		std::cerr << "Can not open the window!" <<SDL_GetError()<< std::endl; return 0;
	}
	CallBG();
	//MAIN CHARACTER CALL:
	MainObject character;
	if (!character.loadImage("CHARACTER.png",renderer))
		std::cerr << " CHARACTER can not load! " << SDL_GetError() << std::endl;
	else
	{
		character.showObject(renderer,0);
		SDL_Texture* test_objectTexture = character.GetObject();
		if (test_objectTexture == NULL)
			std::cout << "ObjectTexture failed!" << std::endl;
			SDL_RenderPresent(renderer);
			

	}
	
	while (!is_quit)
		{
		    Uint32 ticks = SDL_GetTicks();
		    Uint32 sprite = (ticks / 100) % 4;
			bool un_move = true;
			while (SDL_PollEvent(&g_even))
			{
				if (g_even.type == SDL_QUIT)
				{
					is_quit = true;
					break;
				}

				else if (g_even.type == SDL_KEYDOWN)
				{

					character.HandleInputAction(g_even);
					un_move = false;


				}
				else /*if (g_even.type == SDL_KEYUP && (g_even.key.keysym.sym == SDLK_RIGHT || g_even.key.keysym.sym == SDLK_LEFT))*/
					un_move = true;
			}
			SDL_RenderClear(renderer);
			if(song1_played==true) SDL_RenderCopy(renderer, SDLCommonFunc::loadTexture("SONG1.png", renderer), NULL, NULL);
			if(un_move) character.SetSrcrect( 32, 0, 32, 64);
				
			else character.SetSrcrect(sprite * 32, 0, 32, 64);
				
			character.showObject(renderer, 1);
			
			SDL_RenderPresent(renderer);
    }
	SDLCommonFunc::close();
	return 0;
}