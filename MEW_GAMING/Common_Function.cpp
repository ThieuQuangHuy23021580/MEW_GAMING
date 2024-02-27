
#include "Common_Function.h"

SDL_Texture* SDLCommonFunc::loadTexture(std::string file_path,SDL_Renderer* renderer)
{
	SDL_Surface* load_image = NULL;
	load_image = IMG_Load(file_path.c_str());
	if (load_image == NULL) {
		std::cerr << "IMG_Load error:" << SDL_GetError() << std::endl;
	}
	SDL_Texture* texture = NULL;
	texture = SDL_CreateTextureFromSurface(renderer, load_image);
	if (texture == NULL) std::cerr << "LoadTexture is wrong!" << SDL_GetError() << std::endl;
	//SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	//SDL_SetTextureColorMod(texture, 0, 255, 255);
	SDL_FreeSurface(load_image);
	return texture;
}
void SDLCommonFunc::renderTexture(SDL_Texture* texture,SDL_Renderer* renderer, int x, int y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_RenderCopy(renderer, texture,NULL, &offset);
}
void SDLCommonFunc::close()
{
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}