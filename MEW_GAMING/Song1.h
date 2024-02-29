#ifndef SONG1_H_
#define SONG1_H_
#include "BaseObject.h" 

#define WIDTH_MEOW 35
#define HEIGHT_MEOW 35

namespace Song1
{
	void Song1_BG(SDL_Renderer* renderer);
}
class Meow : public BaseObject
{
public:
	Meow();
	~Meow();
	void HandleMove(const int& x_boder, const int& y_boder);
	
private:
	int x_val_;
	int y_val_;
};

#endif
