#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

struct Config
{
   public:
      string regionFile;
      vector< vector<string> > region;
      vector< vector<string> > regionDetail;
      vector< vector<string> > previousRegion;
      int timeLimit;
      int refreshRate;
      int timeStep;
      int totalResident;
      int availableResident;
      int totalGoods;
      int availableGoods;
      int indusPop;
      int commPop;

};

//Opening a file with name provided, as well as return the ifstream
void openFile(string fileName, ifstream &file)
{
   // Opening the file
   file.open(fileName.c_str());

   // checking if the file opened
   if(!file)
   {
      //File did NOT open
      cout << "The file \"" << fileName << "\" could not be opened." << endl;
   }
}

// Closing the file
void closeFile(ifstream &file)
{
   file.close();
}

// storing the information from the given line into the variable
void storeValue(string key, string value, Config* config)
{
      if(key == "Region Layout")
      {
         config->regionFile = value;
        // cout << "Region File Saved: " << config->regionFile << endl;
      }
      else if (key == "Time Limit")
      {
         config->timeLimit = stoi(value);
        // cout << "Time Limit Saved: " << config->timeLimit << endl;
      }
      else if (key == "Refresh Rate")
      {
         config->refreshRate = stoi(value);
        // cout << "Refresh Rate Saved: " << config->refreshRate << endl;
      }
      else
      {
         cout << "There was an error matching " << key << " to any of the given cases!" << endl;
      }
   }

// Printing the region area to the console
void printRegion(Config * config)
{
    // Printing out the frame
   for (int width = 0; width < ((config->regionDetail[0].size() * 2) + 2); width++)
   {
      cout << "-";
   }
   cout << endl;

   // Establishing variables for printing the vectors out
   int counterColumn = 0;
   int counterRow = 0;
   // Printing the vector
   // Looping through the outer vector (Only size 1)
   for (int i = 0; i < config->regionDetail.size(); i++)
   {
      cout << "|";
      for (int j = 0; j < config->regionDetail[i].size(); j++)
      {
         cout << config->regionDetail[i][j] << " ";
      }
      cout << "|" << endl;
   }

   // Printing out the frame
   for (int width = 0; width < ((config->regionDetail[0].size() * 2) + 2); width++)
   {
      cout << "-";
   }
   cout << endl;
}

// Printing out the details
void printDetails(Config * config)
{
   // Printing out time step
   cout << "Time Step: " << config->timeStep << endl;
   // Printing out workers and goods available at the end of the step
   cout << "Available Workers " << config->availableResident << " Available Goods " << config->availableGoods << endl;
}


// Getting region from the input
void getRegion(Config * config)
{
   ifstream file;
   string fileName;
   fileName = config->regionFile;

   // Opening the file
   file.open(fileName.c_str());

   // checking if the file opened
   if(!file)
   {
      //File did NOT open
      cout << "The file \"" << fileName << "\" could not be opened." << endl;
      exit(-1);
   }

   // populating the vector
   string c;
   string first;
   string second;
   // looping while the file is not at end
   while (file.good())
   {
      // looping gathering the row and splitting it up
      while (getline(file, c))
      {
         // creating empty row
         vector<string> temp;

         //looping until the whole row is broken up
         int position = 0;
         int length = 1;
         string cSub;
         for (cSub = c.substr(position, length); position < c.size(); position = position + 2)
         {
            cSub = c.substr(position, length);
            // Pushing the newly broken string into the vector
            temp.push_back(cSub);
         }
         // storing the inner vector (row) to the outer vector
         config->region.push_back(temp);
         config->regionDetail.push_back(temp);
         config->previousRegion.push_back(temp);
      }
   }

   // Printing array
   cout << "Initial Region State" << endl;
   printRegion(config);

   // Setting variables to default values
   config->commPop = 0;
   config->indusPop = 0;
   config->availableGoods = 0;
   config->availableResident = 0;
   config->totalGoods = 0;
   config->totalResident = 0;

   // Next Function is the simulation which goes here!
  // runSimulation(config);

}



// Inserting the information from a previously opened file
void insertInfo(Config * config)
{
   // declaring variables
   string fileName;
   string line;
   string key;
   string value;
   ifstream file;

   // Opening file to read from
   cout << "Beginning simulation" << endl;
   cout << "Please enter the name of the configuration file:";
   cin >> fileName;
   openFile(fileName, file);

   // Gathering the region file name
   // collecting the first line of the document
   while (getline(file, line))
   {
      // creating a new insertion of the already existing inserted line
      istringstream is_line(line);

      // if the getline is true (getting the line up to ':' and store it into key)
      if(getline(is_line, key, ':'))
      {
         // if getline is true (storing the value after the ':' into value)
         if(getline(is_line, value))
         {
            storeValue(key, value, config);
         }
      }
   }
   getRegion(config);
}
