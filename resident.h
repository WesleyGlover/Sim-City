#ifndef RESIDENT
#define RESIDENT
#include <iostream>
#include "Configuration.h"
#include "resident.cpp"
using namespace std;

//function returns the number of T's or #'s  that are adjacent to a R in the matrix 
int countPowerline( int row, int col, Config* config);
//function returns the number of #s >= 1 that are adjacent to a 1 in the matrix
int countRes1( int row, int col, Config* config);
//function returns the number of #s >= 2 that are adjacent to a 2 in the matrix
int countRes2( int row, int col, Config* config);
//function returns the number of #s >= 3 that are adjacent to a 3 in the matrix
int countRes3( int row, int col, Config* config);
//function returns the number of #s >= 4 that are adjacent to a 4 in the matrix
int countRes4( int row, int col, Config* config);
//function locates the cells that have an R
int locRes0( Config* config);
//function locates the cells that have an 1
int locRes1( Config* config);
//function locates the cells that have an 2
int locRes2( Config* config);
//function locates the cells that have an 3
int locRes3( Config* config);
//function locates the cells that have an 4
int locRes4( Config* config);

//function will check for Residential updates
int searchRes( Config* config );

#endif
