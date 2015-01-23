#ifndef Snakes_H
#define Snakes_H

#include "data.h"

class Snake {

private:

	int size;
	point* location;

public:

	Snake();
	Snake(point* loc, int st);
	int MoveSnake(course dir);
	int EatApple();
	int getSize();
	point* getLocation();
	~Snake();
};

#endif Snake