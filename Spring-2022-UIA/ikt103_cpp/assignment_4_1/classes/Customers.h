//
// Created by Andreas on 28.04.2022.
//

#ifndef ASSIGNMENT_4_1_CUSTOMERS_H
#define ASSIGNMENT_4_1_CUSTOMERS_H


#include <string>

class Customers {
public:
    std::string id;
    std::string name;
    std::string address;

    Customers(std::string id, std::string name, std::string address);
};


#endif //ASSIGNMENT_4_1_CUSTOMERS_H
