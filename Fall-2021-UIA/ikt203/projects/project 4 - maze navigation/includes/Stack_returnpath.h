//
// Created by MSI Gaming PC on 9/23/2021.
//

#ifndef PROJECT_4___MAZE_NAVIGATION_STACK_RETURNPATH_H
#define PROJECT_4___MAZE_NAVIGATION_STACK_RETURNPATH_H

#include "library.h"


class Current_stack
{
    // Access Specifier
    Stack *stack = (Stack*)create_stack();

    public:
        // Empty constructor
        Current_stack() {}

        Position pop_stack()
        {
            return pop(stack);
        }

        void push_stack(int x,int y)
        {
            push(stack,x,y);
        }

        int is_empty()
        {
            return is_empty_stack(stack);
        }

};


#endif //PROJECT_4___MAZE_NAVIGATION_STACK_RETURNPATH_H
