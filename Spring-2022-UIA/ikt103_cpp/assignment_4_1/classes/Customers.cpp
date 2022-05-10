//
// Created by Andreas on 28.04.2022.
//

#include "Customers.h"

#include <utility>

Customers::Customers(std::string id, std::string name, std::string address) {
    this->id = id;
    this->name = std::move(name);
    this->address = std::move(address);
}


