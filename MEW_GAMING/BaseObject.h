#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "Common_Function.h"

class BaseObject
{
public: 
	BaseObject();
	~BaseObject();
	bool loadImage(const char* file_name,SDL_Renderer* renderer);
	void showObject(SDL_Renderer* renderer, bool is_animation);
	

	void SetRect(const int& x, const int& y) { rect_.x = x; rect_.y = y; }
	void SetSrcrect(const int& x, const int& y, const int& w, const int& h) { srcrect.x = x; srcrect.y = y; srcrect.w = w; srcrect.h = h; }
	SDL_Rect GetRect() const { return rect_; }
	SDL_Texture* GetObject() { return objectTexture; }
protected:
	SDL_Rect rect_{};
	SDL_Rect srcrect{};
	SDL_Texture* objectTexture;
};

#endif
