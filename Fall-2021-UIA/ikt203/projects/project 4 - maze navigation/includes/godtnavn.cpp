//
// Created by MSI Gaming PC on 9/26/2021.
//

// This is the stack for the sets of points

#include "godtnavn.h"
#include <stdio.h>
#include <stdlib.h>

int is_empty_stack_d(Double_position_stack *stack)
{
    return (stack->next == NULL);
}

int push_d(Double_position_stack *stack, Position start, Position end){
    Double_position_stack *new_node = create_stack_d();
    if (new_node == NULL){
        return INT_MIN;
    }
    else{
        new_node->start = start;
        new_node->end = end;
        new_node->next = stack->next;
        stack->next = new_node;
        return 1;
    }
}


Double_position_stack pop_d(Double_position_stack *stack){
    if (stack->next != NULL){
        Double_position_stack *head = stack->next;
        Double_position_stack *new_head = stack->next->next;
        stack->next = new_head;
        Double_position_stack positions;
        positions.start = head->start;
        positions.end = head->end;
        free(head);
        return positions;
    }
    else
    {
        printf("Super stack is empty! HO! HA!\n");
        Double_position_stack positions;
        positions.start.y = INT_MIN;
        positions.start.x = INT_MIN;
        positions.end.x = INT_MIN;
        positions.end.y = INT_MIN;
        return positions;
    }

}

Double_position_stack * create_stack_d()
{
    Double_position_stack *stack = (Double_position_stack*)malloc(sizeof(Double_position_stack));
    if (stack == NULL){
        return NULL;
    }
    else
        stack->next = NULL;
    return stack;
}
