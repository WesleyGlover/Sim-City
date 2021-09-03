#include "Industrial.h"
#include "Configuration.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;


// checking power lines connected adjacent
int powerLineCheck(Config * config, int row, int col)
{
   int counter = 0;

   //checking all adjacent within the scope
   for( int r = row-1; r <= row+1; r++)
   {
      for( int c = col-1; c <= col+1; c++)
      {
         // Making sure the coordinate are within bounds
         if (r >=0 && r < config->region.size() && c >=0 && c < config->region[r].size())
         {
            // If found increment counter
            if( config->region[r][c] == "T" || config->region[r][c] == "#" )
            {
               counter++;
            } // END OF if( config->region[r][c] == "T" || config->region[r][c] == "#" )
         } // END OF if (r >=0 && r < config->region.size() && c >=0 && c < config->region[r].size())
      } // END OF for( int c = col-1; c <= col+1; c++)
   } // END OF for( int r = row-1; r <= row+1; r++)
   // Return the counter value
   return counter;
}

int adjPopCheck1(Config * config, int row, int col)
{
   int counter = 0;

   //checking all adjacent within the scope
   for( int r = row-1; r <= row+1; r++)
   {
      for( int c = col-1; c <= col+1; c++)
      {
         // Making sure the coordinate are within bounds
         if (r >=0 && r < config->region.size() && c >=0 && c < config->region[r].size())
         {
            // If found increment counter
            if( config->regionDetail[r][c] >= "1" && config->region[r][c] == "I" && config->regionDetail[r][c] <= "9")
            {
               // Checking to make sure you aren't counting your self
               if (r == row && c == col)
               {
                  // DO NOTHING CAUSE THAT YOUR MIDDLE
               }
               else
               {
                  // Increment counter
                  counter++;
               }
            }
         } // END OF if (r >=0 && r < config->region.size() && c >=0 && c < config->region[r].size())
      } // END OF for( int c = col-1; c <= col+1; c++)
   } // END OF for( int r = row-1; r <= row+1; r++)
   // Return the counter value
   return counter;
}

int adjPopCheck2(Config * config, int row, int col)
{
   int counter = 0;

   //checking all adjacent within the scope
   for( int r = row-1; r <= row+1; r++)
   {
      for( int c = col-1; c <= col+1; c++)
      {
         // Making sure the coordinate are within bounds
         if (r >=0 && r < config->region.size() && c >=0 && c < config->region[r].size())
         {
            // If found increment counter
            if( config->regionDetail[r][c] >= "2" && config->region[r][c] == "I")
            {
               // Check to make sure you aren't counting your self
               if (r == row && c == col)
               {
                  // DO NOTHING
               }
               else
               {
                  // Increment counter
                  counter++;
               }
            }
         } // END OF if (r >=0 && r < config->region.size() && c >=0 && c < config->region[r].size())
      } // END OF for( int c = col-1; c <= col+1; c++)
   } // END OF for( int r = row-1; r <= row+1; r++)
   // Return the counter value
   return counter;
}

// Finding the spaces that have an I
int findPop2(Config * config)
{
   int counter = 0;
   // looping for a 2 and a corresponding I
   for (int i = 0; i < config->region.size(); i++)
   {
      for (int j = 0; j < config->region[i].size(); j++)
      {
         if (config->regionDetail[i][j] == "2" && config->region[i][j] == "I")
         {
            // DO SOMETHING
            counter = counter + adjPopCheck2(config, i, j);

            // if population found
            if (counter >= 4)
            {
               // Update the board
               config->regionDetail[i][j] = "3";
               // Assign the workers (take away available)
               config->availableResident = config->availableResident - 2;
               // Incrementing the industrial population by 1
               config->indusPop++;
               // Incrementing the available good and total goods
               config->availableGoods++;
               config->totalGoods++;
               // Return to other function
               return counter;
            }
            else
            {
               counter = 0;
            }
         }
      }
   }
   return 0;
}

int findPop1(Config * config)
{
   int counter = 0;
   // looping for a 1 and a corresponding I
   for (int i = 0; i < config->region.size(); i++)
   {
      for (int j = 0; j < config->region[i].size(); j++)
      {
         if (config->regionDetail[i][j] == "1" && config->region[i][j] == "I")
         {
            // check for adjacent populations >= 1
            counter = counter + adjPopCheck1(config, i, j);

            // if population found
            if (counter >= 2)
            {
               // Update the board
               config->regionDetail[i][j] = "2";
               // Assign the workers (take away available)
               config->availableResident = config->availableResident - 2;
               // Incrementing the industrial population by 1
               config->indusPop++;
               // Incrementing the available good and total goods
               config->availableGoods++;
               config->totalGoods++;
               // Return to other function
               return counter;
            }
            else
            {
               counter = 0;
            }
         }
      }
   }
   return 0;
}

// Finds the population of size 0
int findPop0(Config * config)
{
   int counter = 0;
   // Looping though the region looking for Industrial zone
   for (int i = 0; i < config->region.size(); i++)
   {
      for (int j = 0; j < config->region[i].size(); j++)
      {
         // If found check if there is an adjacent power line
         if (config->regionDetail[i][j] == "I" && config->region[i][j] == "I")
         {
            // Checking for power line and/or Adjacent population >=1
            counter = counter + powerLineCheck(config, i, j);
            counter = counter + adjPopCheck1(config, i, j);
            // IF power line if found
            if (counter >= 1)
            {
               // Update the board
               config->regionDetail[i][j] = "1";
               // Assign the workers (take away available)
               config->availableResident = config->availableResident - 2;
               // Incrementing the industrial population by 1
               config->indusPop++;
               // Return to other function
               return counter;
            }
         }
      }
   }
   // If nothing is found to update just return to other function
   return counter;
}

// The main Decision maker of the program
int industrialEvolution(Config * config)
{
   // Checking variables
   bool actionComplete = false;
   int counter = 0;

   // Checking for population of 2
   if (config->availableResident >= 2 && actionComplete == false)
   {
      counter = findPop2(config);

      // If action was recorded then don't try the rest
      if (counter != 0)
      {
         actionComplete = true;
      }
   }

   // reseting the counter just in case
   counter = 0;

   // Checking for population of 1
   if (config->availableResident >= 2 && actionComplete == false)
   {
      counter = findPop1(config);

      // If action was recorded then don't try the rest
      if (counter != 0)
      {
         actionComplete = true;
      }
   }

   // resetting the counter just incase
   counter = 0;

   // Checking for population of 0
   if (config->availableResident >= 2 && actionComplete == false)
   {
      counter = findPop0(config);

      // If action was recorded then don't try the rest
      if (counter != 0)
      {
         actionComplete = true;
      }
   }

   return 0;
}
