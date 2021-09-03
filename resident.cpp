#include "Configuration.h"
#include "resident.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>

//function returns the number of T/#'s (powerlines) that are adjacent to a location in the matrix   
int countPowerline( int row, int col, Config* config)
{
        int countT = 0;

	for( int r = row-1; r <= row+1; r++)
        {
               	for( int c = col-1; c <= col+1; c++)
               	{	
			if (r >=0 && r < config->region.size() && c >=0 && c < config->region[r].size())
			{
                       		if( config->region[r][c] == "T" || config->region[r][c] == "#" )
                       		{
					if( r != row && c != col) //no duplicates
					{
                               			countT++;
					}
                       		}
			}	
               	}
       	}
        
	return countT;
}

//function returns the number of #s >= 1 that are adjacent to a 1 in the matrix 
int countRes1( int row, int col, Config* config)
{
        int count1 = 0;

        //isolating only bordering slots to count adjacent 1's
        for( int r = row-1; r <= row+1; r++)
        {
                for( int c = col-1; c <= col+1; c++)
                {       
			if (r >=0 && r < config->region.size() && c >=0 && c < config->region[r].size())
			{
                        	if( config->regionDetail[r][c] >= "1" && config->regionDetail[r][c] > "6" && config->region[r][c] == "R" )
                        	{       
					if( r != row && c != col) //no duplicates
                                        {
                                		count1++;
					}
                        	}
			}
                }
        }
      
        return count1;
}

//function returns the number of #s >= 2 that are adjacent to a 2 in the matrix  
int countRes2( int row, int col, Config* config)
{
        int count2 = 0;

        //isolating only bordering slots to count adjacent 2's
        for( int r = row-1; r <= row+1; r++)
        {

		for( int c = col-1; c <= col+1; c++)
                {
                        if (r >=0 && r < config->region.size() && c >=0 && c < config->region[r].size())
			{
				if( config->regionDetail[r][c] >= "2" && config->region[r][c] == "R" )
                        	{
                                	if( r != row && c != col) //no duplicates
					{
						count2++;
					}
                        	}
			}
                }
        }
        return count2;
}

//function returns the number of #s >= 3 that are adjacent to a 3 in the matrix  
int countRes3( int row, int col, Config* config)
{
        int count3 = 0;

        //isolating only bordering slots to count adjacent 3's
        for( int r = row-1; r <= row+1; r++)
        {
                for( int c = col-1; c <= col+1; c++)
                {
			if (r >=0 && r < config->region.size() && c >=0 && c < config->region[r].size())
			{
                        	if( config->regionDetail[r][c] >= "3" && config->region[r][c] == "R" )
                        	{
                                	if( r != row && c != col) //no duplicates
                                        {
						count3++;
					}
                        	}
			}
                }
        }
        return count3;
}

//function returns the number of #s >= 4 that are adjacent to a 4 in the matrix  
int countRes4( int row, int col, Config* config)
{
        int count4 = 0;

        //isolating only bordering slots to count adjacent 4's
        for( int r = row-1; r <= row+1; r++)
        {
                for( int c = col-1; c <= col+1; c++)
                {
                        if (r >=0 && r < config->region.size() && c >=0 && c < config->region[r].size())
			{
				if( config->regionDetail[r][c] >= "4" && config->region[r][c] == "R")
				{
					if( r != row && c != col) //no duplicates
                                        {
						count4++;
					}
				}
			}
                }
        }
        return count4;
}

//function locates the cells that have an R
int locRes0( Config* config)
{
	int count = 0;

	//read through whole board 
        for( int r = 0; r < config->region.size() ; r++)
        {
                for( int c = 0; c < config->region[r].size() ; c++)
		{
                        //only changes numbers if originally was an R 
                        if( config->region[r][c] == "R" )
                        {
				//checking if current board has an R
				if( config->regionDetail[r][c] == "R")
                                {
                                        count += countPowerline(r, c, config);
                                        count += countRes1(r, c, config);

                                        if( count >= 1) //if poweline adj meets condition
                                        {
                                                config->regionDetail[r][c] = "1";//update board
						return count;
                                        }
                                }

                        }//end of if originally an R
                }//end of column for
        }//end of row for
}

//function locates the cells that have an 1
int locRes1( Config* config)
{
	int count = 0;

        //read through whole board 
        for( int r = 0; r < config->region.size() ; r++)
        {
                for( int c = 0; c < config->region[r].size() ; c++)
                {
                        //only changes numbers if originally was an R 
                        if( config->region[r][c] == "R" )
                        {
                                //checking if current board has an 1
                                if( config->regionDetail[r][c] == "1")
                                {
                                        count += countRes1(r, c, config);

                                        if( count >= 2) //if resident 1 adj meets condition
                                        {
                                                config->regionDetail[r][c] = "2";//update board
                                                return count;
                                        }
                                }

                        }//end of if originally an R
                }//end of column for
        }//end of row for
}

//function locates the cells that have an 2
int locRes2( Config* config)
{
	int count = 0;

        //read through whole board 
        for( int r = 0; r < config->region.size() ; r++)
        {
                for( int c = 0; c < config->region[r].size() ; c++)
                {
                        //only changes numbers if originally was an R 
                        if( config->region[r][c] == "R" )
                        {
                                //checking if current board has an 2
                                if( config->regionDetail[r][c] == "2")
                                {
                                        count += countRes1(r, c, config);

                                        if( count >= 4) //if resident 2 adj meets condition
                                        {
                                                config->regionDetail[r][c] = "3";//update board
                                                return count;
                                        }
                                }

                        }//end of if originally an R
                }//end of column for
        }//end of row for
}

//function locates the cells that have an 3
int locRes3( Config* config)
{
	int count = 0;

        //read through whole board 
        for( int r = 0; r < config->region.size() ; r++)
        {
                for( int c = 0; c < config->region[r].size() ; c++)
                {
                        //only changes numbers if originally was an R 
                        if( config->region[r][c] == "R" )
                        {
                                //checking if current board has an 3
                                if( config->regionDetail[r][c] == "3")
                                {
                                        count += countRes1(r, c, config);

                                        if( count >= 6) //if resident 3 adj meets condition
                                        {
                                                config->regionDetail[r][c] = "4";//update board
                                                return count;
                                        }
                                }

                        }//end of if originally an R
                }//end of column for
        }//end of row for
}
	
//function locates the cells that have an 4
int locRes4( Config* config)
{
	int count = 0;

        //read through whole board 
        for( int r = 0; r < config->region.size() ; r++)
        {
                for( int c = 0; c < config->region[r].size() ; c++)
                {
                        //only changes numbers if originally was an R 
                        if( config->region[r][c] == "R" )
                        {
                                //checking if current board has an 4
                                if( config->regionDetail[r][c] == "4")
                                {
                                        count += countRes1(r, c, config);

                                        if( count >= 8) //if resident 4 adj meets condition
                                        {
                                                config->regionDetail[r][c] = "5";//update board
                                                return count;
                                        }
                                }

                        }//end of if originally an R
                }//end of column for
        }//end of row for
}

//function will check for Residential updates
int searchRes( Config* config)
{
	bool actionComplete = false;
   	int counter = 0;

	
	//CHECKING FOR RESIDENTIAL CELL WITH POPULATION OF 4
	if( actionComplete == false )
        {
                counter = locRes4(config);

                // If action was recorded then don't try the rest
                if( counter != 0 )
                {
                        actionComplete = true;
                }
        }
        

	//CHECKING FOR RESIDENTIAL CELL WITH POPULATION OF 3
        // reseting the counter just in case
        counter = 0;
        if( actionComplete == false )
        {
                counter = locRes3(config);

                // If action was recorded then don't try the rest
                if( counter != 0 )
                {
                        actionComplete = true;
                }
        }


   	//CHECKING FOR RESIDENTIAL CELL WITH POPULATION OF 2
	// reseting the counter just in case
        counter = 0;
	if( actionComplete == false )
   	{
      		counter = locRes2(config);

      		// If action was recorded then don't try the rest
      		if( counter != 0 )
     		{
        		actionComplete = true;
      		}
   	}

   	
	//CHECKING FOR RESIDENTIAL CELL WITH POPULATION OF 1
	// reseting the counter just in case
        counter = 0;
	if( actionComplete == false)
   	{
      		counter = locRes1(config);

      		// If action was recorded then don't try the rest
		if( counter != 0 )
      		{
       		  	actionComplete = true;
      		}
   	}

   	//CHECKING FOR RESIDENTIAL CELL WITH POPULATION OF 0
	// reseting the counter just in case
        counter = 0;
	if( actionComplete == false )
   	{
      		counter = locRes0(config);

      		// If action was recorded then don't try the rest
      		if( counter != 0 )
      		{
         		actionComplete = true;
     	 	}
   	}

   return 0;
}
