//
// Created by gabri on 07.09.2021.
//

#ifndef STACK_CALCULATOR_STACK_H
#define STACK_CALCULATOR_STACK_H

#define MINSTACKSIZE 50
#define MAXSTACKSIZE 500000
#define EMPTYTOS -1

typedef struct linked_list{
    int capacity;
    int topOfStack;
    char *array;
    struct linked_list *next;
} Stack_str;

typedef struct{
    int capacity;
    int topOfStack;
    int *array;
} Stack_int;

int isEmpty_str(Stack_str *stack);

int isFull_str(Stack_str *stack);

int push_str(Stack_str *stack, char element);

char stack_peek_str(Stack_str *stack);

char pop_str(Stack_str *stack, int index);

int top_index_str(Stack_str *stack);

int stack_size_str(Stack_str *stack);

void empty_stack_str(Stack_str *stack);

Stack_str *create_stack_str(int stack_size);

Stack_str *operators(Stack_str *stack);

Stack_str *delete_last_stack(Stack_str *stack);

Stack_str *last_element(Stack_str *stack);

int isEmpty_int(Stack_int *stack);

int isFull_int(Stack_int *stack);

int push_int(Stack_int *stack, int element);

int stack_peek_int(Stack_int *stack);

int pop_int(Stack_int *stack, int index);

int top_index_int(Stack_int *stack);

int stack_size_int(Stack_int *stack);

void empty_stack_int(Stack_int *stack);

Stack_int *create_stack_int(int stack_size);

int operator_count(Stack_str *stack);


#endif //STACK_CALCULATOR_STACK_H
