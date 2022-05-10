//
// Created by Andreas on 28.09.2021.
//

#ifndef PROJECT_5_AIR_TRAFFIC_CONTROLLER_LINKED_LIST_H
#define PROJECT_5_AIR_TRAFFIC_CONTROLLER_LINKED_LIST_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <list>




typedef struct node_2{
    sf::RectangleShape radar;
    struct node_2 *next{};
}Rectangle_list;

typedef struct dummy{
    Rectangle_list *rectangle_list;
    int size;
}Dummy_node;

Dummy_node *create_rectangle_list();

void append(Dummy_node *linked_list, sf::RectangleShape);

void remove_last(Dummy_node *linked_list);

class Rectangles {
    private:
        Dummy_node *rectangle;
    public:
        Rectangles();

        Rectangle_list *get_rectangle_list();

        int size();

        void add_rectangle(sf::RectangleShape radar);

        void remove_last_rectangle();
};


#endif //PROJECT_5_AIR_TRAFFIC_CONTROLLER_LINKED_LIST_H
