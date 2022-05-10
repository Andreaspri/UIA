//
// Created by MSI Gaming PC on 9/26/2021.
//

#ifndef PROJECT_4___MAZE_NAVIGATION_GODTNAVN_H
#define PROJECT_4___MAZE_NAVIGATION_GODTNAVN_H

#include "queue.h"


typedef struct stack_part2
{
    Position start;
    Position end;
    struct stack_part2* next;
}Double_position_stack;


int is_empty_stack_d(Double_position_stack * stack);

int push_d(Double_position_stack *stack, Position start, Position end);

Double_position_stack pop_d(Double_position_stack *stack);

Double_position_stack *create_stack_d();




#endif //PROJECT_4___MAZE_NAVIGATION_GODTNAVN_H
