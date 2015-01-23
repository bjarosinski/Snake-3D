#include "snake.h"

Snake::Snake(){

	size=2;
	location=new point[100];
	location[0].x=0;
	location[0].y=1;
	location[1].x=0;
	location[1].y=0;
}

Snake::Snake(point* loc, int st){

	location=loc;
	size=st;

}

Snake::~Snake(){

	delete [] location;

}

int Snake::EatApple(){

	size++;

	if(size>50) return 0;

	//location[size-1]=	


}