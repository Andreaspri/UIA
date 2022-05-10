//
// Created by Andreas on 18.09.2021.
//

#ifndef PROJECT_3_LINKED_LIST_H
#define PROJECT_3_LINKED_LIST_H

#include <Polygon.h>


typedef struct Polygons polygon_list;

struct Polygons create_list();

bool list_is_empty(polygon_list* head);

int add_empty_list_node(polygon_list* head);

struct Polygon* current_polygon(struct Polygons* head);

int add_stack_to_list(struct Polygons* head, Polygon* stack);

polygon_list* end_of_list(polygon_list* list);

void push_stack_to_list_element(polygon_list* head);

void add_mouse_coordinates_to_stack(polygon_list* stack_list, sf::RenderWindow* window);

typedef struct Polygons
{
    void* stack;
    struct Polygons* next_element;
}polygon_list;

#endif //PROJECT_3_LINKED_LIST_H
