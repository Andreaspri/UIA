//
// Created by Andreas on 29.09.2021.
//


#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <random>
#include <map>
#include <functional>
#include <chrono>

#include "aircraft.h"





Aircraft::Aircraft() {
    aircraft = create_aircraft();
}

double Aircraft::calculate_priority()
{
    return priority(aircraft);
}

void Aircraft::move()
{
    move_aircraft(aircraft);
}

void Aircraft::apply_random_changes()
{
    change_properties(aircraft);
}

Position Aircraft::get_position()
{
    return get_position_of_aircraft(aircraft);
}



void Aircraft::free_aircraft()
{
    free(aircraft);
}


void Aircraft::change_angle(double angle)
{
    aircraft->angle=angle;
}

double Aircraft::get_angle()
{
    return aircraft->angle;
}

double Aircraft::get_speed()
{
    return aircraft->speed;
}

void Aircraft::change_speed(double speed)
{
    aircraft->speed=speed;
}

double rand_double(double min, double max)
{
    // Get pseudo seed based on time since epoch
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto seed = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();


    // Feed seed to generator
    std::mt19937 double_generator(seed+rand());

    // Set the distribution range of numbers
    std::uniform_real_distribution<> double_range(min, max);

    // Bind the range to the generator and return the first number in the binding
    return std::bind(double_range, double_generator)();
}

int rand_int(int min, int max)
{
    // Get pseudo seed based on time since epoch
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto seed = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    // Feed seed to generator
    std::mt19937 int_generator(seed+rand());

    // Set the distribution range of numbers
    std::uniform_int_distribution<> int_range(min, max);

    // Bind the range to the generator and return the first number in the binding
    return std::bind(int_range, int_generator)();
}


Aircraft_struct *create_aircraft()
{

    auto * aircraft = (Aircraft_struct*)malloc(sizeof(Aircraft_struct));
    if (rand_int(0,1) == 1){
        aircraft->position.x = rand_double(-RADIUS,RADIUS);
        aircraft->position.y = sqrt(pow(RADIUS,2.0)-pow(aircraft->position.x,2.0));
        if (rand_int(0,1) == 1){
            aircraft->position.y = -aircraft->position.y;
        }
    }
    else
    {
        aircraft->position.y = rand_double(-RADIUS,RADIUS);
        aircraft->position.x = sqrt(pow(RADIUS,2.0)-pow(aircraft->position.y,2.0));
        if (rand_int(0,1) == 1){
            aircraft->position.x = -aircraft->position.x;
        }
    }
    aircraft->speed = rand_double(MIN_SPEED,MAX_SPEED);
    aircraft->angle = rand_double(0,2*M_PI);

    return aircraft;
}

double get_angle_c(double x, double y, double b, double angle){
    if (x >= 0 && y > 0)
    {
        // Angle for first quadrant
        return 2*M_PI-(asin(x/b)+M_PI/2+angle);
    }
    else if (x < 0 && y >= 0)
    {
        // Angle for second quadrant
        return 2*M_PI-(-std::abs(asin(x/b))+M_PI/2+angle);
    }
    else if (x < 0 && y <= 0)
    {
        // Angle for third quadrant
        return -(asin(x/b)+M_PI/2)+angle;
    }
    else if (x >= 0 && y < 0)
    {
        // Angle for fourth quadrant
        return 2*M_PI-angle+asin(x/b)+M_PI/2;
    }
    else{
        printf("Unexpected error in the priority!\n");
        return 0;
    }
}


double get_distance_a(double b, double angle_c, double c){
    double abc1,abc2,sqrt1,sqrt2;

    sqrt1 = pow(2*b*cos(angle_c),2.0)-4*(b*b-c*c);
    sqrt2 = pow(2*b*cos(angle_c),2.0)-4*(b*b-c*c);
    // Checking for imaginary numbers
    if (sqrt1 >= 0)
        abc1 = (2*b*cos(angle_c) + sqrt(sqrt1))/2; // Applying the Quadratic Equation for positive
    else
        abc1 = -1;

    if (sqrt2 >= 0)
        abc2 = (2*b*cos(angle_c) - sqrt(sqrt2))/2; // Applying the Quadratic Equation for negative
    else
        abc2 = -1;

    if (abc1 >= abc2)
    {
        return abc1;
    }
    else if (abc2 >= abc1)
    {
        return abc2;
    }
    else
        printf("Error computing distance!\n");
}




// Gets the priority of the aircraft based on the time it takes to leave your airspace
double priority(Aircraft_struct* aircraft)
{
    double b,c,angle_c,distance,priority;
    // Distance to aircraft from origin
    b = sqrt(pow(aircraft->position.x,2.0)+pow(aircraft->position.y,2.0));
    // Calculate angle C (from position of plane)
    angle_c = get_angle_c(aircraft->position.x, aircraft->position.y, b, aircraft->angle);

    // Distance from origin to edge of our airspace (where the aircraft will leave)
    c = RADIUS;

    // Distance from aircraft to the edge of our airspace
    distance = get_distance_a(b, angle_c, c);
    priority = distance/(aircraft->speed*1.15077954)*60; // 1.15077954 is 1 knot to miles and then converting it from h to m (60)
    return priority;
}




void change_properties(Aircraft_struct* aircraft)
{
    // Only 2% chance of flight changing anything
    switch (rand_int(1, 100)) {
        case 1:
            // 1% chance of angle change
            aircraft->angle += rand_double(-MAX_ANGLE_CHANGE,MAX_ANGLE_CHANGE);
            if (aircraft->angle > 2*M_PI)
                aircraft->angle = 0;
            else if (aircraft->angle < 0)
                aircraft->angle = -aircraft->angle;
            // TODO: Replace the airplane in the queue.
            break;

        case 2:
            // 1% chance of speed change
            aircraft->speed += rand_double(-MAX_SPEED_CHANGE,MAX_SPEED_CHANGE);
            if (aircraft->speed > MAX_SPEED)
                aircraft->speed -= MAX_SPEED_CHANGE;
            else if (aircraft->speed < MIN_SPEED)
                aircraft->speed += MAX_SPEED_CHANGE;
            // TODO: Replace the airplane in the queue.
            break;
        default:
            break;
    }
}


void move_aircraft(Aircraft_struct* aircraft)
{
    aircraft->position.x += AIRCRAFT_MOVEMENT_REDUCER*aircraft->speed*cos(aircraft->angle);
    aircraft->position.y += AIRCRAFT_MOVEMENT_REDUCER*aircraft->speed*sin(aircraft->angle);
}


Position get_position_of_aircraft(Aircraft_struct* aircraft)
{
    return aircraft->position;
}




Aircraft* newAircraft()
{
    return new Aircraft;
}















