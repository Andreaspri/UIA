#ifndef PROJECT_4___MAZE_NAVIGATION_LIBRARY_H
#define PROJECT_4___MAZE_NAVIGATION_LIBRARY_H
#include "queue.h"

typedef struct linked_list{
        Position position;
    struct linked_list *next;
}Stack;

int is_empty_stack(Stack* stack);

int push(Stack *stack, int x, int y);

Position pop(Stack *stack);

Stack *create_stack();

#endif //PROJECT_4___MAZE_NAVIGATION_LIBRARY_H