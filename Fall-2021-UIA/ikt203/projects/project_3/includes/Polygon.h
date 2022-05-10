#include <library.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#ifndef PROJECT_3_POLYGON_H
#define PROJECT_3_POLYGON_H



class Polygon
{
    // Access specifier
    public:
        // Empty constructor
        Polygon () {}

        Stack* coordinate_stack = (Stack*)create_stack();

        int add_coordinate(void* x,void* y) {
            return push(coordinate_stack, x, y);
        }

        Stack *get_polygon(){
            return coordinate_stack;
        }

        Stack *next(){
            return (Stack*)coordinate_stack->next;
        }

        int *delete_last_point(int temp_coordinates[2]){
            pop(coordinate_stack, temp_coordinates);
            if (empty_stack(coordinate_stack)){
                return NULL;
            }
            else
                return inspect_top_of_stack(coordinate_stack, temp_coordinates);
        }

        int *first_point(int temp_coordinates[2]){
            return inspect_bottom_of_stack(coordinate_stack, temp_coordinates);
        }

        int *last_point(int temp_coordinates[2]) {
            return inspect_top_of_stack(coordinate_stack, temp_coordinates);
        }

        int is_empty() {
            return empty_stack(coordinate_stack);
        }

};


#endif //PROJECT_3_POLYGON_H


