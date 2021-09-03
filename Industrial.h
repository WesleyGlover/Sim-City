/* INDUSTRIAL */
#ifndef INDUSTRIAL
#define INDUSTRIAL
#include "Configuration.h"
#include "Industrial.cpp"




int industrialEvolution(Config * config);
int powerLineCheck(Config * config, int row, int col);
int adjPopCheck1(Config * config, int row, int col);
int adjPopCheck2(Config * config, int row, int col);
int findPop2(Config * config);
int findPop1(Config * config);
int findPop0(Config * config);




#endif //CONFIG
