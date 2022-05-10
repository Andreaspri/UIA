//
// Created by Andreas on 28.04.2022.
//

#include "Products.h"

#include <utility>

Products::Products(std::string id, std::string name, std::string price) {
    this->id = std::move(id);
    this->name = std::move(name);
    this->price = std::move(price);
}

