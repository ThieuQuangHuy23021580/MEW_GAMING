#ifndef MAINOBJECT_H_
#define MAINOBJECT_H_
#include"BaseObject.h"

const int WIDTH_MAIN = 142;
const int HEIGHT_MAIN = 288;

class MainObject : public BaseObject
{
public:
  MainObject();
  ~MainObject();

  void HandleInputAction(SDL_Event events);
 
};

#endif