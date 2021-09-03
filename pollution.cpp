#include <iostream>
#include <string>
#include <vector>
#include "Configuration.h"
#include "Industrial.h"
using namespace std;

//initializes slots to zero
void pollution(Config * config)
{
	//char pollution[r][c];
	
	for(int row = 0; row <= config->region.size(); row++)
	{
		for(int col = 0; col <= config->region.size(); col++)
        	{
        		config->previousRegion[row][col] = '0';
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------
//finds where slot is Industrial
void setpollution(Config * config)
{
	for(int row = 0; row <= config->region.size(); row++)
	{
		for(int col = 0; col <= config->region.size(); col++)
        	{
			//setting Industrial slots into new map
            		if((config->region[row][col] == "I") || (config->region[row][col] == "i"))
            		{
               			config->previousRegion[row][col] = "I";
			}
        	}
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------
//setting up the new map
void newMap(Config * config)
{
	for(int row = 0; row <= config->region.size(); row++)
    	{
        	for(int col = 0; col <= config->region.size(); col++)
        	{
			//transferring slots from old map into new map
            		config->previousRegion[row][col] = config->regionDetail[row][col];
		}
    	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------
//sets three and begins spreading twos to adjacent slots
int setthreesAndtwos(Config * config)
{	
    	for(int row = 0; row <= config->region.size(); row++)
    	{
        	for(int col = 0; col <= config->region.size(); col++)
        	{
                	if(config->previousRegion[row][col] == "3")
                	{
                    		for(int a = -1; a <= 1; a++)
                    		{
                        		for(int b = -1; b <= 1; b++)
                        		{
                            			if((row + a >= 0)&&(row + a <= config->region.size())&&(col + b >= 0)&&(col + b <= config->region.size()))
                           			{
                                			if(config->previousRegion[row + a][col + b] != "3")
                                			{
                                    				config->previousRegion[row + a][col + b] = "2";
                                			}
                            			}
                        		}
                    		}
                	}
        	}
    	}

}
//----------------------------------------------------------------------------------------------------------------------------------------------------------
//spreading ones when adjacent to twos
int setOnes(Config * config)
{
    	for(int row = 0; row <= config->region.size(); row++)
    	{
        	for(int col = 0; col <= config->region.size(); col++)
        	{
                	if(config->previousRegion[row][col] == "2")
                	{
                    		for(int e = -1; e <= 1; e++)
                    		{
                        		for(int d = -1; d <= 1; d++)
                        		{
                            			if((row + e >= 0)&&(row + e <= config->region.size())&&(col + d >= 0)&&(col + d <= config->region.size()))
                            			{
                                			if((config->previousRegion[row + e][col + d] != "3") && (config->previousRegion[row + e][col + d] != "2"))
                                			{
                                    				config->previousRegion[row + e][col + d] = "1";
                                			}
                            			}
                        		}
                    		}
                	}
        	}
    	}

}
//----------------------------------------------------------------------------------------------------------------------------------------------------------
//spreads zeros when adjacent to ones
void setZeros(Config * config)
{
    	for(int row = 0; row <= config->region.size(); row++)
    	{
        	for(int col = 0; col <= config->region.size(); col++)
        	{
            		if((config->previousRegion[row][col] != "3") || (config->previousRegion[row][col] != "2") || (config->previousRegion[row][col] != "1"))
            		{
                		config->previousRegion[row][col] = "0";
            		}
        	}
    	}
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------
//counts the total number of pollution units
int countPollution(Config * config)
{
	int threecount;//increments by one
	int totalthree;//holds total three slot value

	int twocount;//increments by one
	int totaltwo;//holds total two slot value

	int onecount;//increments by one

	int totalcount;//total pollution units

	for(int row = 0; row <= config->region.size(); row++)
	{
		for(int col = 0; col <= config->region.size(); col++)
		{
			if(config->previousRegion[row][col] == "3")
			{
				threecount++;
			}
			if(config->previousRegion[row][col] == "2")
			{
				twocount++;
			}
			if(config->previousRegion[row][col] == "1")
			{
				onecount++;
			}
		}
	}

	totalthree = threecount * 3;
	totaltwo = twocount * 2;

	totalcount = totalthree + totaltwo + onecount;

	return totalcount;
}

//prints out new map of pollution
void outputMap(Config * config)
{	
    	for(int row = 0; row <= config->region.size(); row++)
    	{
        	for(int col = 0; col <= config->region.size(); col++)
        	{
            		cout << config->previousRegion[row][col];
        	}
        	cout << endl;
    	}

}

