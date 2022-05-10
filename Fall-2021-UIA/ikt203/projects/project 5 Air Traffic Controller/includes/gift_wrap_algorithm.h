//
// Created by Andreas on 06.10.2021.
//

#ifndef PROJECT_5_AIR_TRAFFIC_CONTROLLER_GIFT_WRAP_ALGORITHM_H
#define PROJECT_5_AIR_TRAFFIC_CONTROLLER_GIFT_WRAP_ALGORITHM_H
#include <iostream>
#include <cmath>
#include "queue.h"

typedef struct return_data{
    Position *positions;
    int size;
}Data;

int orientation(Position *, Position, Position);

Data convex_hull(Node *, int, int, int);

#endif //PROJECT_5_AIR_TRAFFIC_CONTROLLER_GIFT_WRAP_ALGORITHM_H
