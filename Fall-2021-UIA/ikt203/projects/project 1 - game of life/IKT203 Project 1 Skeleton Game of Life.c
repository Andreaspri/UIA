#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 21
#define MAX_COLUMNS 44  

#define FALSE 0
#define TRUE 1

#define DELAY 100000000


/* show movie */
void ShowMovie(char [][], int);

/* main functions */
void PrintWorld(char [][], int, int);
void ClearWorld(char [][], int, int);
void CopyWorld(char [][], char [][], int, int);
void NextGeneration(char [][], char [][], int, int); 
void Animate(int, int);
int LiveCell(char [][], int, int);

/* neighboring cells in major wind directions */
int North(char [][], int, int);
int East(char [][], int, int);
int South(char [][], int, int);
int West(char [][], int, int);

/* neighboring cells in minor wind directions */
int NorthEast(char [][], int, int);
int SouthEast(char [][], int, int);
int SouthWest(char [][], int, int);
int NorthWest(char [][], int, int);


main()
{
        char emptyWorld[MAX_ROWS][MAX_COLUMNS] = {"!------------------------------------------!",
                                                  "!                                          !",
                                                  "!                                          !",   
                                                  "!                                          !",
                                                  "!                                          !",
                                                  "!                                          !",
                                                  "!                                          !",
                                                  "!                                          !",
                                                  "!                                          !",
                                                  "!                                          !",
                                                  "!                                          !",
                                                  "!                                          !",
                                                  "!                                          !",
                                                  "!                                          !",
                                                  "!                                          !",
                                                  "!                                          !",
                                                  "!                                          !",
                                                  "!                                          !",
                                                  "!                                          !",
                                                  "!                                          !",
                                                  "!------------------------------------------!"};
                                           
                                           
        char stableWorld[MAX_ROWS][MAX_COLUMNS] = {"!------------------------------------------!",
                                                   "!                                          !",
                                                   "!       xx xx                              !",   
                                                   "!        x x                               !",
                                                   "!        x x            xx                 !",
                                                   "!       xx xx           xx                 !",
                                                   "!                                          !",
                                                   "!                                          !",
                                                   "!                                          !",
                                                   "!       xxxx             x                 !",
                                                   "!                        xx                !",
                                                   "!                         x                !",
                                                   "!                                          !",
                                                   "!                                          !",
                                                   "!                                          !",
                                                   "!                                          !",
                                                   "!            x                             !",
                                                   "!            xxx                           !",
                                                   "!                                          !",
                                                   "!                                          !",
                                                   "!------------------------------------------!"};
         
        
        
        char oscillatingWorld[MAX_ROWS][MAX_COLUMNS] = {"!------------------------------------------!",
                                                        "!                                          !",
                                                        "!                                          !",   
                                                        "!                                          !",
                                                        "!                                          !",
                                                        "!       xx     xx                          !",
                                                        "!        xx   xx               xxx         !",
                                                        "!     x  x x x x  x                        !",
                                                        "!     xxx xx xx xxx                        !",
                                                        "!      x x x x x x                         !",
                                                        "!       xxx   xxx                          !",
                                                        "!                                          !",
                                                        "!       xxx   xxx                          !",
                                                        "!      x x x x x x               x         !",
                                                        "!     xxx xx xx xxx              x         !",
                                                        "!     x  x x x x  x              x         !",
                                                        "!        xx   xx                           !",
                                                        "!       xx     xx                          !",                                 
                                                        "!                                          !",
                                                        "!                                          !",
                                                        "!------------------------------------------!"};
                                                        
      
      
        char spaceShipWorld[MAX_ROWS][MAX_COLUMNS] = {"!------------------------------------------!",
                                                      "!                                          !",
                                                      "!     x                                    !",   
                                                      "!      x                                   !",
                                                      "!    xxx                                   !",
                                                      "!                                          !",
                                                      "!                                          !",
                                                      "!                                          !",
                                                      "!                                          !",
                                                      "!                                          !",
                                                      "!                                          !",
                                                      "!                                          !",
                                                      "!                                          !",
                                                      "!                                          !",
                                                      "!                                          !",
                                                      "!                                          !",
                                                      "!           x                              !",
                                                      "!          x                               !",
                                                      "!          xxx                             !",
                                                      "!                                          !",
                                                      "!------------------------------------------!"};
                                                      
                                                      

    
        
        while (TRUE)
        {
                ShowMovie(stableWorld, 10);
                ShowMovie(oscillatingWorld, 30);
                ShowMovie(spaceShipWorld, 300); 
        }
}


void ShowMovie(char world [][], int maxTicks)
{
        
}


/* print the grid of the world */
void PrintWorld(char world[][MAX_COLUMNS], int m, int n)
{
      
}


/* clear all cells of the world; caution: do not overwrite the array elements along the margins */ 
void ClearWorld(char world[][MAX_COLUMNS], int m, int n)
{
        
}


/* make a copy of the world */
void CopyWorld(char world[][MAX_COLUMNS], char copyWorld[][MAX_COLUMNS], int m, int n)
{
        
}


/* compute the next generation of the world */
void NextGeneration(char oldWorld[][MAX_COLUMNS], char newWorld[][MAX_COLUMNS], int m, int n)
{
        
}


/* insert sufficient printf("\n") statement to display the world in the same place as the 
   before and delay printing the next world sufficienty so that it looks like a movie */
void Animate(int tick, int delay)
{
        int i;
        
        
        printf("\nMy world at generation %d\n\n\n", tick);
          
        for (i=0; i<delay; i++);
                
        for (i=0; i<23; i++)
                printf("\n");
                
      
}


/* return 1 if a cell at (x, y) is alive and 0 otherwise */
int LiveCell(char world[][MAX_COLUMNS], int i, int j)
{
        
}


/* return 1 if a cell North of (x, y) is alive and 0 otherwise 
   special care must be taken to find the neighbors of cells 
   along the upper boundary of the world                        */                             
int North(char world[][MAX_COLUMNS], int row, int column)
{
        
}


/* return 1 if a cell Northeast of (x, y) is alive and 0 otherwise  
   special care must be taken to find the neighbors of cells 
   along the upper and right boundaries of the world              */  
int NorthEast(char world[][MAX_COLUMNS], int row, int column)
{
        
}


/* return 1 if a cell East of (x, y) is alive and 0 otherwise  
   special care must be taken to find the neighbors of cells 
   along the right boundary of the world                        */  
int East(char world[][MAX_COLUMNS], int row, int column)
{
            
}


/* return 1 if a cell Southeast of (x, y) is alive and 0 otherwise  
   special care must be taken to find the neighbors of cells 
   along the left and lower boundaries of the world             */  
int SouthEast(char world[][MAX_COLUMNS], int row, int column)
{
           
}



/* return 1 if a cell South of (x, y) is alive and 0 otherwise  
   special care must be taken to find the neighbors of cells 
   along the lower boundary of the world                        */  
int South(char world[][MAX_COLUMNS], int row, int column)
{
            
}


/* return 1 if a cell Southwest of (x, y) is alive and 0 otherwise  
   special care must be taken to find the neighbors of cells 
   along the lower and left boundaries of the world             */  
int SouthWest(char world[][MAX_COLUMNS], int row, int column)
{
            
}


/* return 1 if a cell West of (x, y) is alive and 0 otherwise  
   special care must be taken to find the neighbors of cells 
   along the left boundary of the world                        */  
int West(char world [][MAX_COLUMNS], int row, int column)
{
            
}


/* return 1 if a cell Northwest of (x, y) is alive and 0 otherwise  
   special care must be taken to find the neighbors of cells 
   along the left and upper boundaries of the world             */  
int NorthWest(char world [][MAX_COLUMNS], int row, int column)
{
            
}






