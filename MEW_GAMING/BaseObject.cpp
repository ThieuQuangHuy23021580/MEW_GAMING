
#include "BaseObject.h"

BaseObject::BaseObject()
{
	rect_.x = 0;
	rect_.y = 0;
	
	objectTexture = NULL;
}

BaseObject::~BaseObject()
{
	if (objectTexture != NULL) {
		SDL_DestroyTexture(objectTexture);
	}
}

bool BaseObject::loadImage(const char* file_name,SDL_Renderer* renderer)
{
	objectTexture = SDLCommonFunc::loadTexture(file_name,renderer);
	if (objectTexture == NULL) {
		std::cerr << "objectTexture error:" << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

void BaseObject::showObject(SDL_Renderer* renderer,bool is_animation) {
	if (objectTexture != NULL&&!is_animation) {
		SDLCommonFunc::renderTexture(objectTexture,renderer, rect_.x , rect_.y, rect_.w, rect_.h);
	}
	else if (objectTexture != NULL && is_animation) {
		SDLCommonFunc::renderTexture(objectTexture, renderer, rect_.x, rect_.y, rect_.w, rect_.h,srcrect);
	}
}
