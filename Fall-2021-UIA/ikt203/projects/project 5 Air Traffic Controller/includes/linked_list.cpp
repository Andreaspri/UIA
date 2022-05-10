//
// Created by Andreas on 28.09.2021.
//

#include "linked_list.h"

Dummy_node *create_rectangle_list(){
    auto *rectangles = (Dummy_node *)malloc(sizeof(Dummy_node));
    rectangles->size = 0;
    return rectangles;
}

void append(Dummy_node *linked_list, sf::RectangleShape radar){
    if (linked_list->size == 0){
        auto *new_rectangle = (Rectangle_list *)malloc(sizeof(Rectangle_list));
        new_rectangle->next = nullptr;
        new_rectangle->radar = radar; // Cheat mode: On.
        linked_list->rectangle_list = new_rectangle;
        linked_list->size++;
    }
    else{
        auto *new_rectangle = (Rectangle_list *)malloc(sizeof(Rectangle_list));
        new_rectangle->radar = radar;
        new_rectangle->next = linked_list->rectangle_list;
        linked_list->rectangle_list = new_rectangle;
        linked_list->size++;
    }
}

void remove_last(Dummy_node *linked_list){
    if (linked_list->size == 0){
        printf("Linked list is empty!\n");
    }
    else{
        Rectangle_list  *second_last_node;
        Rectangle_list *last_node = linked_list->rectangle_list;
        while(last_node->next != nullptr){
            second_last_node = last_node;
            last_node = last_node->next;
        }
        free(last_node);
        linked_list->size --;
        if (linked_list->size == 0){
            linked_list->rectangle_list = nullptr;
        }
        else{
            second_last_node->next = nullptr;
        }
    }


}

Rectangles::Rectangles() :
    rectangle(){
    rectangle = create_rectangle_list();
}

Rectangle_list *Rectangles::get_rectangle_list() {
    return rectangle->rectangle_list;
}

int Rectangles::size() {
    return rectangle->size;
}

void Rectangles::remove_last_rectangle() {
    remove_last(rectangle);
}

void Rectangles::add_rectangle(sf::RectangleShape radar) {
    append(rectangle, radar);
}