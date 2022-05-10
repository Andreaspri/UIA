#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <myString.h>
#include "stack.h"


// Returns true (or 1) if stack is empty
int isEmpty_str(Stack_str *stack)
{
    return stack->topOfStack == EMPTYTOS;
}

// Returns true (or 1) if stack is full
int isFull_str(Stack_str *stack)
{
    return stack->topOfStack == stack->capacity + EMPTYTOS;
}

// Pushes value to top of stack
// On error returns -1
int push_str(Stack_str *stack, char element)
{
    if (isFull_str(stack)){
        printf("Error - Can not push to stack. Stack Overflow condition!\n");
        return -1;
    }
    else{
        stack->topOfStack++;
        stack->array[stack->topOfStack] = element;
        return 0;
    }
}

// Clears the last stack of the linked list of stacks.
Stack_str *delete_last_stack(Stack_str *stack){
    Stack_str *current_stack = stack;
    Stack_str *prev_stack;

    // Find the last stack in the list
    while (current_stack->next != NULL){
        prev_stack = current_stack;
        current_stack = current_stack->next;
    }

    // Un-allocate the memory for the stack
    free(current_stack->next);

    // NULL-Terminate the previous next pointer to make it the new last element
    prev_stack->next = NULL;

    return stack;
}

// Returns the value at the top of the stack without clearing it
// Error on empty stack, CHAR_MIN
char stack_peek_str(Stack_str *stack)
{
    if (isEmpty_str(stack)){
        printf("Error - Can not peek into an empty stack\n");
        return CHAR_MIN;
    }
    return stack->array[stack->topOfStack];
}

// Returns the length of a linked-list of stacks
int operator_count(Stack_str *stack){
    Stack_str *current_stack = stack;
    int count = 0;
    while (current_stack != NULL){
        count += top_index_str(current_stack)+1;
        current_stack = current_stack->next;
    }
    return count;
}

// Returns a operator stack compressed to one stack based on the given linked list of stacks
Stack_str *operators(Stack_str *stack){
    Stack_str *operator_list = create_stack_str(MINSTACKSIZE);
    operator_list->next = NULL;
    Stack_str *current_stack = stack;
    while (current_stack != NULL){
        while (!isEmpty_str(current_stack)){
            push_str(operator_list, pop_str(current_stack, 0));
        }
        current_stack = current_stack->next;
    }
    return operator_list;
}

// Returns the last stack in a linked list of stacks
Stack_str *last_element(Stack_str *stack){
    Stack_str *current_stack = stack;
    while (current_stack->next != NULL){
        current_stack = current_stack->next;
    }
    return current_stack;
}

// Returns value at given index after removing it from the stack and restructuring the stack.
// Error returns CHAR_MIN
char pop_str(Stack_str *stack, int index)
{
    // Clears the value at the given index of the stack,
    // restructure stack if index is below top of stack
    // returns value
    // On error returns CHAR_MIN
    if (isEmpty_str(stack))
        return CHAR_MIN;
    char temp_element = stack->array[index];
    if (index < stack->topOfStack){
        for (int i = index;i < (stack->topOfStack); i++){
            stack->array[i] = stack->array[i+1];
            if (i == (stack->topOfStack-1))
                stack->topOfStack = i;
        }
    }
    else{
        stack->topOfStack = index-1;
    }

    return temp_element;
}

// Returns the index of the top of the stack
// Error on empty stack, CHAR_MIN
int top_index_str(Stack_str *stack)
{
    if (isEmpty_str(stack)){
        //printf("Error - Can not get index of empty stack\n");
        return CHAR_MIN;
    }
    else
        return stack->topOfStack;
}

// Returns the maximum size of the stack
int stack_size_str(Stack_str *stack)
{
    return stack->capacity;
}

// Set top of stack to empty value
void empty_stack_str(Stack_str *stack)
{
    stack->topOfStack = EMPTYTOS;
}

// Creates an empty character stack of size stack_size. If an error happens, NULL is returned
Stack_str *create_stack_str(int stack_size){
    // Cancel if elements are too low
    if (stack_size<MINSTACKSIZE)
    {
        printf("Error - Stack size too small!\n");
        return NULL;
    }
    // Cancel if elements are too high
    if (stack_size>=MAXSTACKSIZE)
    {
        printf("Error - Stack size too big!\n");
        return NULL;
    }

    // Define stack and allocate memory
    Stack_str *stack = (Stack_str *)malloc(sizeof (Stack_str));

    // Abort if allocation fails
    if (stack == NULL)
    {
        printf("Error - Memory allocation for stack failed. Out of memory!\n");
        return NULL;
    }

    // Set stack capacity to stack_size
    stack->capacity = stack_size;

    // Allocate more memory to the array
    stack->array = (char *)malloc(stack_size*sizeof(char));

    // Abort if allocation fails
    if (stack->array == NULL)
    {
        printf("Error - Memory allocation for stack array failed. Out of memory!\n");
        return NULL;
    }
    // Make the stack empty
    empty_stack_str(stack);

    // NULL-terminate the next pointer
    stack->next = NULL;
    return stack;
}

// Returns true (or 1) if stack is empty
int isEmpty_int(Stack_int *stack)
{
    return stack->topOfStack == EMPTYTOS;
}

// Returns true (or 1) if stack is full
int isFull_int(Stack_int *stack)
{
    return stack->topOfStack == stack->capacity - 1;
}

// Pushes value to top of stack.
// On error returns -1
int push_int(Stack_int *stack, int element)
{
    if (isFull_int(stack)){
        printf("Error while pushing. Stack Overflow condition!\n");
        return -1;
    }
    else{
        stack->topOfStack++;
        stack->array[stack->topOfStack] = element;
        return 0;
    }
}

// Returns the value at the top of the stack without clearing it
// Error on empty stack, INT_MIN
int stack_peek_int(Stack_int *stack)
{
    if (isEmpty_int(stack)){
        printf("Error - Can not peek into an empty stack\n");
        return INT_MIN;
    }
    return stack->array[stack->topOfStack];
}

// Returns value at given index after removing it from the stack and restructuring the stack.
// Error returns INT_MIN
int pop_int(Stack_int *stack, int index)
{
    if (isEmpty_int(stack)){
        printf("Error - Can not pop from empty stack\n");
        return INT_MIN;
    }

    int temp_element = stack->array[index];
    if (index < stack->topOfStack){
        for (int i = index;i < (stack->topOfStack); i++){
            stack->array[i] = stack->array[i+1];
            if (i == (stack->topOfStack-1))
                stack->topOfStack = i;
        }
    }
    else{
        stack->topOfStack = index-1;
    }

    return temp_element;
}

// Returns the index of the top of the stack
// Error on empty stack, INT_MIN
int top_index_int(Stack_int *stack)
{
    if (isEmpty_int(stack)){
        printf("Error - Can not get index from empty stack!\n");
        return INT_MIN;
    }
    else
        return stack->topOfStack;
}

// Returns the max size of the stack
int stack_size_int(Stack_int *stack)
{
    return stack->capacity;
}

// Set top of stack to empty value
void empty_stack_int(Stack_int *stack)
{
    stack->topOfStack = EMPTYTOS;
}

// Creates an empty int stack of size stack_size. If an error happens, NULL is returned
Stack_int *create_stack_int(int stack_size)
{
    // Cancel if elements are too low
    if (stack_size<MINSTACKSIZE)
    {
        printf("Error - Stack size too small!\n");
        return NULL;
    }
    // Cancel if elements are too high
    if (stack_size>=MAXSTACKSIZE)
    {
        printf("Error - Stack size too big!\n");
        return NULL;
    }

    // Define stack and allocate memory
    Stack_int *stack = (Stack_int *)malloc(sizeof (Stack_int));

    // Abort if allocation fails
    if (stack == NULL)
    {
        printf("Error - Memory allocation for stack failed. Out of memory!\n");
        return NULL;
    }

    // Set stack capacity to stack_size
    stack->capacity = stack_size;

    // Allocate more memory to the array
    stack->array = (int *)malloc(stack_size*sizeof(int));

    // Abort if allocation fails
    if (stack->array == NULL)
    {
        printf("Error - Memory allocation for stack array failed. Out of memory!\n");
        return NULL;
    }

    // Make the stack empty
    empty_stack_int(stack);
    return stack;
}

