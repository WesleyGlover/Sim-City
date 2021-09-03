#ifndef CONFIGERATION
#define CONFIGERATION
#include "Configuration.cpp"

using namespace std;
struct Config;

// storing the information from the given line into the variable
void storeValue(string key, string value, Config* config);

// Printing the region area to the console
void printRegion(Config * config);

// Printing out the details of the region
void printDetails(Config * config);

// Inserting the information from a previously opened file
void insertInfo(Config * config);

// Getting region from the input
void getRegion(Config * config);

//Opening a file with name provided, as well as return the ifstream
void openFile(string fileName, ifstream &file);

// Closing the file
void closeFile(ifstream &file);




#endif //CONFIG
