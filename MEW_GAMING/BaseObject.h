#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "Common_Function.h"

class BaseObject
{
public: 
	BaseObject();
	~BaseObject();
	bool loadImage(const char* file_name);
	void showObject();

	void SetRect(const int& x, const int& y) { rect_.x = x; rect_.y = y; }
	SDL_Rect GetRect() const { return rect_; }
	SDL_Texture* GetObject() { return objectTexture; }
protected:
	SDL_Rect rect_;
	SDL_Texture* objectTexture;
};

#endif
