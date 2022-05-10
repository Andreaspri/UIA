//
// Created by Andreas on 18.09.2021.
//

#include "linked_list.h"
#include "Polygon.h"
#include <climits>
#include <graphics_handling.h>

polygon_list create_list()
{
    auto* head = (polygon_list*)malloc(sizeof(polygon_list));
    head->next_element = nullptr;
    head->stack = nullptr;
    return *head;
};

void push_stack_to_list_element(polygon_list* head)
{
    auto* stack = (Polygon*)malloc(sizeof(Polygon));
    stack->coordinate_stack = (Stack*)create_stack();
    head->stack = stack;
}


void add_mouse_coordinates_to_stack(polygon_list* stack_list, sf::RenderWindow* window)
{
sf::Vector2<int>* coordinates = get_mouse_position(window);
current_polygon(end_of_list(stack_list))->add_coordinate(&coordinates->x, &coordinates->y);
}

// True if list is empty
bool list_is_empty(polygon_list* head)
{
    return head->next_element == nullptr;
}


/*Return true if position is the last position in the list*/
int is_last(polygon_list* position )
{
    return position->next_element == nullptr;
}

int list_size(polygon_list* list){
    polygon_list* temporary_list = list;
    int counter = 0;
    while (temporary_list->next_element){
        counter++;
    }
    return counter;
}

polygon_list* end_of_list(polygon_list* list){
    if (is_last(list))
        return list;
    polygon_list* temporary_list = list;
    while (!is_last(temporary_list)){
        temporary_list = temporary_list->next_element;
    }
    return temporary_list;
}

// Gets position of given element
int getposition(polygon_list* list, Polygon* element) {
    polygon_list* position;
    int i = 0;
    for (position = list; position!= nullptr; position=(polygon_list*)position->next_element)
    {
        if (position->stack == element)
            return i+1;
        else i++;
    }
    return INT_MIN;
}

// Gets element in given position
Polygon* get_element(polygon_list* list, int pos) {
    polygon_list* temporary_list;
    int number;
    temporary_list = list;
    if (pos > list_size(list))
        return nullptr;
    else {
        for(int i=0; i<pos; i++)
            temporary_list = (polygon_list*)temporary_list->next_element;
        return (Polygon*)temporary_list->stack;
    }
}


// Gets the stack of the top polygon
Polygon* current_polygon(polygon_list* list)
{
    return (Polygon*)((polygon_list*)list)->stack;
}

int add_stack_to_list(polygon_list* head, Polygon* stack)
{
    polygon_list* new_node = (polygon_list*)malloc(sizeof(polygon_list));
    if (new_node == nullptr){
        printf("Error - Unable to allocate memory new node.\n");
        return INT_MIN;
    }
    polygon_list* last_node = end_of_list(head);

    new_node->stack = stack;
    new_node->next_element = nullptr;

    last_node->next_element = new_node;
    return 1;
}


//// Adds a new node to the list
int add_empty_list_node(polygon_list* head)
{
    auto* stack = (Polygon*)malloc(sizeof(Polygon));
    stack->coordinate_stack = (Stack*)create_stack();
    auto* new_node = (Polygons*) malloc(sizeof(Polygons));
    if (new_node == nullptr){
        printf("Error - Unable to allocate memory new list node.\n");
        return INT_MIN;
    }
    new_node->stack = stack;
    polygon_list *end = end_of_list(head);
    end->next_element = new_node;
    new_node->next_element = nullptr;
    return 1;
}