
//#include"Common_Function.h"

#include"MainObject.h"
#include"Song1.h"
#include<cmath>
#include"PlayMusic.h"
#include<thread>

bool call_bg = false;
bool song1_played = false;
bool song2_played = false;
bool song3_played = false;
Graphics graphics;




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
		if (TTF_Init() == -1)
		{
			std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
		}	
	}
	

	return success;
}
bool playMusic() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) 
	{
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return 0;
	}
	return 1;

}
void ChooseSong(SDL_Texture* Mouse, int mx, int my,SDL_Texture* background) {
	
	song1_played = false;
	bool song_clicked = false;
	int song_double_clicked = 0;
	Mix_Chunk* gChunk = graphics.loadSound("CLICK_SOUND.wav");
	if (gChunk == NULL) std::cerr << "Sound Error" << SDL_GetError() << std::endl;
	while (song_double_clicked<2&&!call_bg)
	{   
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, background, NULL, NULL);
		SDL_GetMouseState(&mx, &my);
		//std::cerr << mx << " " << my << std::endl;
		SDLCommonFunc::renderTexture(Mouse, renderer, mx - 25, my - 25, 120, 123);

		SDL_RenderPresent(renderer);
		//SDL_DestroyTexture(Fake_Mouse);
		while (SDL_PollEvent(&g_even) != NULL)
		{   
			if (g_even.type == SDL_MOUSEBUTTONDOWN)
				graphics.playSound(gChunk);
			if (g_even.type == SDL_QUIT)
			{
				SDLCommonFunc::close();
			}
			else if (g_even.type == SDL_MOUSEBUTTONDOWN && g_even.button.button == SDL_BUTTON_LEFT)
			{   
			
		
				int mouseX_song, mouseY_song;
				SDL_GetMouseState(&mouseX_song, &mouseY_song);
				if (mouseY_song > 310 && mouseY_song < 430)
				{
					SDL_RenderClear(renderer);
					//Song1::Song1_BG(renderer);
					song1_played = true;
					song_double_clicked++;
					call_bg = true;
				}
				else if (mouseY_song > 460 && mouseY_song < 560)
				{
					SDL_RenderClear(renderer);
					//Song1::Song1_BG(renderer);
					song2_played = true;
					song_double_clicked++;
					call_bg = true;
				}
				else if (mouseY_song > 590 && mouseY_song < 700) 
				{
					SDL_RenderClear(renderer);
					//Song1::Song1_BG(renderer);
					song3_played = true;
					song_double_clicked++;
					call_bg = true;
				}
				else if (mouseY_song < 100&&mouseY_song>0 && mouseX_song < 100&&mouseX_song >0)
				{
					call_bg = false;
					song_double_clicked++;
				}
			}
		}
	}
}
void Menu(SDL_Texture* Mouse,SDL_Texture* background)
{   
	Mix_Chunk* gChunk = graphics.loadSound("CLICK_SOUND.wav");
	if (gChunk == NULL) std::cerr << "Sound Error" << SDL_GetError() << std::endl;
	bool menu_clicked = false;
	SDL_Texture* menu_1 = SDLCommonFunc::loadTexture("FOOD_MENU_1.png", renderer);
	SDL_Texture* menu_2 = SDLCommonFunc::loadTexture("FOOD_MENU_2.png", renderer);
	int mx, my;
	SDL_Rect menu_Rect = { 277,690,1,1 };

	
	

	while (!menu_clicked)
	{   
		SDL_RenderClear(renderer);
		SDL_GetMouseState(&mx, &my);
		SDL_RenderCopy(renderer, background, NULL, NULL);
		SDL_RenderCopy(renderer, menu_1, NULL, &menu_Rect);
		
			if(menu_Rect.x > 0 )menu_Rect.x--;
			if(menu_Rect.y > 0)menu_Rect.y--;
			if(menu_Rect.w < 529)menu_Rect.w++;
			if(menu_Rect.h < 748)menu_Rect.h++;
		
		std::cout << mx << "," << my << std::endl;
		SDLCommonFunc::renderTexture(Mouse, renderer, mx - 25, my - 25, 120, 123);
		SDL_RenderPresent(renderer);
		call_bg = true;
		while (SDL_PollEvent(&g_even) != NULL)
		{
			if (g_even.type == SDL_MOUSEBUTTONDOWN)
				graphics.playSound(gChunk);
			if (g_even.type == SDL_QUIT)
			{
				SDLCommonFunc::close();
			}
			else if (g_even.type == SDL_MOUSEBUTTONDOWN && g_even.button.button == SDL_BUTTON_LEFT)
			{
				if (mx > 200 && mx < 347 && my>565 && my < 615) 
				{ 
					menu_clicked = true;
				
				}
			}
		}
	}
}
void CallBG(SDL_Texture* Mouse, int &mx, int &my) 
{   
	
	
	bool clicked = false;
	SDL_Texture* background1 = NULL;
	SDL_Texture* background2 = NULL;
	SDL_Texture* background3 = NULL;

	background1 = SDLCommonFunc::loadTexture("bg1.png", renderer);
	background2 = SDLCommonFunc::loadTexture("bg2.png", renderer);
	background3 = SDLCommonFunc::loadTexture("bg3.png", renderer);
	if (background1 == NULL||background2==NULL) 
		std::cerr << "BG error: " << SDL_GetError() << std::endl;
	SDL_Texture* Start1 = NULL;
	Start1 = SDLCommonFunc::loadTexture("START_BUTTON_1.png", renderer);
	SDL_Texture* Start2 = NULL;
	Start2 = SDLCommonFunc::loadTexture("START_BUTTON_2.png", renderer);
	SDL_Rect S1_Rect = { 180,450,181,182};
	SDL_Rect S2_Rect = { 180,450,181,182 };
	SDL_Texture* char_button = SDLCommonFunc::loadTexture("CHAR_BUTTON.png", renderer);
	SDL_Rect d_char = { 225,640, 96, 92 };
	SDL_Rect s1_char = { 0,0,191,184 };
	SDL_Rect s2_char = { 200,0,191,184 };
	
	if (Start1 == NULL||Start2==NULL)
		std::cerr << "Start error" << SDL_GetError() << std::endl;
	else {
		
		Mix_Chunk* gChunk = graphics.loadSound("CLICK_SOUND.wav");
		if (gChunk == NULL) std::cerr << "Sound Error" << SDL_GetError() << std::endl;
		
		while (!clicked)
		{   
			SDL_RenderClear(renderer);
			
			
			
			SDL_GetMouseState(&mx, &my);
			std::cout << mx << "," << my <<std:: endl;
			if (mx > 235 && mx < 320 && my>650 && my < 730)
			{
				SDL_RenderCopy(renderer, background2, NULL, NULL);
				SDL_RenderCopy(renderer, Start1, NULL, &S1_Rect);
				SDL_RenderCopy(renderer, char_button, &s2_char, &d_char);
			}
			else if (mx>190&&mx<360&&my>460&&my<630) {
				SDL_RenderCopy(renderer, background2, NULL, NULL);
				SDL_RenderCopy(renderer, Start2, NULL, &S2_Rect);
				SDL_RenderCopy(renderer, char_button, &s1_char, &d_char);
				
			
			}
			else
			{
				SDL_RenderCopy(renderer, background1, NULL, NULL);
				SDL_RenderCopy(renderer, Start1, NULL, &S1_Rect);
				SDL_RenderCopy(renderer, char_button, &s1_char, &d_char);
				
			}
			SDLCommonFunc::renderTexture(Mouse, renderer, mx - 25, my - 25, 120, 123);
			SDL_RenderPresent(renderer);
			while (SDL_PollEvent(&g_even) != NULL)
			{    
				if(g_even.type== SDL_MOUSEBUTTONDOWN)
				 graphics.playSound(gChunk);
				if (g_even.type == SDL_QUIT)
				{
					SDLCommonFunc::close();
				}
				else if (g_even.type == SDL_MOUSEBUTTONDOWN && g_even.button.button == SDL_BUTTON_LEFT)
				{
					int mouseX, mouseY;
					SDL_GetMouseState(&mouseX, &mouseY);
					if (mouseX > 190 && mouseX < 360 && mouseY>460 && mouseY < 630)
					{
						SDL_Delay(700);
						SDL_RenderClear(renderer);
						background1 = SDLCommonFunc::loadTexture("PLAYLIST_BG.png", renderer);
						SDL_RenderCopy(renderer, background1, NULL, NULL);
						SDL_RenderPresent(renderer);

						//Choose song:
						ChooseSong(Mouse,mx,my,background1);

						clicked = true;

					}
					else if (mouseX > 235 && mouseX < 320 && mouseY>650 && mouseY < 730)
					{
						
						Menu(Mouse,background3);

					}
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


	if (playMusic() == 0) {
		std::cout << "Can't play music" << std::endl;
	}
	
    Mix_Music* gMusic= graphics.loadMusic("SCARY_MUSIC.mp3");
	if (gMusic == NULL) std::cerr << "Music Error"<<SDL_GetError()<<std::endl;
	



	/*bool first_click = false;
	while (!first_click)
	{
		graphics.play(gMusic);
		SDL_Texture* backgr = NULL;
		backgr = SDLCommonFunc::loadTexture("SCARY.png", renderer);
		if (backgr == NULL)
			std::cerr << "BG error: " << SDL_GetError() << std::endl;
		else SDL_RenderCopy(renderer, backgr, NULL, NULL);
		SDL_RenderPresent(renderer); 
		while (SDL_PollEvent(&g_even) != NULL)
		{   
			if (g_even.type == SDL_QUIT)
			{
				SDLCommonFunc::close();
			}
			else if (g_even.type == SDL_MOUSEBUTTONDOWN && g_even.button.button == SDL_BUTTON_LEFT)
			{
				first_click = true;
				Mix_FreeMusic(gMusic);
			}
		}
	}


	
	
	if (first_click)
	{
		SDL_Delay(3);
		SDL_Texture* backgr2 = NULL;
		backgr2 = SDLCommonFunc::loadTexture("just_kidding.png", renderer);
		if (backgr2 == NULL)
			std::cerr << "BG error: " << SDL_GetError() << std::endl;
		else SDL_RenderCopy(renderer, backgr2, NULL, NULL);
		SDL_RenderPresent(renderer);
		SDL_Delay(500);
	}*/
	gMusic = graphics.loadMusic("MAIN_MUSIC.mp3");
	
	
	//MAIN CHARACTER CALL:
	MainObject character;
	if (!character.loadImage("WALK_BG_FULL1.png",renderer))
		std::cerr << " CHARACTER can not load! " << SDL_GetError() << std::endl;
	else
	{
		character.SetSrcrect(1136, 0, 142, 288);
		//character.showObject(renderer, 1);
		SDL_Texture* test_objectTexture = character.GetObject();
		if (test_objectTexture == NULL)
			std::cout << "ObjectTexture failed!" << std::endl;
		//SDL_RenderPresent(renderer);
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
			 //SDL_RenderPresent(renderer);
		 }
	 }
	 cat[0].SetRect(cat[0].GetRect().x, 0);
	 cat[1].SetRect(cat[1].GetRect().x, -200);
	//Load Song BACKGROUND:
	SDL_Texture* song1_bg = SDLCommonFunc::loadTexture("song1bg.png", renderer);
	SDL_Texture* song2_bg = SDLCommonFunc::loadTexture("song2bg.png", renderer);
	SDL_Texture* song3_bg = SDLCommonFunc::loadTexture("song3bg.png", renderer);
	
	int sprite_plus[16] = { 0,1,2,3,4,5,6,7,9,10,11,12,13,14,15,16 };
	int i = 35, j = 45;
	SDL_Texture* Mouse = NULL;
	Mouse = SDLCommonFunc::loadTexture("MOUSE_3.png", renderer);
	if (Mouse == NULL) 
		std::cerr << "MOUSE pic unload!" << SDL_GetError() << std::endl;
	int mx = 0, my = 0;
	SDL_ShowCursor(0);

	//POINT :
	int plus = 0;
	TTF_Font* font = graphics.loadFont("SpeedRush.ttf", 50);
	SDL_Color color = { 255, 255, 0, 255 };
	std::string point = "Score: ";
	

	
	while (!is_quit)
	{

		graphics.play(gMusic);
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
				else if (g_even.key.keysym.sym == SDLK_LEFT)
				{

					if (i == 0) i = 35;
					if (i % 5 == 0)
						character.SetSrcrect(sprite_plus[i / 5] * 142, 0, 142, 288);
					i--;

				}
				else if (g_even.key.keysym.sym == SDLK_RIGHT)
				{

					if (j == 80) j = 45;
					if (j % 5 == 0)
						character.SetSrcrect(sprite_plus[j / 5 - 1] * 142, 0, 142, 288);
					j++;
				}
			}
			else
				character.SetSrcrect(1136, 0, 142, 288);
			un_move = true;


		}
		while (call_bg == false) {
			CallBG(Mouse, mx, my);
			//call_bg = true;

		}

		SDL_RenderClear(renderer);

		if (song1_played == true) SDL_RenderCopy(renderer, song1_bg, NULL, NULL);
		else if (song2_played == true) SDL_RenderCopy(renderer, song2_bg, NULL, NULL);
		else if (song3_played == true) SDL_RenderCopy(renderer, song3_bg, NULL, NULL);

		//POINT: 
		point = "Score: " + std::to_string(plus);
	    graphics.renderText(renderer, point, font, color, 10, 10);
		
		


		/*SDL_GetMouseState(&mx, &my);
		std::cerr << mx << " " << my << std::endl;
		SDLCommonFunc::renderTexture(Mouse, renderer, mx - 25, my - 25, 50, 45);*/
		
		//SongNote(cat);
		cat[0].HandleMove();
		cat[0].showObject(renderer, 0);

		int bottom_x = cat->GetRect().x + WIDTH_MEOW / 2;
		if (character.GetRect().x < bottom_x && character.GetRect().x + WIDTH_MAIN >bottom_x && character.GetRect().y - HEIGHT_MAIN / 10 == cat->GetRect().y)
		{
			cat[0].SetLose(true);
			plus++;
		}
		if (cat[0].GetRect().y == SCREEN_HEIGHT - 200)
		{
			MessageBox(NULL, L"Thua roi liu liu :>", L"HUY said:", MB_OK); /* == IDOK */
			SDL_Delay(100);
			call_bg = false;
		}
		


		/*cat[1].HandleMove();
		cat[1].showObject(renderer, 0);*/





		character.showObject(renderer, 1);

		SDL_RenderPresent(renderer);

	}
	
	
	
	Mix_FreeMusic(gMusic);
	graphics.closeMusic();
	SDLCommonFunc::close();
	return 0;
}