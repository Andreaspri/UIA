//
// Created by MSI Gaming PC on 9/26/2021.
//

// This is the class for the stack for the sets of points

#ifndef PROJECT_4___MAZE_NAVIGATION_BESTANAVNET_H
#define PROJECT_4___MAZE_NAVIGATION_BESTANAVNET_H

#include "godtnavn.h"


class Super_stack
{
    // Access Specifier
    Double_position_stack *super_stack = (Double_position_stack*)create_stack_d();
public:
    // Empty constructor
    Super_stack() {
    }

    int is_empty(){
        return is_empty_stack_d(super_stack);
    }

    int push(int x1, int y1, int x2, int y2) {
        Position start;
        Position end;
        start.x = x1;
        start.y = y1;
        end.x = x2;
        end.y = y2;
        return push_d(super_stack, start, end);
    }

    Double_position_stack pop(){
        return pop_d(super_stack);
    }


};



#endif //PROJECT_4___MAZE_NAVIGATION_BESTANAVNET_H
