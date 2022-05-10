//
// Created by Andreas on 29.09.2021.
//

#ifndef PROJECT_5_AIR_TRAFFIC_CONTROLLER_AIRCRAFT_H
#define PROJECT_5_AIR_TRAFFIC_CONTROLLER_AIRCRAFT_H

#define RADIUS 100 // Miles
#define MIN_SPEED 100 // knots
#define MAX_SPEED 1000 // knots
//#define ALARM_DISTANCE 500 //feet
#define ALARM_DISTANCE_ORIGINAL 500*0.0001893939 //500 feet in miles
#define ALARM_DISTANCE 1000*0.0001893939 //5000 feet in miles - Because 500 feet converts to 0.094 distance, which is extremely close... This is 0.94 instead
#define MAX_ANGLE_CHANGE 0.1 // Maximum angle a plane can change in both positive and negative direction. This is radians change for every iteration
#define MAX_SPEED_CHANGE 30 // Maximum speed change in botch positive and negative direction for each iteration
#define AIRCRAFT_MOVEMENT_REDUCER (double)1/(60*60*6) // Reducing the movement from miles per hour to miles per N seconds to prevent the aircraft from going too fast

typedef struct position_struct {
    double x;
    double y;
} Position;


typedef struct flight_struct {
    Position position;
    double speed;
    double angle;;
} Aircraft_struct;
class Aircraft;

Aircraft_struct *create_aircraft();
double priority(Aircraft_struct* aircraft);
void move_aircraft(Aircraft_struct* aircraft);
void change_properties(Aircraft_struct* aircraft);
Position get_position_of_aircraft(Aircraft_struct* aircraft);
int rand_int(int min, int max);
Aircraft* newAircraft();
Position get_pos(Aircraft_struct* aircraft);

class Aircraft {

    Aircraft_struct *aircraft;

public:
    //Aircraft()= default;
    Aircraft();

    double calculate_priority();

    void move();

    void apply_random_changes();

    Position get_position();

    void free_aircraft();

    void change_angle(double angle);

    double get_angle();

    double get_speed();

    void change_speed(double speed);


};


#endif //PROJECT_5_AIR_TRAFFIC_CONTROLLER_AIRCRAFT_H
