#include "data.h"


player actual;

course board[10][10];

int set_player(options op, player* pl)
{
	pl->name=op.name;
	pl->points=0;

}