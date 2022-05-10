#ifndef STACK_LINKED_LIST_LIBRARY_H
#define STACK_LINKED_LIST_LIBRARY_H

//#include "Polygon.h"



typedef struct linked_list Stack;


int push(Stack *stack, void* x, void* y);

int *inspect_bottom_of_stack(Stack *stack, int coordinates[2]);

int *inspect_top_of_stack(Stack *stack, int coordinates[2]);

int *pop(Stack *stack, int coordinates[2]);

void make_empty_stack(Stack *stack);

int stack_size(Stack *stack);

void edit_point(Stack *stack, int x_b, int y_b, int x_a, int y_a);

int empty_stack(Stack *stack);



Stack *create_stack();

typedef struct linked_list{
    void* x;
    void* y;
    struct linked_list *next;
}Stack;



#endif //STACK_LINKED_LIST_LIBRARY_H