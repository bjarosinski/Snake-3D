#ifndef fileio
#define fileio
#include <fstream>
#include "data.h"

extern std::fstream best;
extern std::fstream settings;

extern int loadOptions(options & op);
extern int saveOption(options op);
extern int loadBest(player* ar);
extern int saveBest(player*ar, player pl);
#endif