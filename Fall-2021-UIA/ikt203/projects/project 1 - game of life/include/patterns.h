//
// Created by Nixxen on 04.09.2021.
//


#define MAX_COLUMNS 45 // Added +1 for cpp
#define MAX_ROWS 21
#define PIXEL 20

#ifndef PROJECT_1___GAME_OF_LIFE_PATTERNS_H
#define PROJECT_1___GAME_OF_LIFE_PATTERNS_H

typedef struct patterns{
    char world[MAX_ROWS][MAX_COLUMNS];
    int index;
    struct patterns *next;
} Patterns;
#endif //PROJECT_1___GAME_OF_LIFE_PATTERNS_H
