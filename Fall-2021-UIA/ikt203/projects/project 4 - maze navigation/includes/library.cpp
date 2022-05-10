#include "library.h"
#include <stdio.h>
#include <stdlib.h>




int is_empty_stack(Stack *stack)
{
    return (stack->next == NULL);
}


int push(Stack *stack, int x, int y){
    Stack *new_node = create_stack();
    if (new_node->position.x == INT_MIN && new_node->position.y == INT_MIN){
        return INT_MIN;
    }
    else{
        new_node->position.x = x;
        new_node->position.y = y;
        new_node->next = stack->next;
        stack->next = new_node;
        return 1;
    }
}


Position pop(Stack *stack){
    if (stack->next != NULL){
        Stack *head = stack->next;
        Stack *new_head = stack->next->next;
        stack->next = new_head;
        Position position;
        position.x = head->position.x;
        position.y = head->position.y;
        free(head);
        return position;
    }
    else
    {
        Position position;
        position.x = INT_MIN;
        position.y = INT_MIN;
        return position;
    }

}

Stack* create_stack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (stack == NULL){
        return NULL;
    }
    else
        stack->next = NULL;
    return stack;
}

