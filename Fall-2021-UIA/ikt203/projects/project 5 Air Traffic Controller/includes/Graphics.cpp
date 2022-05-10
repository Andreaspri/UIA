//
// Created by Andreas on 29.09.2021.
//

#include "Graphics.h"
#include <algorithm>
/*
sf::Vector2f new_position(sf::Vector2f vector){
    float a[2][2];
    sf::Vector2f sum;

    // Rotational matrix
    a[0][0] = cos(DELTA_ANGLE);
    a[0][1] = -sin(DELTA_ANGLE);
    a[1][0] = sin(DELTA_ANGLE);
    a[1][1] = cos(DELTA_ANGLE);

    sum.x = a[0][0]*(vector.x-WIDTH/2) + a[0][1]*(vector.y-HEIGHT/2) + WIDTH/2;
    sum.y = a[1][0]*(vector.x-WIDTH/2) + a[1][1]*(vector.y-HEIGHT/2) + HEIGHT/2;

    return sum;
}
*/

namespace game {
    Game_background::Game_background(sf::Color color_circle, Queue *aircrafts) :
            shape((float) (std::min(WIDTH, HEIGHT) - SPACING) / 2) {
        shape.setFillColor(color_circle);
        shape.setOrigin((sf::Vector2f(shape.getRadius(), shape.getRadius())));
        shape.setPosition((float) WIDTH / 2, (float) HEIGHT / 2);
        shape.setOutlineColor(LINE_COLOR);
        shape.setOutlineThickness(CIRCLE_LINE_THICC);
        //sf::Vector2f starting_position(shape.getRadius() + (float)WIDTH/2, (float)HEIGHT/2);
        //rectangles = (std::vector<sf::RectangleShape> *)malloc(sizeof(std::vector<sf::RectangleShape>))
        positions = (Data *) malloc(sizeof(Data));
        smallest_distance = (Data *) malloc(sizeof(Data));
        smallest_distance->positions = (Position *)malloc(2*sizeof(Position));
        positions->size = 0;
        planes = aircrafts;
        degrees = 0;

    }

    Game_background::~Game_background() {
    }


    void Game_background::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        sf::VertexArray line(sf::LineStrip, 2);
        // Generate background line grid
        for (int x = 0; x <= WIDTH; x += GRID_DELTA) {
            line[0] = sf::Vector2f((float) x, 0);
            line[0].color = GREEN;
            line[1] = sf::Vector2f((float) x, HEIGHT);
            line[1].color = GREEN;
            target.draw(line, states);
        }
        for (int y = 0; y <= HEIGHT; y += GRID_DELTA) {
            line[0] = sf::Vector2f(0, (float) y);
            line[0].color = GREEN;
            line[1] = sf::Vector2f(WIDTH, float(y));
            line[1].color = GREEN;
            target.draw(line, states);
        }
        target.draw(shape, states);


        // Generate radar circles
        for (int i = 0; i < (int) shape.getRadius(); i += CIRCLE_SPACER) {
            sf::CircleShape circle_lines(shape.getRadius() - (float) i);
            circle_lines.setOrigin(circle_lines.getRadius(), circle_lines.getRadius());
            circle_lines.setPosition((float) WIDTH / 2, (float) HEIGHT / 2);
            circle_lines.setOutlineColor(LINE_COLOR);
            circle_lines.setOutlineThickness(CIRCLE_LINES_NOT_THICC);
            target.draw(circle_lines, states);
        }
        // Generate radar circle "line spacers"
        for (int i = 0; i <= CIRCLE_DEGREE; i += DELTA) {
            line[0] = sf::Vector2f((float) WIDTH / 2, (float) HEIGHT / 2);
            line[0].color = sf::Color::Black;
            line[1] = sf::Vector2f(ORIGIN_X + shape.getRadius() * cos(i * M_PI / ((float) CIRCLE_DEGREE / 2)),
                                   ORIGIN_Y + shape.getRadius() * sin(i * M_PI / ((float) CIRCLE_DEGREE / 2)));
            line[1].color = sf::Color::Black;
            target.draw(line, states);
        }
        // Generate radar directional scanner line
        sf::RectangleShape radar_line(sf::Vector2f(shape.getRadius(), RADAR_THICC));
        radar_line.setFillColor(RADAR_COLOR);
        radar_line.setPosition(shape.getPosition());
        /*
        float length_x = (position.x - (float)WIDTH/2);
        float length_y = ((HEIGHT/2)-position.y);
        printf("%f  %f\n", length_x, length_y);
        float angle = atan(length_x/length_y);
        if ((length_y < 0) && (length_x < 0)){
            angle += 2*M_PI;
        }
        else if (length_x < 0){
            angle += 2*M_PI;
        }
        */
        //Display radar line.
        float initial_degrees = degrees;
        float fade = TRANSPARENT;
        float delta = TRANSPARENT / FADING_COUNT;
        for (int i = 0; i < FADING_COUNT; i++) {
            radar_line.setFillColor(sf::Color(141, 27, 31, (int) fade));
            radar_line.setRotation(initial_degrees + (float) i * DELTA_ANGLE);
            target.draw(radar_line, states);
            fade -= delta;
        }
        /*
        if (rectangles->size() == FADING_COUNT){
            rectangles->erase(rectangles->begin());
        }
        rectangles->push_back(radar_line); //
        int fading = TRANSPARENT/FADING_COUNT;
        int current_fade = TRANSPARENT;
        for (int i = (int)rectangles->size()-1; i >= 0; i--){
            (rectangles->begin()+i)->setFillColor(sf::Color(141, 27, 31, current_fade));
            target.draw(*(rectangles->begin()+i), states);
            current_fade -= fading;
        }
        */
        sf::CircleShape circle;
        circle.setRadius(PLANE_RADIUS);
        circle.setFillColor(PLANE_COLOR);

        for (int i = 0; i < planes->size(); i++) {
            Position position = planes->get_aircraft_position_by_index(i);
            /*
            for_each(data.begin(), data.end(), [](Position *it)
            {
                std::cout<<it->name;
            });
            */
            if (smallest_distance->size != 0){
                if (smallest_distance->positions->x == position.x && smallest_distance->positions->y == position.y){
                    circle.setFillColor(PLANE_CLOSEST_PAIR_COLOR);
                    circle.setRadius(PLANE_RADIUS*PLANE_CLOSEST_MAGNIFIER);
                }
                else if (smallest_distance->positions[1].x == position.x && smallest_distance->positions[1].y == position.y){
                    circle.setFillColor(PLANE_CLOSEST_PAIR_COLOR);
                    circle.setRadius(PLANE_RADIUS*PLANE_CLOSEST_MAGNIFIER);
                }
            }
            else{
                for (const auto &it: to_close_index) {
                    float r = shape.getRadius();
                    sf::VertexArray line_2(sf::LineStrip, 2);
                    int index = 0;
                    bool draw = false;
                    for (const auto &it_2: it) {
                        if ((position.x == it_2.x) && (position.y == it_2.y)) {
                            line_2[index] = sf::Vector2f((float) ORIGIN_X + (float) it_2.x * r / RADIUS,
                                                         (float) ORIGIN_Y - (float) it_2.y * r / RADIUS);
                            line_2[index].color = PLANE_DANGER_COLOR;
                            circle.setFillColor(PLANE_DANGER_COLOR);
                            circle.setRadius(PLANE_RADIUS*PLANE_DANGER_MAGNIFIER);
                            draw = true;
                        } else {
                            line_2[index] = sf::Vector2f((float) ORIGIN_X + (float) it_2.x * r / RADIUS,
                                                         (float) ORIGIN_Y - (float) it_2.y * r / RADIUS);
                            line_2[index].color = PLANE_DANGER_COLOR;
                        }
                        index++;
                    }
                    if (draw)
                        target.draw(line_2, states);
                }
            }
            circle.setPosition((float) ORIGIN_X + (float) position.x * shape.getRadius() / RADIUS - PLANE_RADIUS,
                               (float) ORIGIN_Y - (float) position.y * shape.getRadius() / RADIUS - PLANE_RADIUS);
            target.draw(circle, states);
            circle.setRadius(PLANE_RADIUS);
            circle.setFillColor(PLANE_COLOR);
        }
        if (positions->size != 0) {
            sf::VertexArray convex_hull(sf::LineStrip, positions->size);
            for (int i = 0; i < positions->size; ++i) {
                Position *temp_pos = positions->positions + i;
                convex_hull[i] = sf::Vector2f((float) ORIGIN_X + (float) temp_pos->x * shape.getRadius() / RADIUS,
                                              (float) ORIGIN_Y - (float) temp_pos->y * shape.getRadius() / RADIUS);
                convex_hull[i].color = CONVEX_COLOR;
            }
            target.draw(convex_hull, states);
            if (smallest_distance->size != 0){
                sf::VertexArray line_3(sf::LineStrip, 2);
                for (int z = 0; z < 2; ++z){
                    line_3[z] = sf::Vector2f((float) ORIGIN_X + (float) smallest_distance->positions[z].x * shape.getRadius() / RADIUS,
                                             (float) ORIGIN_Y - (float) smallest_distance->positions[z].y * shape.getRadius() / RADIUS);
                    line_3[z].color = sf::Color(PLANE_CLOSEST_PAIR_COLOR);
                }
                target.draw(line_3, states);
            }
            positions->size = 0;
            free(positions->positions);
        }

    }

    void Game_background::update_radar() {
        degrees -= DELTA_DEGREES;
        if (degrees < 0.0) degrees += CIRCLE_DEGREE;
    }


    void Game_background::update_aircrafts(Node *aircrafts, int size, int front) {
        // Clearing the entire list.
        to_close_index.erase(to_close_index.begin(), to_close_index.end());
        // Finding the aircraft's that are to close.
        int index_0 = front;
        bool skip_smallest_distance = false;
        smallest_distance->size = 0;
        smallest_distance->positions->x = 10000000;
        smallest_distance->positions->y = 10000000;
        smallest_distance->positions[1].x = 0;
        smallest_distance->positions[1].y = 0;
        for (int i = 0; i < size; ++i, index_0 = aircrafts[index_0].next) {
            int index_1 = front;
            for (int j = 0; j < size; ++j, index_1 = aircrafts[index_1].next) {
                // Checking that the plane is not equal to other plane.
                if ((((Aircraft *) aircrafts[index_0].data)->get_position().x !=
                     ((Aircraft *) aircrafts[index_1].data)->get_position().x) &&
                    (((Aircraft *) aircrafts[index_0].data)->get_position().y !=
                     ((Aircraft *) aircrafts[index_1].data)->get_position().y)) {
                    // Checking if the distance is within the danger radius.
                    double delta_x = std::abs(((((Aircraft *) aircrafts[index_0].data)->get_position().x -
                                                ((Aircraft *) aircrafts[index_1].data)->get_position().x)));
                    double delta_y = std::abs((((Aircraft *) aircrafts[index_0].data)->get_position().y -
                                               ((Aircraft *) aircrafts[index_1].data)->get_position().y));
                    if ((delta_x <= ALARM_DISTANCE * shape.getRadius() / RADIUS) &&
                        (delta_y <= ALARM_DISTANCE * shape.getRadius() / RADIUS)) {


                        // Mix things up, to avoid getting static eject patterns that never dissolve.
                        double eject_modifier = 1.1;
                        // Makes things easier to translate in graphics from aircraft. Highway to the... :)
                        double danger_zone = (ALARM_DISTANCE * shape.getRadius() / RADIUS) * eject_modifier;

                        // Update the speed and direction of the two aircraft to avoid crashing.
                        // Get vector between AP_a and AP_b.
                        // Vector AB = (A.x,A.y),(B.x,B.y).
                        // Vector BA = (B.x,B.y),(A.x,A.y).
                        Position AP_a = ((Aircraft *) aircrafts[index_0].data)->get_position();
                        Position AP_b = ((Aircraft *) aircrafts[index_1].data)->get_position();
                        // Get speed and direction of AP_a and AP_b.
                        double AP_a_speed = ((Aircraft *) aircrafts[index_0].data)->get_speed();
                        double AP_b_speed = ((Aircraft *) aircrafts[index_1].data)->get_speed();
                        double AP_a_angle = ((Aircraft *) aircrafts[index_0].data)->get_angle();
                        double AP_b_angle = ((Aircraft *) aircrafts[index_1].data)->get_angle();
                        // Construct velocity vector points from speed and direction for AP_a and AP_b.
                        double AP_a_velocity_x = cos(AP_a_angle) * AP_a_speed;  // Predicted next step x, for AP_a
                        double AP_a_velocity_y = sin(AP_a_angle) * AP_a_speed;
                        double AP_b_velocity_x = cos(AP_b_angle) * AP_b_speed;
                        double AP_b_velocity_y = sin(AP_b_angle) * AP_b_speed;
                        // Get sign modifiers
                        double AP_ab_x_sign;    // Should be negative if ax < bx. Used later for the danger_zone modifier.
                        double AP_ab_y_sign;
                        double AP_ba_x_sign;
                        double AP_ba_y_sign;
                        if (AP_a_velocity_x < AP_b_velocity_x) AP_ab_x_sign = -1.0;
                        else AP_ab_x_sign = 1.0;
                        if (AP_a_velocity_y < AP_b_velocity_y) AP_ab_y_sign = -1.0;
                        else AP_ab_y_sign = 1.0;
                        AP_ba_x_sign = -AP_ab_x_sign; // Added just for clarity to make the code easier to read.
                        AP_ba_y_sign = -AP_ab_y_sign;
                        // Logic for decomposed x logic for aircraft a:
                        // Vector Cx = vector BxAx + Vector new Ax'Bx' (note the reversal of BxAx).
                        //  Note: Vector BxAx (distance between aircraft) is replaced with danger_zone modifier * sign modifier for higher repulsion effect.
                        // new AP_ax velocity vector = (old AP_ax velocity vector) + Vector Cx.
                        double AP_a_velocity_x_new = (AP_a_velocity_x - AP_a.x) + ((double)danger_zone*AP_ab_x_sign+(AP_a_velocity_x - AP_b_velocity_x));
                        double AP_a_velocity_y_new = (AP_a_velocity_y - AP_a.y) + ((double)danger_zone*AP_ab_y_sign+(AP_a_velocity_y - AP_b_velocity_y));
                        // new AP_b velocity vector = (old AP_b velocity vector) + vector AB (note the reversal).
                        double AP_b_velocity_x_new = (AP_b_velocity_x - AP_b.x) + ((double)danger_zone*AP_ba_x_sign+(AP_b_velocity_x - AP_a_velocity_x));
                        double AP_b_velocity_y_new = (AP_b_velocity_y - AP_b.y) + ((double)danger_zone*AP_ba_y_sign+(AP_b_velocity_y - AP_a_velocity_y));
                        // This should be hard abort angle, without "flips". Aka, emergency redirection.

                        // Convert this back to angle and speed and store in the airplanes.
                        double AP_a_delta_x = ((AP_a_velocity_x_new) - (AP_a.x));
                        double AP_a_delta_y = ((AP_a_velocity_y_new) - (AP_a.y));
                        double AP_b_delta_x = ((AP_b_velocity_x_new) - (AP_b.x));
                        double AP_b_delta_y = ((AP_b_velocity_y_new) - (AP_b.y));
                        // Speed = abs vector. Kept within the speed limits.
                        double AP_a_speed_new = std::max(
                                std::min(sqrt(pow(AP_a_delta_x, 2.0) + pow(AP_a_delta_y, 2.0)), (double) MAX_SPEED),
                                (double) MIN_SPEED);
                        double AP_b_speed_new = std::max(
                                std::min(sqrt(pow(AP_b_delta_x, 2.0) + pow(AP_b_delta_y, 2.0)), (double) MAX_SPEED),
                                (double) MIN_SPEED);

                        // Slight offset to x to remove probability of 0.
                        if (AP_a_delta_x == 0) AP_a_delta_x += 0.0001;
                        if (AP_b_delta_x == 0) AP_b_delta_x += 0.0001;
                        // Slight offset to y to remove probability of PI/2 direction
                        if (AP_a_delta_y == AP_a_delta_x) AP_a_delta_y += 0.0001;
                        if (AP_b_delta_y == AP_b_delta_x) AP_b_delta_y += 0.0001;
                        // Angle = arctan(y/x).
                        double AP_a_angle_new = atan(AP_a_delta_y / (AP_a_delta_x));
                        double AP_b_angle_new = atan(AP_b_delta_y / (AP_b_delta_x));

                        // Correct angle for negative x,y (-180deg if x and y sign is negative).
                        if (AP_ab_x_sign < 0 && AP_ab_y_sign < 0) AP_a_angle_new -= M_PI;
                        if (AP_ba_x_sign < 0 && AP_ba_y_sign < 0) AP_b_angle_new -= M_PI;

                        //printf("Old Angle: %f, new angle: %f, DeltaX: %f, DeltaY: %f,\n", AP_a_angle, AP_a_angle_new, AP_a_delta_x, AP_a_delta_y);
                        //printf("AP_b_velocity_y - AP_a_velocity_y: %f,\n", AP_b_velocity_y - AP_a_velocity_y);

                        // Push the new angle and speed back into the airplanes.
                        ((Aircraft *) aircrafts[index_0].data)->change_angle(AP_a_angle_new);
                        ((Aircraft *) aircrafts[index_1].data)->change_angle(AP_b_angle_new);
                        ((Aircraft *)aircrafts[index_0].data)->change_speed(AP_a_speed_new);
                        ((Aircraft *)aircrafts[index_1].data)->change_speed(AP_b_speed_new);
                        std::list<Position> temp;
                        temp.push_back(((Aircraft *) aircrafts[index_0].data)->get_position());
                        temp.push_back(((Aircraft *) aircrafts[index_1].data)->get_position());
                        to_close_index.push_back(temp);
                        temp.erase(temp.begin(), temp.end());
                        smallest_distance->size = 0;
                        skip_smallest_distance = true;
                    }
                    else if (!skip_smallest_distance && sqrt(std::pow(delta_x, 2) + std::pow(delta_y, 2)) < sqrt(pow(smallest_distance->positions->x - smallest_distance->positions[1].x, 2) +
                    pow(smallest_distance->positions->y - smallest_distance->positions[1].y, 2))){
                        smallest_distance->positions->x = ((Aircraft *) aircrafts[index_0].data)->get_position().x;
                        smallest_distance->positions->y = ((Aircraft *) aircrafts[index_0].data)->get_position().y;
                        smallest_distance->positions[1].x = ((Aircraft *) aircrafts[index_1].data)->get_position().x;
                        smallest_distance->positions[1].y = ((Aircraft *) aircrafts[index_1].data)->get_position().y;
                        smallest_distance->size = 2;
                    }
                }
            }
        }
    }

    void Game_background::update_convex_hull(Data new_positions) {
        positions->positions = new_positions.positions;
        positions->size = new_positions.size;
    }
}






/*

float length_x = (position.x - (float)WIDTH/2);
float length_y = ((HEIGHT/2)-position.y);
printf("%f  %f\n", length_x, length_y);
float angle = atan(length_x/length_y);
if ((length_y < 0) && (length_x < 0)){
    angle += 2*M_PI;
}
else if (length_x < 0){
    angle += 2*M_PI;
}

*/

/*
    radar_line.rotate(degrees);
      if (rectangles->size() == FADING_COUNT){
          //rectangles->erase(rectangles->begin());
      }
      rectangles->push_back(radar_line); //
      int fading = TRANSPARENT/FADING_COUNT;
      int current_fade = TRANSPARENT;
      for (int i = (int)rectangles->size()-1; i >= 0; i--){
          (rectangles->begin()+i)->setFillColor(sf::Color(141, 27, 31, current_fade));
          target.draw(*(rectangles->begin()+i), states);
          current_fade -= fading;
      }
*/
