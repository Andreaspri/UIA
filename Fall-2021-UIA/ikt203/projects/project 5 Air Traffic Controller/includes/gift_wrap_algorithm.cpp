//
// Created by Andreas on 06.10.2021.
//

#include "gift_wrap_algorithm.h"

int orientation(Position *current_position, Position test_position, Position last_valid_test_position){
    double cross_product = (last_valid_test_position.y - current_position->y) * (test_position.x - current_position->x) - (last_valid_test_position.x - current_position->x) * (test_position.y - current_position->y);
    if (cross_product == 0) return 0; // co-linear
    return (cross_product > 0)? 1: 2; // 1: To the right. 2: To the left.
}

Data convex_hull(Node *points, int size, int front, int tail){

    //There must be at least 3 points.
    if (size < 3){
        Data error;
        error.size = 0;
        error.positions = nullptr;
        return error;
    }

    int current_index = front;
    int current_size = 1;

    auto *polygon = (Position *)malloc(current_size*sizeof(Position));

    // Finding the leftmost point.
    polygon[0] = ((Aircraft *)points[front].data)->get_position();
    for (int i = points[front].next; i != tail; i = points[i].next){
        if (((Aircraft *)points[i].data)->get_position().x < polygon[0].x){
            polygon[0] = ((Aircraft *)points[i].data)->get_position();
            current_index = i;
        }
    }
    // have to check the last index.
    if (((Aircraft *)points[tail].data)->get_position().x < polygon[0].x){
        polygon[0] = ((Aircraft *)points[tail].data)->get_position();
        current_index = tail;
    }

    Position *current_position = polygon;
    Position last_valid_test_position;
    bool changed;
    do{
        changed = false;
        // Here we can choose a random point in the list excepts the current point. I decided to  choose the next or the previous because this is a linked list.
        /*
        try
        {
            int new_index = points[current_index].next;
            last_valid_test_position = ((Aircraft *)points[new_index].data)->get_position();
        }
        catch (...)
        {
            last_valid_test_position = ((Aircraft *)points[previous_index].data)->get_position();
        }
        */
        // Find a random point in the list which is NOT the current point.
        int potential_next_index;
        for (int i = front; i != tail; i = points[i].next){
            if (i != current_index){
                last_valid_test_position = ((Aircraft *)points[i].data)->get_position();
                potential_next_index = i;
                break;
            }
        }
        // Left vector for each in list other than tail
        for (int i = front; i != tail; i = points[i].next){
            if (orientation(current_position,  ((Aircraft *)points[i].data)->get_position(), last_valid_test_position) == 2){
                last_valid_test_position = ((Aircraft *)points[i].data)->get_position();
                current_index = i;
                changed = true;
            }

        }
        // Left vector for tail
        if (orientation(current_position,  ((Aircraft *)points[tail].data)->get_position(), last_valid_test_position) == 2){
            last_valid_test_position = ((Aircraft *)points[tail].data)->get_position();
            current_index = tail;
            changed = true;
        }
        current_size++;
        polygon = (Position *)realloc(polygon, current_size*sizeof(Position));
        polygon[current_size-1] = last_valid_test_position;
        current_position = polygon+(current_size-1);
        if (!changed){
            current_index = potential_next_index;
        }


    }while((current_position->x != polygon->x) && (current_position->y != polygon->y));

    Data great_success;
    great_success.positions = polygon;
    great_success.size = current_size;

    return great_success;

}

