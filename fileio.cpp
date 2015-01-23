#include <fstream>
#include <sstream>
#include "fileio.h"
//#include "data.h"

std::fstream best;
std::fstream settings;

//std::string best_scorers[20][20];
int loadOptions(options & op)
{	
	std::string temp;
	
	settings.open("options.txt",std::ios::in);

	if(!settings.good()) return 0; 

	getline(settings,op.name);
	getline(settings, temp);
	std::istringstream tm(temp);
	tm>>op.difficulty;
	getline(settings, temp);
	std::istringstream tm2(temp);
	tm2>>op.res;
	settings.close();
	return 1;
}

int saveOptions(options op)
{
	std::ostringstream tm;
	settings.open("options.txt",std::ios::out);
	if(!settings.good()) return 0; 
	settings << op.name;

	tm << op.difficulty;
	
	settings << tm.str();

	tm<< op.res;

	settings << tm.str();

	settings.close();
	return 1;

}

int loadBest(player* ar)
{
	std::string temp;
	std::ostringstream tm;
	best.open("best_scores.txt",std::ios::in);

	if(!best.good()) return 0;

	for(int i=0;i<20;i++)
	{

		getline(best,ar[i].name);
		getline(best,temp);
		std::istringstream tm2(temp);
		tm2 >> ar[i].points;
	}
	
	best.close();
	return 1;

}

int saveBest(player* ar, player pl)
{
	player cur;
	std::ostringstream tm;
	best.open("best_scores.txt",std::ios::out);

	if(!best.good()) return 0;
	int i=0,k=0;
	while(i<20)
	{
		if(ar[k].points>=pl.points)
		{
			best<<ar[k].name;
			tm << ar[k].points;	
			best<< tm.str();
			k++;
		}

		else
		{
			best<<cur.name;
			tm << pl.points;	
			best<< tm.str();
		}

		i++;

	}

	best.close();
	return 1;

}