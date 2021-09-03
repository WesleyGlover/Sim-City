#include "Configuration.h"
#include "Industrial.h"
#include "Pollution.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

// Simulation stage
void simmulate(Config * config)
{
   // Assigning last stage to previous region before making changes
   for (int i = 0; i < config->region.size(); i++)
   {
      for  (int j = 0; j < config->region[i].size(); j++)
      {
         config->previousRegion[i][j] = config->regionDetail[i][j];
      }
   }

   // Calling functions to simulate changes
   industrialEvolution(config);
}

// Ending simulation
void endSimulation(Config * config)
{
   cout << "Final Region State" << endl;

   // Printing out the region
   printRegion(config);

   // PRINT OUT POLUTION HERE

   // Printing out the total populations for each section
   cout << "The total populations for the region are:" << endl;
   cout << "Residential: " << config->totalResident << endl;
   cout << "Industrial: " << config->indusPop << endl;
   cout << "Commercial: " << config->commPop << endl;

   // Calling the pollution function

   // ENTER THE POLUTION TOTAL VARIBLE HERE------------------>
   cout << "The total amount of pollution in the region is " <<" " << " units." << endl;

   // Calculate the populations of a selected area (inputed by user)

   // Once thats all done
   cout << "Simulation complete" << endl;
   exit(0);
}


// Runs the Simulation
void runSimulation(Config * config)
{
   // Counter to run the simulation with a refresh rate
   int counter = 0;

   // running the stages per refresh rate
   while (counter != config->refreshRate)
   {
      // running the stage
      simmulate(config);
      counter++;
   }

   // Testing if any changes were made
   int different = 0;
   //looping through element wise
   for (int i = 0; i < config->region.size(); i++)
   {
      for (int j = 0; j < config->region[i].size(); j++)
      {
         if (config->regionDetail[i][j] == config->previousRegion[i][j])
         {
            // No changes
         }
         else
         {
            // Yes Changes
            different++;
         }
      }
   }

   // If changes were NOT detected
   if (different == 0)
   {
      endSimulation(config);
   }

   // Increasing the time step counter
   config->timeStep++;

   // Printing out the details
   printDetails(config);

   // Printing out the outcome of the stage(s) within the refresh
   printRegion(config);

   // Getting next refresh
   runSimulation(config);
}
