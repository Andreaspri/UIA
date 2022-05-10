//
// Created by Andreas on 28.04.2022.
//

#ifndef ASSIGNMENT_4_1_ORDERS_H
#define ASSIGNMENT_4_1_ORDERS_H


#include <string>

class Orders {

public:
    std::string id;
    std::string  customerId;
    std::string  productId;
    std::string  amount;

    Orders(std::string  id, std::string  customerId, std::string  productId, std::string  amount);

};


#endif //ASSIGNMENT_4_1_ORDERS_H
