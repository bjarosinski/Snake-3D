#ifndef data_h
#define data_h
#include <string>
typedef struct
{
	std::string name;
	int difficulty;
	int res;
}options;

typedef struct
{
		std::string name;
		int points;
}player;

typedef struct
{
	int x;
	int y;
}point;

//player best_scorers[20];

enum course{left=1, straight, right};

enum area{empty=1, snake, apple};

#endif data