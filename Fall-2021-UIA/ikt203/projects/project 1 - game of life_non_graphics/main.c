#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "patterns.h"
//#include <graphics.h>
// Tried to converted to C++ due to graphics.h requiring c++ std libraries
// https://stackoverflow.com/questions/29040857/fatal-error-sstream-no-such-file-or-directory
// C++ did not support the size of the char arrays in use here though, and would not compile - added 1 to MAX_ variables
// Fixed bug in graphics.h (double defined int right).
// Still after all this, it would not run.

#define FALSE 0
#define TRUE 1

#define DELAY 100000000


/* show movie */
void ShowMovie(char [][MAX_COLUMNS], int);

/* main functions */
void PrintWorld(char [][MAX_COLUMNS]);
void ClearWorld(char [][MAX_COLUMNS]);
void CopyWorld(char [][MAX_COLUMNS], char [][MAX_COLUMNS]);
void NextGeneration(char [][MAX_COLUMNS], char [][MAX_COLUMNS]);
void Animate(int, int);
int LiveCell(char [][MAX_COLUMNS], int, int);

/* neighboring cells in major wind directions */
int North(char [][MAX_COLUMNS], int, int);
int East(char [][MAX_COLUMNS], int, int);
int South(char [][MAX_COLUMNS], int, int);
int West(char [][MAX_COLUMNS], int, int);

/* neighboring cells in minor wind directions */
int NorthEast(char [][MAX_COLUMNS], int, int);
int SouthEast(char [][MAX_COLUMNS], int, int);
int SouthWest(char [][MAX_COLUMNS], int, int);
int NorthWest(char [][MAX_COLUMNS], int, int);

bool CompareWorlds(Patterns *head, char [][MAX_COLUMNS], Patterns *equal);


int main()
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

    char spaceShipWorldMix[MAX_ROWS][MAX_COLUMNS] = {"!------------------------------------------!",
                                                  "!                                          !",
                                                  "!                                          !",
                                                  "!                                          !",
                                                  "!    xxx                                   !",
                                                  "!      x                                   !",
                                                  "!     x                                    !",
                                                  "!                                          !",
                                                  "!                                          !",
                                                  "!                                          !",
                                                  "!  xx                                      !",
                                                  "!  x x                                     !",
                                                  "!  x                                 xx    !",
                                                  "!                                   x x    !",
                                                  "!                                     x    !",
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
        //ShowMovie(spaceShipWorldMix, 300);
    }
}




void ShowMovie(char originalWorld [][MAX_COLUMNS], int maxTicks)
{
    // Something to animate the game simulation
    char newWorld[MAX_ROWS][MAX_COLUMNS];
    char world[MAX_ROWS][MAX_COLUMNS];
    CopyWorld(originalWorld, world); // To avoid messing up the original world
    Patterns *head = (Patterns*)malloc(sizeof(Patterns));
    CopyWorld(world, head->world);
    head->index = 0;
    head->next = NULL;

    bool found_repeat = false;

    // Keeps track of repeating pattern time
    int repeating_pattern = 0;
    int repeating_pattern_index = 0;

    // print initial world
    PrintWorld(world);

    // Later used to retrieving index offset of the repeating pattern
    Patterns *pattern = (Patterns*)malloc(sizeof(Patterns));
    pattern->next = NULL;

    // Insert generation + spacing
    Animate(0, DELAY);
    Patterns *current_element = head;
    for (int i = 1; i < maxTicks; ++i) {
        // simulate next step of world
        CopyWorld(world, newWorld); // copy world to get the borders, since we never simulate those.
        ClearWorld(newWorld); // Wipe the center
        NextGeneration(world, newWorld); // Generate new center
        CopyWorld(newWorld, world); // Prepares the cycle for a new loop

        if (!found_repeat){
            current_element->next = (Patterns*)malloc(sizeof(Patterns));
            current_element = current_element->next;
            CopyWorld(world, current_element->world);
            current_element->index = i;
            current_element->next = NULL;
        }

        // Repeating pattern logic:
        // store world state in list
        // after each "newWorld" simulation compare every world in list to newWorld
        // If match found, return index of world in list
        if (!found_repeat && CompareWorlds(head, world, pattern)){
            repeating_pattern = i-pattern->index;
            repeating_pattern_index = i;
            found_repeat = true;
        }

        // print world
        PrintWorld(world);
        if (!found_repeat)
        {
            printf("Repeating pattern not found yet\n");
        }
        else
        {
            if (repeating_pattern == 1){
                printf("Found repeating pattern at index %d, but pattern is static!\n", repeating_pattern_index);
            }
            else{
                printf("Found repeating pattern at index %d after %d cycles\n", repeating_pattern_index, repeating_pattern);
            }
        }

        // Insert generation + spacing
        Animate(i, DELAY);
    }
}

bool CompareWorlds(Patterns *head, char world[][MAX_COLUMNS], Patterns *pattern){
    Patterns *current_element = head;
    bool state = true;
    while (current_element->next != NULL){
        for (int row = 1; row < MAX_ROWS-1; row++){
            for (int column = 1; column < MAX_COLUMNS-1; column++){
                char i = current_element->world[row][column];
                char f = world[row][column];
                if (i != f){
                    state = false;
                    goto end;
                }
            }
        }
        end:
        if (state){
            pattern->index = current_element->index;
            break;
        }
        current_element = current_element->next;
        if (current_element->next != NULL)
            state = true;
    }
    return state;
}


/* print the grid of the world */
void PrintWorld(char world[][MAX_COLUMNS])
{
    // Iterate through each 1d and print the entire array
    for (int i = 0; i < MAX_ROWS; ++i) {
        for (int j = 0; j < MAX_COLUMNS; ++j) {
            printf("%c", world[i][j]);
        }
        printf("\n");
    }
}


/* clear all cells of the world; caution: do not overwrite the array elements along the margins */
void ClearWorld(char world[][MAX_COLUMNS])
{
    // Loop through each array of world (double for loop) except first and last element
    // ! = wall is skipped
    // - = wall is skipped
    // Set value to " "
    for (int i = 1; i < MAX_ROWS-1; ++i) {
        for (int j = 1; j < MAX_COLUMNS-1; ++j) {
            world[i][j] = ' ';
        }
    }
}


/* make a copy of the world */
void CopyWorld(char world[][MAX_COLUMNS], char copyWorld[][MAX_COLUMNS])
{
    // iterate through max col/row, set copyWorld to equivalent value in world (including borders)
    for (int i = 0; i < MAX_ROWS; ++i) {
        for (int j = 0; j < MAX_COLUMNS; ++j) {
            copyWorld[i][j] = world[i][j];
        }
    }
}


/* compute the next generation of the world */
void NextGeneration(char oldWorld[][MAX_COLUMNS], char newWorld[][MAX_COLUMNS])
{
    // Iterate through each element of oldWorld.
    // apply rules for game of life to each cell.
    // Insert new values in newWorld

    // Apply game logic:
    // 1.	Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
    // 2.	Any live cell with more than three live neighbours dies, as if by overcrowding.
    // 3.	Any live cell with two or three live neighbours lives on to the next generation.
    // 4.	Any dead cell with exactly three live neighbours becomes a live cell.

    int alive_cells = 0;
    for (int row = 1; row < MAX_ROWS-1;row++){
        for (int column = 1; column < MAX_COLUMNS-1;column++){
            alive_cells += North(oldWorld, row, column);
            alive_cells += South(oldWorld, row, column);
            alive_cells += West(oldWorld, row, column);
            alive_cells += East(oldWorld, row, column);
            alive_cells += NorthEast(oldWorld, row, column);
            alive_cells += NorthWest(oldWorld, row, column);
            alive_cells += SouthEast(oldWorld, row, column);
            alive_cells += SouthWest(oldWorld, row, column);

            if (LiveCell(oldWorld,row,column)){
                if (alive_cells < 2 || alive_cells > 3)
                    newWorld[row][column] = ' ';
                else
                    newWorld[row][column] = 'x';
            }
            else if (!LiveCell(oldWorld,row,column) && alive_cells == 3)
                newWorld[row][column] = 'x';

            alive_cells = 0;
        }
    }
}


/* insert sufficient printf("\n") statement to display the world in the same place as the
   before and delay printing the next world sufficiently so that it looks like a movie */
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
    // Check if a space has cell. Return 1 if so. Otherwise return 0.
    if (world[i][j] == 'x')
        return 1;
    else
        return 0;
}


/* return 1 if a cell North of (x, y) is alive and 0 otherwise
   special care must be taken to find the neighbors of cells
   along the upper boundary of the world                        */
int North(char world[][MAX_COLUMNS], int row, int column)
{
    if (row == 1)
        row = MAX_ROWS-2;
    else
        row -= 1;
    return LiveCell(world,row,column);
}


/* return 1 if a cell Northeast of (x, y) is alive and 0 otherwise
   special care must be taken to find the neighbors of cells
   along the upper and right boundaries of the world              */
int NorthEast(char world[][MAX_COLUMNS], int row, int column)
{
    if (row == 1)
        row = MAX_ROWS-2;
    else
        row -= 1;
    if (column == MAX_COLUMNS-2)
        column = 1;
    else
        column += 1;
    return LiveCell(world,row,column);
}


/* return 1 if a cell East of (x, y) is alive and 0 otherwise
   special care must be taken to find the neighbors of cells
   along the right boundary of the world                        */
int East(char world[][MAX_COLUMNS], int row, int column)
{
    if (column == MAX_COLUMNS-2)
        column = 1;
    else
        column += 1;
    return LiveCell(world,row,column);
}


/* return 1 if a cell Southeast of (x, y) is alive and 0 otherwise
   special care must be taken to find the neighbors of cells
   along the left and lower boundaries of the world             */
int SouthEast(char world[][MAX_COLUMNS], int row, int column)
{
    if (row == MAX_ROWS-2)
        row = 1;
    else
        row += 1;
    if (column == MAX_COLUMNS-2)
        column = 1;
    else
        column += 1;
    return LiveCell(world,row,column);
}



/* return 1 if a cell South of (x, y) is alive and 0 otherwise
   special care must be taken to find the neighbors of cells
   along the lower boundary of the world                        */
int South(char world[][MAX_COLUMNS], int row, int column)
{
    if (row == MAX_ROWS-2)
        row = 1;
    else
        row += 1;
    return LiveCell(world,row,column);
}


/* return 1 if a cell Southwest of (x, y) is alive and 0 otherwise
   special care must be taken to find the neighbors of cells
   along the lower and left boundaries of the world             */
int SouthWest(char world[][MAX_COLUMNS], int row, int column)
{
    if (row == MAX_ROWS-2)
        row = 1;
    else
        row += 1;
    if (column == 1)
        column = MAX_COLUMNS - 2;
    else
        column -= 1;
    return LiveCell(world,row,column);
}


/* return 1 if a cell West of (x, y) is alive and 0 otherwise
   special care must be taken to find the neighbors of cells
   along the left boundary of the world                        */
int West(char world [][MAX_COLUMNS], int row, int column)
{
    if (column == 1)
        column = MAX_COLUMNS - 2;
    else
        column-= 1;
    return LiveCell(world,row,column);
}


/* return 1 if a cell Northwest of (x, y) is alive and 0 otherwise
   special care must be taken to find the neighbors of cells
   along the left and upper boundaries of the world             */
int NorthWest(char world [][MAX_COLUMNS], int row, int column)
{
    if (row == 1)
        row = MAX_ROWS - 2;
    else
        row -= 1;
    if (column == 1)
        column = MAX_COLUMNS -2;
    else
        column -= 1;
    return LiveCell(world,row,column);

}


