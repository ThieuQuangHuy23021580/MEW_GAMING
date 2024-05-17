#ifndef MAINOBJECT_H_
#define MAINOBJECT_H_
#include"BaseObject.h"

const int WIDTH_MAIN = 157;
const int HEIGHT_MAIN = 185;

class MainObject : public BaseObject
{
public:
  MainObject();
  ~MainObject();

  void HandleInputAction(SDL_Event events);
  void StartState();
 
};

#endif