//
// Created by Andreas on 19.09.2021.
//

#ifndef PROJECT_3_GRAPHICS_HANDLING_H
#define PROJECT_3_GRAPHICS_HANDLING_H
#include <Polygon.h>
#include <linked_list.h>

#define FUZZY_CLICK 50
#define INF 100000


Polygon* point_clicked(polygon_list *stack_list, int x, int y, int old_point[2]);
Polygon point_clicked_helper(polygon_list *stack_list, int x, int y, int old_point[2]);
int orientation(sf::Vector2<int> p,sf::Vector2<int> q,sf::Vector2<int> r);
bool doIntersect(sf::Vector2<int> p1,sf::Vector2<int> q1,sf::Vector2<int> p2,sf::Vector2<int> q2);
bool isInside(Polygon* poly,sf::Vector2<int>  point);
bool check_if_inside(polygon_list* stack_list, polygon_list* selected_polygons, sf::Vector2<int> mouse);
void draw_all_polygons(polygon_list* stack_list, sf::RenderWindow* window);
void draw_all_selected_polygons(polygon_list* stack_list, sf::RenderWindow* window);
sf::Vector2<int>* get_mouse_position(sf::RenderWindow* window);





#endif //PROJECT_3_GRAPHICS_HANDLING_H
