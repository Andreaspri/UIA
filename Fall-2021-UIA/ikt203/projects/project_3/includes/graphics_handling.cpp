//
// Created by Andreas on 19.09.2021.
//

#include "graphics_handling.h"








// Returns the first polygon within FUZZY_CLICK pixels to the mouse pointer (if any)
Polygon* point_clicked(polygon_list *stack_list, int x, int y, int old_point[2]) {
    Stack *current_node;
    polygon_list *curr_polygon = stack_list;
    while(true)
    {
        current_node = (Stack*)current_polygon(curr_polygon)->coordinate_stack->next;
        while (current_node != nullptr) {
            if ((abs(*(int*)current_node->y-y) <= FUZZY_CLICK) && (abs(*(int*)current_node->x-x) <= FUZZY_CLICK)){
                old_point[0] = *(int*)current_node->x;
                old_point[1] = *(int*)current_node->y;

//                if current_node first element || last element:
//                    second_point[0]
//                    second_point[1]
                return current_polygon(curr_polygon);
            }
            current_node = current_node->next;
        }

        if (curr_polygon->next_element == nullptr)
            break;
        curr_polygon = curr_polygon->next_element;

    }
    return nullptr;
}
Polygon point_clicked_helper(polygon_list *stack_list, int x, int y, int old_point[2])
{
    Polygon* temp;
    temp = point_clicked(stack_list, x, y, old_point);
    return *temp;
}


/* VIKTIG */

// Funksjonen for å sjekke om punktet er inne i polygonet er ikke min. Vi burde kanskje gjøre noe med den?
// Link til koden under. Har bare gjort små endringer på koden til nå
// https://www.geeksforgeeks.org/how-to-check-if-a-given-point-lies-inside-a-polygon/


/* START OF BORROWED CODE */

#define INF 100000


// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(sf::Vector2<int> p,sf::Vector2<int> q,sf::Vector2<int> r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0; // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}


// The function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool doIntersect(sf::Vector2<int> p1,sf::Vector2<int> q1,sf::Vector2<int> p2,sf::Vector2<int> q2)
{
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;


    return false;
}

// Returns true if the point p lies inside the polygon[] with n vertices
bool isInside(Polygon* poly,sf::Vector2<int>  point)
{
    // There must be at least 3 vertices in polygon[]

    // Create a point for line segment from p to infinite
    sf::Vector2<int> extreme = {INF, point.y};
    sf::Vector2<int> polygon;
    sf::Vector2<int> polygon_next;
    // Count intersections of the above line with sides of polygon
    int count = 0;
    Stack* curr_poly = (Stack*)poly->coordinate_stack;
    if (curr_poly->next == nullptr)
        return 0;
    while (curr_poly->next->next != nullptr)
    {
        polygon = {*(int*)curr_poly->next->x,*(int*)curr_poly->next->y};
        polygon_next = {*(int*)curr_poly->next->next->x,*(int*)curr_poly->next->next->y};
        // Check if the line segment from 'p' to 'extreme' intersects
        // with the line segment from 'polygon[i]' to 'polygon[next_element]'
        if (doIntersect(polygon, polygon_next, point, extreme))
        {

            count++;
        }
        curr_poly = curr_poly->next;
    }

    // Return true if count is odd, false otherwise
    return count&1; // Same as (count%2 == 1)
}


/* END OF BORROWED CODE */



bool check_if_inside(polygon_list* stack_list, polygon_list* selected_polygons, sf::Vector2<int> mouse) {
    polygon_list* curr_polygon = stack_list;
    while(true)
    {
        if(isInside(current_polygon(curr_polygon), mouse))
            add_stack_to_list(selected_polygons, current_polygon(curr_polygon));

        if (curr_polygon->next_element == nullptr)
            break;

        curr_polygon = curr_polygon->next_element;
    }
    return true;
}


void draw_all_polygons(polygon_list* stack_list, sf::RenderWindow* window){
    int index;
    int count;
    Stack *current_point;


    polygon_list* curr_polygon = stack_list;
    while(true)
    {

        current_point = (Stack*)current_polygon(curr_polygon)->coordinate_stack;
        count = stack_size(current_point);

        sf::VertexArray lines(sf::LineStrip, count);
        std::vector<sf::Vertex> vertices;
        index = 0;

        float x;
        float y;

        while (current_point->next != nullptr){
            x = *(int*)current_point->next->x;
            y = *(int*)current_point->next->y;
            //lines[index].position =  sf::Vector2f(*(float*)current_point->next->x, *(float*)current_point->next->y);
            lines[index].position =  sf::Vector2f(x, y);
            lines[index].color = sf::Color::Black;
            current_point = current_point->next;
            index++;

        }
        window->draw(lines);

        if (curr_polygon->next_element == nullptr)
            break;
        curr_polygon = curr_polygon->next_element;

    }

}


void draw_all_selected_polygons(polygon_list* stack_list, sf::RenderWindow* window){
    int index;
    Stack *current_point;

    polygon_list* curr_polygon = stack_list;
    while(true)
    {

        if ((Stack*)current_polygon(curr_polygon) == nullptr)
        {
            if (curr_polygon->next_element == nullptr)
                break;
            curr_polygon = curr_polygon->next_element;
            continue;
        }


        current_point = (Stack*)current_polygon(curr_polygon)->coordinate_stack;


        sf::ConvexShape shape = sf::ConvexShape(stack_size(current_point)) ;

        index = 0;
        float x;
        float y;



        while (current_point->next != nullptr){
            x = *(int*)current_point->next->x;
            y = *(int*)current_point->next->y;
            shape.setPoint(index,sf::Vector2f(x, y));
            // Pretty colors
            shape.setFillColor(sf::Color(rand() % 255,rand() % 255,rand() % 255));
            //shape.setFillColor(sf::Color::Red);
            current_point = current_point->next;
            index++;

        }
        window->draw(shape);


        if (curr_polygon->next_element == nullptr)
            break;
        curr_polygon = curr_polygon->next_element;
    }

}


sf::Vector2<int>* get_mouse_position(sf::RenderWindow* window)
{
    auto* coordinates = (sf::Vector2<int>*)malloc(sizeof(sf::Vector2<int>));

    coordinates->y = sf::Mouse::getPosition(*window).y;
    coordinates->x = sf::Mouse::getPosition(*window).x;

    return coordinates;
}