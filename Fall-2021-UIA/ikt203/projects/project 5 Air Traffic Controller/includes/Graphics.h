//
// Created by Andreas on 29.09.2021.
//

#ifndef PROJECT_5_AIR_TRAFFIC_CONTROLLER_GRAPHICS_H
#define PROJECT_5_AIR_TRAFFIC_CONTROLLER_GRAPHICS_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <cmath>
#include <iostream>
#include "queue.h"
#include <list>
#include <vector>
#include "gift_wrap_algorithm.h"

#define CIRCLE_DEGREE 360
#define DELTA 20
#define GREEN sf::Color(150,249,123)
#define LINE_COLOR sf::Color::Black
#define CIRCLE_LINE_THICC 4
#define DELTA_ANGLE 0.1*M_PI
#define CONVEX_COLOR sf::Color::Red
#define SHADOW 0.3
#define DELTA_DEGREES 0.5
#define RADAR_THICC 4
#define RADAR_COLOR sf::Color::Red
#define CIRCLE_LINES_NOT_THICC 1
#define CIRCLE_SPACER 40
#define GRID_DELTA 50
#define SPACING 40
#define WIDTH 1400
#define PLANE_RADIUS 2
#define PLANE_DANGER_MAGNIFIER 2
#define PLANE_CLOSEST_MAGNIFIER 1.5
#define PLANE_COLOR sf::Color(0,154,0)
#define PLANE_DANGER_COLOR sf::Color::Red
#define PLANE_CLOSEST_PAIR_COLOR sf::Color::Black
#define FADING_COUNT 50
//#define DANGER_DISTANCE 1
#define TRANSPARENT 255
#define HEIGHT 900
#define ORIGIN_X WIDTH/2
#define ORIGIN_Y HEIGHT/2

// provide your namespace to avoid collision/ambiguities
namespace game {

    class Game_background : public sf::Drawable {
    private:
        Queue *planes;
        sf::CircleShape shape;
        Data *positions;
        Data *smallest_distance;
        float degrees;
        std::list<std::list<Position>> to_close_index;
        //std::vector<sf::RectangleShape> *rectangles;
    public:
        Game_background(sf::Color color_circle, Queue *aircrafts);

        virtual ~ Game_background();

        virtual void draw(sf::RenderTarget &, sf::RenderStates) const;

        void update_radar();

        void update_aircrafts(Node *, int, int);

        void update_convex_hull(Data);

    };
}





#endif //PROJECT_5_AIR_TRAFFIC_CONTROLLER_GRAPHICS_H
