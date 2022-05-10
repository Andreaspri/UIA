#include "library.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int push(Stack *stack, void* x, void* y){
    Stack *new_node = create_stack();
    if (new_node == nullptr){
        printf("Error - Unable to allocate memory to new stack node during push.\n");
        return INT_MIN;
    }
    else{


        new_node->x = (int*)x;
        new_node->y = (int*)y;

        new_node->next = (Stack*)stack->next;
        stack->next = (Stack*)new_node;

        return 1;
    }
}

void edit_point(Stack *stack, int x_b, int y_b, int x_a, int y_a)
{
    Stack *current_node = stack;
    int index = 0;
    while (current_node->next != nullptr)
    {
        if ((*(int*)((Stack*)current_node->next)->x == x_b) && (*(int*)((Stack*)current_node->next)->y == y_b)){

            *(int*)((Stack*)current_node->next)->x = x_a;
            *(int*)((Stack*)current_node->next)->y = y_a;
            if (index != 0){
                goto end;
            }
        }
        index++;
        current_node = (Stack*)current_node->next;
    }
    end:;
}

int *inspect_bottom_of_stack(Stack *stack, int coordinates[2]){
    int* temp = (int*) malloc(sizeof(int)*2);
    for (Stack *current_node = stack; current_node->next != nullptr; current_node = (Stack*)current_node->next)
    {
        temp[0] = *(int*)((Stack*)current_node->next)->x;
        temp[1] = *(int*)((Stack*)current_node->next)->y;
    }
    return temp;
}

int *inspect_top_of_stack(Stack *stack, int coordinates[2]){
    if (!empty_stack(stack))
    {
        coordinates[0] = *(int*)((Stack*)stack->next)->x;
        coordinates[1] = *(int*)((Stack*)stack->next)->y;
        return coordinates;
    }
    else
    {
        printf("Error - Impossible operation. Attempting to inspect empty stack.\n");
        return nullptr;
    }
}

int *pop(Stack *head, int coordinates[2]){
    if (head->next != nullptr){
        Stack *node_to_delete = (Stack*)head->next;
        head->next = ((Stack*)head->next)->next;
        coordinates[0] = *(int*)node_to_delete->x;
        coordinates[1] = *(int*)node_to_delete->y;
        free(node_to_delete);
        return coordinates;
    }
    else
        return nullptr;
}

int stack_size(Stack *stack){
    int size = 0;
    Stack *current_node = stack;
    while (current_node->next != nullptr){
        current_node = current_node->next;
        size++;
    }
    return size;
}

void make_empty_stack(Stack *stack){
    Stack *current_node = stack;
    while (current_node->next != nullptr){
        int temp_coordinates[2];
        temp_coordinates[0] = *(int*)current_node->x;
        temp_coordinates[1] = *(int*)current_node->y;
        pop(stack, temp_coordinates);
    }
}

int empty_stack(Stack *stack){
    return stack->next == nullptr;
}

Stack *create_stack(){
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (stack == nullptr){
        printf("Error - Unable to allocate memory to new stack.\n");
        // pass
    }
    else
        stack->next = nullptr;
    return (Stack*)stack;
}

