
//#include"Common_Function.h"

#include"MainObject.h"
#include"Song1.h"
#include<cmath>
#include"PlayMusic.h"
#include<thread>
#include<cstring>
#define MAXN 308

bool call_bg = false;
bool song1_played = false;
bool song2_played = false;
bool song3_played = false;
int food = 1;
bool choose_food = false;

Graphics graphics;
Mix_Music* gMusic;
BaseObject disc[3];




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
	Uint32 ticks = SDL_GetTicks();
	Uint32 sprite = (ticks / 90) % 9;
	
	
	
	bool song_clicked = false;
	
	Mix_Chunk* gChunk = graphics.loadSound("CLICK_SOUND.wav");
	if (gChunk == NULL) std::cerr << "Sound Error" << SDL_GetError() << std::endl;
	BaseObject undo;
	undo.loadImage("UNDO.png", renderer);
	undo.SetRect_Size(100, 100);
	undo.SetSrcrect(0, 0, 196, 201);
	undo.SetRect(0, 0);

	while (!song_clicked&&!call_bg)
	{   
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, background, NULL, NULL);
		SDL_GetMouseState(&mx, &my);
		
		if (my < 100 && my>0 && mx < 100 && mx >0) undo.SetSrcrect(203, 0, 196, 201);
		else undo.SetSrcrect(0, 0, 196, 201);
		undo.showObject(renderer, 1);


		
		
		ticks = SDL_GetTicks();
		sprite = (ticks / 90) % 9;

		if (mx > 155 && mx < 430 && my > 290 && my < 360) disc[0].SetSrcrect(sprite * 1587, 0, 1587, 1625);
		else disc[0].SetSrcrect(0, 0, 1587, 1625);
	    if(mx > 155 && mx < 430&& my > 430 && my < 500) disc[1].SetSrcrect(sprite * 1587, 0, 1587, 1625);
		else disc[1].SetSrcrect(0, 0, 1587, 1625);
		if(mx > 155 && mx < 430&& my > 560 && my < 635) disc[2].SetSrcrect(sprite * 1587, 0, 1587, 1625);
		else disc[2].SetSrcrect(0, 0, 1587, 1625);
		
		 disc[0].showObject(renderer, 1);
		 disc[1].showObject(renderer, 1);
		 disc[2].showObject(renderer, 1);
		
		std::cerr << mx << " " << my << std::endl;
		
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
		
				if (mx > 155 && mx < 430) 
				{
					if (my > 290 && my < 360)
					{
						SDL_RenderClear(renderer);
						
						song1_played = true;
						song_clicked = true;
						call_bg = true;
					   
					}
					else if (my > 430 && my < 500)
					{
						SDL_RenderClear(renderer);
						song2_played = true;
						song_clicked = true;
						call_bg = true;
					}
					else if (my > 560 && my < 635)
					{
						SDL_RenderClear(renderer);
						song3_played = true;
						song_clicked = true;
						call_bg = true;
						
					}
				}
				else if (my < 100 && my>0 && mx < 100 && mx >0)
				{
					call_bg = false;
					song_clicked = true;
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
	SDL_Texture* menu_1 = SDLCommonFunc::loadTexture("FOOD_MENU_1_new.png", renderer);
	SDL_Texture* menu_2 = SDLCommonFunc::loadTexture("FOOD_MENU_2_new.png", renderer);
	int mx, my;
	SDL_Rect menu_Rect = { 277,690,1,1 };
	BaseObject f1, f2, f3, f4, f5, f6, tick;
	f1.loadImage("APPLE_PIE.png", renderer);
	f2.loadImage("BREAD.png", renderer);
	f3.loadImage("BURGER.png", renderer);
	f4.loadImage("COOKIES.png", renderer);
	f5.loadImage("DONUT.png", renderer);
	f6.loadImage("HOTDOG.png", renderer);
	tick.loadImage("TICK.png", renderer);

	f1.SetRect(100, 78);
	f2.SetRect(213, 78);
	f3.SetRect(328, 78);
	f4.SetRect(100, 200);
	f5.SetRect(213, 200);
	f6.SetRect(328, 200);

	if (food == 1)tick.SetRect(100 + 25, 78 + 88);
	else if (food == 2)tick.SetRect(213 + 25, 78 + 88);
	else if (food == 3)tick.SetRect(328 + 25, 78 + 88);
	else if (food == 4)tick.SetRect(100 + 25, 200 + 88);
	else if (food == 5)tick.SetRect(213 + 25, 200 + 88);
	else if (food == 6)tick.SetRect(328 + 25, 200 + 88);
	f1.SetRect_Size(100, 100);
	f2.SetRect_Size(100, 100);
	f3.SetRect_Size(100, 100);
	f4.SetRect_Size(100, 100);
	f5.SetRect_Size(100, 100);
	f6.SetRect_Size(100, 100);
	tick.SetRect_Size(50, 50);

	Graphics word;
	TTF_Font* font = word.loadFont("SpeedRush.ttf", 20);
	SDL_Color color = { 0, 0, 0, 255 };
	std::string s1 = "W",s2="h",s3="a",s4="t ",s5="o",s6="o ",s7="u ", s8="L", s9="i",s10="k",s11="e?";
	bool c1 = false, c2 = false, c3 = false, c4 = false, c5 = false, c6 = false, c7 = false, c8 = false, c9 = false, c10 = false;
	
	
	while (!menu_clicked)
	{   
		SDL_RenderClear(renderer);
		SDL_GetMouseState(&mx, &my);
		SDL_RenderCopy(renderer, background, NULL, NULL);
		if (mx > 200 && mx < 347 && my>565 && my < 615) SDL_RenderCopy(renderer, menu_2, NULL, &menu_Rect);
		else {
			SDL_RenderCopy(renderer, menu_1, NULL, &menu_Rect);

			if (menu_Rect.x > 0)menu_Rect.x-=1;
			if (menu_Rect.y > 0)menu_Rect.y-=1;
			if (menu_Rect.w < 529)menu_Rect.w+=1;
			if (menu_Rect.h < 748)menu_Rect.h+=1;
		}
		if (menu_Rect.x == 0 && menu_Rect.y == 0 && menu_Rect.w == 529 && menu_Rect.h == 748)
		{   
			tick.showObject(renderer, 0);

			word.renderText(renderer, s1, font, color, 263, 425);
			if (!c1) {
				SDL_GetMouseState(&mx, &my);
				SDLCommonFunc::renderTexture(Mouse, renderer, mx - 25, my - 25, 120, 123); SDL_RenderPresent(renderer);  SDL_Delay(100); c1 = true; }
			word.renderText(renderer, s2, font, color, 277, 425);
			if (!c2) {
				SDL_GetMouseState(&mx, &my);
				SDLCommonFunc::renderTexture(Mouse, renderer, mx - 25, my - 25, 120, 123); SDL_RenderPresent(renderer);  SDL_Delay(100); c2 = true; }
			word.renderText(renderer, s3, font, color, 287, 425);
			if (!c3) {
				SDL_GetMouseState(&mx, &my);
				SDLCommonFunc::renderTexture(Mouse, renderer, mx - 25, my - 25, 120, 123); SDL_RenderPresent(renderer);  SDL_Delay(100); c3 = true; }
			word.renderText(renderer, s4, font, color, 297, 425);
			if (!c4) {
				SDL_GetMouseState(&mx, &my);
				SDLCommonFunc::renderTexture(Mouse, renderer, mx - 25, my - 25, 120, 123); SDL_RenderPresent(renderer);  SDL_Delay(100); c4 = true; }
			word.renderText(renderer, s5, font, color, 313, 425);
			if (!c5) {
				SDL_GetMouseState(&mx, &my);
				SDLCommonFunc::renderTexture(Mouse, renderer, mx - 25, my - 25, 120, 123); SDL_RenderPresent(renderer); SDL_Delay(100); c5 = true; }
			word.renderText(renderer, s6, font, color, 323, 425);
			if (!c6) {
				SDL_GetMouseState(&mx, &my);
				SDLCommonFunc::renderTexture(Mouse, renderer, mx - 25, my - 25, 120, 123); SDL_RenderPresent(renderer); SDL_Delay(100); c6 = true; }
			word.renderText(renderer, s7, font, color, 340, 425);
			if (!c7) {
				SDL_GetMouseState(&mx, &my);
				SDLCommonFunc::renderTexture(Mouse, renderer, mx - 25, my - 25, 120, 123); SDL_RenderPresent(renderer); SDL_Delay(100); c7 = true; }
			word.renderText(renderer, s8, font, color, 356, 425);
			if (!c8) {
				SDL_GetMouseState(&mx, &my);
				SDLCommonFunc::renderTexture(Mouse, renderer, mx - 25, my - 25, 120, 123); SDL_RenderPresent(renderer); SDL_Delay(100); c8 = true; }
			word.renderText(renderer, s9, font, color, 366, 425);
			if (!c9) {
				SDL_GetMouseState(&mx, &my);
				SDLCommonFunc::renderTexture(Mouse, renderer, mx - 25, my - 25, 120, 123); SDL_RenderPresent(renderer); SDL_Delay(100); c9 = true; }
			word.renderText(renderer, s10, font, color, 370, 425);
			if (!c10) {
				SDL_GetMouseState(&mx, &my);
				SDLCommonFunc::renderTexture(Mouse, renderer, mx - 25, my - 25, 120, 123); SDL_RenderPresent(renderer); SDL_Delay(100); c10 = true; }
			word.renderText(renderer, s11, font, color, 380, 425);
			
			
			
			if (my > 145 && my < 240)
			{
				if (mx > 107 && mx < 210) {
					f1.showObject(renderer, 0);
					
				}
				else if (mx > 220 && mx < 320) {
					f2.showObject(renderer, 0);
				}
				else if (mx > 340 && mx < 430) {
					f3.showObject(renderer, 0);
				}
			}
			else if (my > 265 && my < 360)
			{
				if (mx > 107 && mx < 210) {
					f4.showObject(renderer, 0);
				}
				else if (mx > 220 && mx < 320) {
					f5.showObject(renderer, 0);
				}
				else if (mx > 340 && mx < 430) {
					f6.showObject(renderer, 0);
				}
			}
		}
		
		std::cout << mx << "," << my << std::endl;
		SDLCommonFunc::renderTexture(Mouse, renderer, mx - 25, my - 25, 120, 123);
		SDL_RenderPresent(renderer);
	    
		

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
				if (my > 145 && my < 240)
				{
					if (mx > 107 && mx < 210) {
						tick.SetRect(100 + 25, 78 + 88);
						food = 1;
					}
					else if (mx > 220 && mx < 320) {
						tick.SetRect(213 + 25, 78 + 88);
						food = 2;
					}
					else if (mx > 340 && mx < 430) {
						tick.SetRect(328 + 25, 78 + 88);
						food = 3;
					}
				}
				else if (my > 265 && my < 360)
				{
					if (mx > 107 && mx < 210) {
						tick.SetRect(100 + 25, 200 + 88);
						food = 4;
					}
					else if (mx > 220 && mx < 320) {
						tick.SetRect(213 + 25, 200 + 88);
						food = 5;
					}
					else if (mx > 340 && mx < 430) {
						tick.SetRect(328 + 25, 200 + 88);
						food = 6;
					}
				}
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
			/*SDL_PointInRect()*/
			
			
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
			while (SDL_PollEvent(&g_even))
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
						SDL_Delay(300);
						SDL_RenderClear(renderer);
						background1 = SDLCommonFunc::loadTexture("PLAY_LIST_NEW.png", renderer);
						SDL_RenderCopy(renderer, background1, NULL, NULL);

						disc[0].loadImage("MUSIC_DISC.png", renderer);
						disc[0].SetSrcrect(0, 0, 1587, 1625);
						disc[0].SetRect_Size(140, 144);
						disc[0].SetRect(30, 248);
						disc[1] = disc[0];
						disc[2] = disc[0];
						disc[1].SetRect(30, 387);
						disc[2].SetRect(30, 520);
						disc[0].showObject(renderer, 1);
						disc[1].showObject(renderer, 1);
						disc[2].showObject(renderer, 1);

						SDLCommonFunc::renderTexture(Mouse, renderer, mx - 25, my - 25, 120, 123);
						SDL_RenderPresent(renderer);

						//Choose song:
						ChooseSong(Mouse,mx,my,background1);

						clicked = true;

					}
					else if (mouseX > 235 && mouseX < 320 && mouseY>650 && mouseY < 730)
					{
						SDL_RenderCopy(renderer, background3, NULL, NULL);
						SDLCommonFunc::renderTexture(Mouse, renderer, mx - 25, my - 25, 120, 123);
						Menu(Mouse,background3);

					}
				}
			}
		}
	}
}
//void SongNote(Meow cat[],bool& setRect) {
//  
//	if (!setRect) {
//		cat[0].SetRect(cat[0].GetRect().x, 0);
//		cat[1].SetRect(cat[1].GetRect().x, -20);
//		setRect = true;
//	}
//
//	cat[0].HandleMove(2);
//	cat[1].HandleMove(2);
//	
//	
//	
//
//	cat[0].showObject(renderer, 0);
//	cat[1].showObject(renderer, 0);
//}

void catRect(Meow cat[])
{
	cat[0].SetRect(cat[0].GetRect().x, 0);
	cat[1].SetRect(cat[1].GetRect().x, -30);
	cat[2].SetRect(cat[1].GetRect().x, -60);
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
	
    gMusic= graphics.loadMusic("SCARY_MUSIC.mp3");
	if (gMusic == NULL) std::cerr << "Music Error"<<SDL_GetError()<<std::endl;
	
	Mix_Music* Cheap_Thrills;
	
	Cheap_Thrills = graphics.loadMusic("CHEAP_THRILLS.mp3");
	if (Cheap_Thrills == NULL) std::cerr << "Music Error" << SDL_GetError() << std::endl;

	Mix_Music* mainMusic= graphics.loadMusic("MAIN_MUSIC.mp3");
	gMusic = mainMusic;
	
	
	
	
	//MAIN CHARACTER CALL:
	MainObject character;
	character.loadImage("VD_000.png", renderer);
	MainObject right_cat, left_cat, eat_right, eat_left;
	BaseObject game_over, victory, noSong;
	right_cat.loadImage("VD_CAT.png", renderer);
	left_cat.loadImage("VD_CAT_2.png", renderer);
	eat_right.loadImage("NHAI_RIGHT.png", renderer);
	eat_left.loadImage("NHAI_LEFT.png", renderer);
	game_over.loadImage("GAME_OVER.png", renderer);
	victory.loadImage("WON.png", renderer);
	noSong.loadImage("NO_SONG.png", renderer);

	game_over.SetRect_Size(424, 292);
	game_over.SetRect(50, 220);
	eat_right.SetRect_Size(25, 21);
	eat_left.SetRect_Size(25, 21);
	victory.SetRect_Size(424, 292);
	victory.SetRect(50, 220);
	noSong.SetRect_Size(238, 77);
	noSong.SetRect(150, 300);
	



	//FALL CAT:
	 int n = 307;
	 Meow cat[MAXN];	

	 Meow cat1,cat2,cat3,cat4,cat5,cat6;
	 
		 cat1.loadImage("06_apple_pie_dish.png", renderer);
	 
	 
		 cat2.loadImage("08_bread_dish.png", renderer);
	 
	
		 cat3.loadImage("16_burger_dish.png", renderer);
	 
	
		 cat4.loadImage("29_cookies_dish.png", renderer);
	 
	
		 cat5.loadImage("35_donut_dish.png", renderer);
	 

		 cat6.loadImage("56_hotdog_dish.png", renderer);
	 
	 
	 bool setRect_cat = false;
	/* cat[0].SetRect(cat[0].GetRect().x, 0);
	 cat[1].SetRect(cat[1].GetRect().x, -200);*/
	
	Uint32 ticks = SDL_GetTicks();
	Uint32 sprite = (ticks / 100) % 8;
	SDL_Texture* Mouse = NULL;
	Mouse = SDLCommonFunc::loadTexture("MOUSE_3.png", renderer);
	if (Mouse == NULL) 
		std::cerr << "MOUSE pic unload!" << SDL_GetError() << std::endl;
	int mx = 0, my = 0;
	SDL_ShowCursor(0);

	//POINT + CLOUD;
	int plus = 0;
	TTF_Font* font = graphics.loadFont("SpeedRush.ttf", 20);
	SDL_Color color = { 255, 255, 0, 255 };
	std::string point = "Score: ";
	
	SDL_Texture* nature_bg = SDLCommonFunc::loadTexture("NATURE_BG.png", renderer);
	SDL_Rect nature_scr = { 264,0,528,748 };
	BaseObject score_board;
	score_board.loadImage("SCORE.png", renderer);
	score_board.SetRect_Size(160, 55);
	score_board.SetRect(0, 0);
	
	Meow cloud;
	cloud.loadImage("CLOUD.png", renderer);
	cloud.SetRect_Size(238, 162);
	

	bool cat_state = true;
	while (!is_quit)
	{
		if (!choose_food) {
			for (int i = 0; i < n; i++) {
				switch (food) {
				case 1:
					cat[i] = cat1; break;
				case 2:
					cat[i] = cat2; break;
				case 3:
					cat[i] = cat3; break;
				case 4:
					cat[i] = cat4; break;
				case 5:
					cat[i] = cat5; break;
				case 6:
					cat[i] = cat6; break;
				};
			}
			choose_food = true;
		}
		eat_right.SetRect(character.GetRect().x + 32, character.GetRect().y + 19);
		eat_left.SetRect(character.GetRect().x + 5, character.GetRect().y + 19);
		
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
				right_cat.SetRect(character.GetRect().x, character.GetRect().y);
				left_cat.SetRect(character.GetRect().x, character.GetRect().y);
				


				if (g_even.key.keysym.sym == SDLK_LEFT)
				{
					cat_state = false;
					if (nature_scr.x > 0) nature_scr.x -= WIDTH_MAIN / 30;
				}
				else if (g_even.key.keysym.sym == SDLK_RIGHT)
				{
					cat_state = true;
					if (nature_scr.x < 386) nature_scr.x += WIDTH_MAIN / 30;
				}

			}
		}
		ticks = SDL_GetTicks();
		sprite = (ticks / 160) % 8;
			switch (cat_state) {
			case true:
				right_cat.SetSrcrect(sprite * 157, 0, 157, 185);
				break;
			case false:
				left_cat.SetSrcrect(sprite * 157, 0, 157, 185);
				break;
			};
		graphics.play(gMusic);
		while (call_bg == false) {
				choose_food = false;
				if(gMusic!=mainMusic)gMusic = mainMusic;
				CallBG(Mouse, mx, my);
				
		}
		
		if (song3_played) {
			Mix_HaltMusic(); gMusic = Cheap_Thrills;
			song3_played = false;
			graphics.playSong(gMusic);
			call_bg = true;
		}
		else if (song1_played || song2_played)
		{
			noSong.showObject(renderer, 0); SDL_RenderPresent(renderer); SDL_Delay(1500);
			call_bg = false;
			song1_played = false;
			song2_played = false;
		}
		if (call_bg) {




			SDL_RenderClear(renderer);

			/*if (song1_played == true) SDL_RenderCopy(renderer, song1_bg, NULL, NULL);
			else if (song2_played == true) SDL_RenderCopy(renderer, song2_bg, NULL, NULL);
			else if (song3_played == true) SDL_RenderCopy(renderer, song3_bg, NULL, NULL);*/
			SDL_RenderCopy(renderer, nature_bg, &nature_scr, NULL);

			//POINT: 
			cloud.CloudMove();
			cloud.showObject(renderer, 0);

			score_board.showObject(renderer, 0);
			point = "Score: " + std::to_string(plus);
			graphics.renderText(renderer, point, font, color, 52, 12);



			/*SDL_GetMouseState(&mx, &my);
			std::cerr << mx << " " << my << std::endl;
			SDLCommonFunc::renderTexture(Mouse, renderer, mx - 25, my - 25, 50, 45);*/


			if (cat_state) right_cat.showObject(renderer, 1);
			else left_cat.showObject(renderer, 1);
			/*SongNote(cat,setRect_cat);*/
			if (!setRect_cat) {
				catRect(cat);
				setRect_cat = true;
			}
			cat[0].HandleMove(200, -80);
			cat[1].HandleMove(220, -190);
			cat[2].HandleMove(230, -250);
			cat[3].HandleMove(240, -410);

			cat[4].HandleMove(240, -650); //+240
			cat[5].HandleMove(230, -760);//+110
			cat[6].HandleMove(220, -820);//+160
			cat[7].HandleMove(210, -980);//+160

			cat[8].HandleMove(190, -1230);//+250
			cat[9].HandleMove(180, -1340);//+110
			cat[10].HandleMove(170, -1400);//160
			cat[11].HandleMove(160, -1590);//190

			cat[12].HandleMove(160, -1890);
			cat[13].HandleMove(160, -1940);
			cat[14].HandleMove(160, -1970);
			cat[15].HandleMove(160, -2000);
			cat[16].HandleMove(160, -2030);
			cat[17].HandleMove(160, -2060);
			cat[18].HandleMove(160, -2090);
			cat[19].HandleMove(160, -2120);

			cat[20].HandleMove(150, -2450);
			cat[21].HandleMove(140, -2560);
			cat[22].HandleMove(130, -2620);
			cat[23].HandleMove(120, -2780);

			cat[24].HandleMove(110, -3040);
			cat[25].HandleMove(100, -3120);
			cat[26].HandleMove(90, -3250);
			cat[27].HandleMove(80, -3410);

			cat[28].HandleMove(100, -3610);
			cat[29].HandleMove(110, -3730);
			cat[30].HandleMove(120, -3820);
			cat[31].HandleMove(130, -3940);

			cat[32].HandleMove(150, -4240);
			cat[33].HandleMove(150, -4280);
			cat[34].HandleMove(150, -4320);
			cat[35].HandleMove(150, -4350);
			cat[36].HandleMove(150, -4380);
			cat[37].HandleMove(150, -4410);
			cat[38].HandleMove(150, -4440);
			cat[39].HandleMove(150, -4470);

			cat[40].HandleMove(160, -4660);
			cat[41].HandleMove(160, -4780);

			cat[42].HandleMove(180, -4890);
			cat[43].HandleMove(180, -4925);
			cat[44].HandleMove(180, -4955);
			cat[45].HandleMove(180, -4990);

			cat[46].HandleMove(190, -5140);
			cat[47].HandleMove(190, -5250);
			cat[48].HandleMove(190, -5330);

			cat[49].HandleMove(200, -5490);
			cat[50].HandleMove(210, -5525);
			cat[51].HandleMove(215, -5555);
			cat[52].HandleMove(220, -5600);

			cat[53].HandleMove(230, -5900);
			cat[54].HandleMove(230, -5930);

			cat[55].HandleMove(240, -6030);
			cat[56].HandleMove(240, -6140);

			cat[57].HandleMove(260, -6350);
			cat[58].HandleMove(260, -6385);
			cat[59].HandleMove(260, -6460);

			cat[60].HandleMove(250, -6670);
			cat[61].HandleMove(250, -6695);
			cat[62].HandleMove(250, -6735);
			cat[63].HandleMove(250, -6770);

			cat[64].HandleMove(270, -6950);
			cat[65].HandleMove(270, -7020);
			cat[66].HandleMove(270, -7120);

			cat[67].HandleMove(280, -7250);
			cat[68].HandleMove(280, -7275);
			cat[69].HandleMove(280, -7305);
			cat[70].HandleMove(280, -7350);

			cat[71].HandleMove(300, -7530);
			cat[72].HandleMove(310, -7610);
			cat[73].HandleMove(320, -7710);

			cat[74].HandleMove(330, -7810);
			cat[75].HandleMove(330, -7835);
			cat[76].HandleMove(330, -7865);
			cat[77].HandleMove(330, -7910);
			cat[78].HandleMove(330, -7940);
			cat[79].HandleMove(330, -7980);

			cat[80].HandleMove(310, -8180);
			cat[81].HandleMove(310, -8230);
			cat[82].HandleMove(310, -8280);

			cat[83].HandleMove(320, -8380);
			cat[84].HandleMove(320, -8430);
			cat[85].HandleMove(320, -8460);
			cat[86].HandleMove(320, -8490);

			cat[87].HandleMove(340, -8680);
			cat[88].HandleMove(340, -8730);
			cat[89].HandleMove(340, -8780);

			cat[90].HandleMove(350, -9000);
			cat[91].HandleMove(355, -9065);
			cat[92].HandleMove(360, -9135);
			cat[93].HandleMove(365, -9200);

			cat[94].HandleMove(370, -9410);
			cat[95].HandleMove(370, -9470);

			cat[96].HandleMove(390, -9610);

			cat[97].HandleMove(370, -9710);
			cat[98].HandleMove(370, -9780);
			cat[99].HandleMove(370, -9850);

			cat[100].HandleMove(350, -9990);

			cat[101].HandleMove(340, -10130);

			cat[102].HandleMove(330, -10230);
			cat[103].HandleMove(330, -10280);
			cat[104].HandleMove(320, -10330);
			cat[105].HandleMove(310, -10380);

			cat[106].HandleMove(340, -10550);

			cat[107].HandleMove(350, -10750);
			cat[108].HandleMove(350, -10810);
			cat[109].HandleMove(350, -10860);
			cat[110].HandleMove(350, -10900);
			cat[111].HandleMove(350, -10940);
			cat[112].HandleMove(350, -10980);
			cat[113].HandleMove(350, -11020);
			cat[114].HandleMove(350, -11060);
			cat[115].HandleMove(350, -11100);
			cat[116].HandleMove(350, -11140);
			cat[117].HandleMove(350, -11180);
			cat[118].HandleMove(350, -11220);
			cat[119].HandleMove(350, -11260);
			cat[120].HandleMove(350, -11300);
			cat[121].HandleMove(350, -11340);
			cat[122].HandleMove(350, -11380);
			cat[123].HandleMove(350, -11420);
			cat[124].HandleMove(350, -11460);
			cat[125].HandleMove(350, -11500);
			cat[126].HandleMove(350, -11540);
			cat[127].HandleMove(350, -11580);
			cat[128].HandleMove(350, -11620);
			cat[129].HandleMove(350, -11660);
			cat[130].HandleMove(350, -11700);

			cat[131].HandleMove(360, -11880);
			cat[132].HandleMove(370, -11980);
			cat[133].HandleMove(380, -12080);
			cat[134].HandleMove(390, -12210);
			cat[135].HandleMove(400, -12310);

			cat[136].HandleMove(390, -12490);
			cat[137].HandleMove(370, -12560);
			cat[138].HandleMove(360, -12660);
			cat[139].HandleMove(350, -12790);
			cat[140].HandleMove(340, -12910);

			cat[141].HandleMove(350, -13090);
			cat[142].HandleMove(350, -13150);
			cat[143].HandleMove(350, -13200);
			cat[144].HandleMove(350, -13240);
			cat[145].HandleMove(350, -13280);
			cat[146].HandleMove(350, -13320);
			cat[147].HandleMove(350, -13340);
			cat[148].HandleMove(350, -13380);
			cat[149].HandleMove(350, -13420);
			cat[150].HandleMove(350, -13460);
			cat[151].HandleMove(350, -13500);
			cat[152].HandleMove(350, -13540);
			cat[153].HandleMove(350, -13580);
			cat[154].HandleMove(350, -13620);
			cat[155].HandleMove(350, -13660);
			cat[156].HandleMove(350, -13700);
			cat[157].HandleMove(350, -13740);
			cat[158].HandleMove(350, -13780);
			cat[159].HandleMove(350, -13820);
			cat[160].HandleMove(350, -13840);
			cat[161].HandleMove(350, -13880);
			cat[162].HandleMove(350, -13920);
			cat[163].HandleMove(350, -13960);
			cat[164].HandleMove(350, -14000);

			cat[165].HandleMove(370, -14200);
			cat[166].HandleMove(360, -14270);
			cat[167].HandleMove(350, -14390);
			cat[168].HandleMove(340, -14440);

			cat[169].HandleMove(320, -14540);
			cat[170].HandleMove(310, -14640);
			cat[171].HandleMove(300, -14740);
			cat[172].HandleMove(310, -14840);
			cat[173].HandleMove(320, -14940);
			cat[174].HandleMove(323, -15040);
			cat[175].HandleMove(326, -15140);
			cat[176].HandleMove(329, -15240);
			cat[177].HandleMove(331, -15340);
			cat[178].HandleMove(333, -15440);
			cat[179].HandleMove(336, -15540);
			cat[180].HandleMove(339, -15640);
			cat[181].HandleMove(341, -15740);
			cat[182].HandleMove(344, -15840);
			cat[183].HandleMove(347, -15940);
			cat[184].HandleMove(350, -16040);
			cat[185].HandleMove(353, -16080);
			cat[186].HandleMove(357, -16120);

			cat[187].HandleMove(360, -16750);
			cat[188].HandleMove(370, -16863);
			cat[189].HandleMove(380, -16976);
			cat[190].HandleMove(390, -17090);

			cat[191].HandleMove(400, -17190);
			cat[192].HandleMove(410, -17290);
			cat[193].HandleMove(420, -17390);
			cat[194].HandleMove(430, -17490);
			cat[195].HandleMove(440, -17590);
			cat[196].HandleMove(450, -17690);
			cat[198].HandleMove(460, -17790);
			cat[199].HandleMove(470, -17890);
			cat[200].HandleMove(480, -17990);
			cat[201].HandleMove(490, -18090);
			cat[202].HandleMove(480, -18190);
			cat[203].HandleMove(470, -18290);
			cat[204].HandleMove(460, -18390);
			cat[205].HandleMove(450, -18490);
			cat[206].HandleMove(440, -18590);
			cat[207].HandleMove(430, -18690);
			cat[208].HandleMove(430, -18730);
			cat[209].HandleMove(430, -18770);

			cat[210].HandleMove(400, -19270);
			cat[211].HandleMove(390, -19370);
			cat[212].HandleMove(380, -19470);
			cat[213].HandleMove(370, -19570);
			cat[214].HandleMove(360, -19670);
			cat[215].HandleMove(350, -19770);
			cat[216].HandleMove(340, -19870);
			cat[217].HandleMove(330, -19970);
			cat[218].HandleMove(320, -20070);

			cat[219].HandleMove(310, -20270);
			cat[220].HandleMove(300, -20370);
			cat[221].HandleMove(290, -20470);
			cat[222].HandleMove(280, -20570);
			cat[223].HandleMove(270, -20670);
			cat[224].HandleMove(260, -20770);
			cat[225].HandleMove(250, -20870);
			cat[226].HandleMove(240, -20970);
			cat[227].HandleMove(230, -21070);
			cat[228].HandleMove(220, -21170);
			cat[229].HandleMove(210, -21270);
			cat[230].HandleMove(200, -21370);

			cat[231].HandleMove(170, -21670);
			cat[232].HandleMove(175, -21570);
			cat[233].HandleMove(180, -21670);
			cat[234].HandleMove(185, -21770);
			cat[235].HandleMove(190, -21870);
			cat[236].HandleMove(195, -21970);
			cat[237].HandleMove(200, -22070);
			cat[238].HandleMove(205, -22170);
			cat[239].HandleMove(210, -22270);

			cat[240].HandleMove(200, -22470);
			cat[241].HandleMove(190, -22570);
			cat[242].HandleMove(180, -22670);
			cat[243].HandleMove(170, -22770);
			cat[244].HandleMove(160, -22870);
			cat[245].HandleMove(150, -22970);
			cat[246].HandleMove(140, -23070);
			cat[247].HandleMove(130, -23170);
			cat[248].HandleMove(120, -23270);
			cat[249].HandleMove(110, -23370);
			cat[250].HandleMove(110, -23470);
			cat[251].HandleMove(110, -23570);

			cat[252].HandleMove(70, -24100);
			cat[253].HandleMove(65, -24300);
			cat[254].HandleMove(60, -24500);
			cat[255].HandleMove(55, -24700);
			cat[256].HandleMove(50, -24900);
			cat[257].HandleMove(45, -24940);
			cat[258].HandleMove(40, -24980);
			cat[259].HandleMove(35, -25020);
			cat[260].HandleMove(30, -25060);
			cat[261].HandleMove(35, -25100);
			cat[262].HandleMove(40, -25140);
			cat[263].HandleMove(45, -25180);
			cat[264].HandleMove(50, -25220);
			cat[265].HandleMove(55, -25260);
			cat[266].HandleMove(60, -25300);
			cat[267].HandleMove(65, -25340);
			cat[268].HandleMove(70, -25380);
			cat[269].HandleMove(75, -25420);
			cat[270].HandleMove(80, -25460);
			cat[271].HandleMove(85, -25500);
			cat[272].HandleMove(90, -25540);
			cat[273].HandleMove(95, -25580);
			cat[274].HandleMove(100, -25620);
			cat[275].HandleMove(105, -25660);
			cat[276].HandleMove(110, -25700);
			cat[277].HandleMove(115, -25740);
			cat[278].HandleMove(120, -25780);

			cat[279].HandleMove(130, -25880);

			cat[280].HandleMove(170, -26500);
			cat[281].HandleMove(175, -26700);
			cat[282].HandleMove(180, -26900);
			cat[283].HandleMove(185, -26700);
			cat[284].HandleMove(190, -27100);
			cat[285].HandleMove(195, -27140);
			cat[286].HandleMove(200, -27180);
			cat[287].HandleMove(205, -27220);
			cat[288].HandleMove(210, -27260);
			cat[289].HandleMove(215, -27300);
			cat[290].HandleMove(220, -27340);
			cat[291].HandleMove(225, -27480);
			cat[292].HandleMove(230, -27520);
			cat[293].HandleMove(240, -27560);
			cat[294].HandleMove(245, -27600);
			cat[295].HandleMove(250, -27640);
			cat[296].HandleMove(255, -27680);
			cat[297].HandleMove(260, -27720);
			cat[298].HandleMove(265, -27760);
			cat[299].HandleMove(270, -27800);
			cat[300].HandleMove(275, -27840);
			cat[301].HandleMove(280, -27880);
			cat[302].HandleMove(285, -27920);
			cat[303].HandleMove(290, -27960);
			cat[304].HandleMove(295, -28000);
			cat[305].HandleMove(300, -28040);
			cat[306].HandleMove(300, -28080);

			cat[307].HandleMove(310, -28180);
			for (int i = 0; i < 308; i++)
				cat[i].showObject(renderer, 0);

			for (int i = 0; i < 308; i++) {
				int bottom_x = cat[i].GetRect().x + WIDTH_MEOW / 2;

				if (character.GetRect().x < bottom_x && character.GetRect().x + WIDTH_MAIN / 2.5 >bottom_x && character.GetRect().y < cat[i].GetRect().y + 2 * HEIGHT_MEOW)
				{
					if (cat_state) {
						eat_right.showObject(renderer, 0);
					}
					else eat_left.showObject(renderer, 0);
				}
				if (character.GetRect().x < bottom_x && character.GetRect().x + WIDTH_MAIN / 2.5 >bottom_x && character.GetRect().y < cat[i].GetRect().y)
				{
					cat[i].SetLose(true);
					plus++;
					if (plus == 307)
					{
						victory.showObject(renderer, 0);
						SDL_RenderPresent(renderer);
						character.StartState();
						right_cat.SetRect(character.GetRect().x, character.GetRect().y);
						left_cat.SetRect(character.GetRect().x, character.GetRect().y);
						Mix_HaltMusic();
						gMusic = mainMusic;
						graphics.play(gMusic);

						SDL_Delay(2000);
						call_bg = false;
						plus = 0;
						setRect_cat = false;
					}
				}
				else if (cat[i].GetRect().y > SCREEN_HEIGHT - 90)
				{
					game_over.showObject(renderer, 0);
					SDL_RenderPresent(renderer);
					character.StartState();
					right_cat.SetRect(character.GetRect().x, character.GetRect().y);
					left_cat.SetRect(character.GetRect().x, character.GetRect().y);
					Mix_HaltMusic();
					gMusic = mainMusic;
					graphics.play(gMusic);

					SDL_Delay(2000);
					call_bg = false;
					plus = 0;
					setRect_cat = false;
				}
			}






			/*character.showObject(renderer, 1);*/



			SDL_RenderPresent(renderer);
		}
	}
	
	
	
	Mix_FreeMusic(gMusic);
	graphics.closeMusic();
	SDLCommonFunc::close();
	return 0;
}