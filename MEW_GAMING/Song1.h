#ifndef SONG1_H_
#define SONG1_H_
#include "BaseObject.h" 

const int WIDTH_MEOW = 60;
const int HEIGHT_MEOW = 57;

namespace Song1
{
	void Song1_BG(SDL_Renderer* renderer);
}
class Meow : public BaseObject
{
public:
	Meow();
	~Meow();
	void HandleMove( );
	bool GetMove() { return is_move;}
	bool SetMove(bool set) { is_move = set; }
	void SetLose(bool lose) { is_lose = lose; }
	bool GetLose() { return is_lose; }
protected:
	/*int x_val_;
	int y_val_;*/
	bool is_move = false;
	bool is_lose = false;
	bool drop_effect = true;
	bool delay = false;
	
};


#endif
