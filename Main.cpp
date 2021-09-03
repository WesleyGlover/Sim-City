#include <iostream>
#include <fstream>
#include "Configuration.h"
#include "Industrial.h"
#include "Simulate.h"

using namespace std;


int main()
{
   // Creating a config struct
   Config * config;
   config = new Config;

   // Calling function to populate the config
   insertInfo(config);

   // Running simulation
   runSimulation(config);


   return 0;
}
