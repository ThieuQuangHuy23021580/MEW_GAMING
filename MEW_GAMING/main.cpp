
//#include"Common_Function.h"

#include"MainObject.h"
#include"Song1.h"
#include<cmath>

bool call_bg = false;
bool song1_played = false;
bool song2_played = false;
bool song3_played = false;


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
bool playMusic() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return 1;
	}
}
void ChooseSong() {
	song1_played = false;
	bool song_clicked = false;
	while (!song_clicked&&!call_bg)
	{
		while (SDL_PollEvent(&g_even) != NULL)
		{
			if (g_even.type == SDL_MOUSEBUTTONDOWN && g_even.button.button == SDL_BUTTON_LEFT)
			{
				int mouseX_song, mouseY_song;
				SDL_GetMouseState(&mouseX_song, &mouseY_song);
				if (mouseY_song > 310 && mouseY_song < 430)
				{
					SDL_RenderClear(renderer);
					//Song1::Song1_BG(renderer);
					song1_played = true;
					song_clicked = true;
					call_bg = true;
				}
				else if (mouseY_song > 460 && mouseY_song < 560)
				{
					SDL_RenderClear(renderer);
					//Song1::Song1_BG(renderer);
					song2_played = true;
					song_clicked = true;
					call_bg = true;
				}
				else if (mouseY_song > 590 && mouseY_song < 700) 
				{
					SDL_RenderClear(renderer);
					//Song1::Song1_BG(renderer);
					song3_played = true;
					song_clicked = true;
					call_bg = true;
				}
				else if (mouseY_song < 100&&mouseY_song>0 && mouseX_song < 100&&mouseX_song >0)
				{
					call_bg = false;
					song_clicked = true;
				}
			}
		}
	}
}

void CallBG() 
{   
	bool clicked = false;
	SDL_Texture* background = NULL;
	background = SDLCommonFunc::loadTexture("openBackground.png", renderer);
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
					SDL_Delay(700);
					SDL_RenderClear(renderer);
					background = SDLCommonFunc::loadTexture("PLAYLIST_BG.png", renderer);
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
void SongNote(Meow cat[]) {
  
	
	cat[0].HandleMove();
	cat[0].showObject(renderer, 0);
	
	cat[1].HandleMove();
	cat[1].showObject(renderer, 0);
	

}



int main(int argc, char* args[]) {
	bool is_quit = false;
	if (init() == false)
	{
		std::cerr << "Can not open the window!" <<SDL_GetError()<< std::endl; return 0;
	}
	while (call_bg == false) {
		CallBG();
		//call_bg = true;
	}
	
	//MAIN CHARACTER CALL:
	MainObject character;
	if (!character.loadImage("WALK_BG_FULL1.png",renderer))
		std::cerr << " CHARACTER can not load! " << SDL_GetError() << std::endl;
	else
	{
		character.SetSrcrect(1136, 0, 142, 288);
		character.showObject(renderer, 1);
		SDL_Texture* test_objectTexture = character.GetObject();
		if (test_objectTexture == NULL)
			std::cout << "ObjectTexture failed!" << std::endl;
		SDL_RenderPresent(renderer);
	}
	//FALL CAT:
	 Meow cat[2];	
	 
	 
	 for (int i = 0; i < 2; i++) {
		 if (!cat[i].loadImage("CAT.jpg", renderer))
			 std::cerr << " CAT can not load! " << SDL_GetError() << std::endl;
		 else
		 {

			 cat[i].showObject(renderer, 0);
			 SDL_Texture* test_catTexture = cat[i].GetObject();
			 if (test_catTexture == NULL)
				 std::cout << "CatTexture failed!" << std::endl;
			 SDL_RenderPresent(renderer);
		 }
	 }
	 cat[0].SetRect(cat[0].GetRect().x, 0);
	 cat[1].SetRect(cat[1].GetRect().x, -200);
	//Load Song BACKGROUND:
	SDL_Texture* song1_bg = SDLCommonFunc::loadTexture("song1bg.png", renderer);
	SDL_Texture* song2_bg = SDLCommonFunc::loadTexture("song2bg.png", renderer);
	SDL_Texture* song3_bg = SDLCommonFunc::loadTexture("song3bg.png", renderer);
	
	int sprite_plus[16] = { 0,1,2,3,4,5,6,7,9,10,11,12,13,14,15,16 };
	int i = 0, j = 45, i_ = 0,j_=45;
	while (!is_quit)
		{
		    Uint32 ticks = SDL_GetTicks();
		    Uint32 sprite = (ticks / 200) % 17;
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
					if (un_move) character.SetSrcrect(1136, 0, 142, 288);
					else if (g_even.key.keysym.sym == SDLK_LEFT/*&& sprite%17!=0 && sprite%17 != 1 && sprite %17!= 2 && sprite%17 != 3 && sprite % 17 != 4 && sprite % 17 != 5 && sprite % 17 != 6 && sprite % 17 != 7 && sprite % 17 != 8*/)
					{
						
						if (i == 35) i = 0;
						if (i % 5 == 0) {
							character.SetSrcrect(sprite_plus[i_/5] * 142, 0, 142, 288);
							i_ = i;
						}
					/*	else {
							character.SetSrcrect(sprite_plus[i_] * 142, 0, 142, 288);
						}*/
						
						i++;
						
					}
					else if (g_even.key.keysym.sym == SDLK_RIGHT /*&& sprite % 17 != 8 && sprite % 17 != 9 && sprite % 17 != 10 && sprite % 17 != 11 && sprite % 17 != 12 && sprite % 17 != 13 && sprite % 17 != 14 && sprite % 17 != 15 && sprite % 17 != 16*/)
					{
						
						if (j == 80) j = 45;
						if (j % 5 == 0) {
							character.SetSrcrect(sprite_plus[j_/5] * 142, 0, 142, 288);
							j_ = j;
						}
						//else character.SetSrcrect(sprite_plus[j_] * 142, 0, 142, 288);
						j++;
					}
				}
				else 
					character.SetSrcrect(1136, 0, 142, 288);
					un_move = true;
			}
			//SDL_Delay(3);
			SDL_RenderClear(renderer);
			if (song1_played == true) SDL_RenderCopy(renderer, song1_bg, NULL, NULL);
			else if (song2_played == true) SDL_RenderCopy(renderer, song2_bg, NULL, NULL);
			else if (song3_played == true) SDL_RenderCopy(renderer, song3_bg, NULL, NULL);

			SongNote(cat);
			
			
			
			
			character.showObject(renderer, 1);
			
			SDL_RenderPresent(renderer);
		
    }
	SDLCommonFunc::close();
	return 0;
}