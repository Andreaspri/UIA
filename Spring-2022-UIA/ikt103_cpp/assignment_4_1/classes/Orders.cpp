//
// Created by Andreas on 28.04.2022.
//

#include "Orders.h"

#include <utility>

Orders::Orders(std::string  id, std::string  customerId, std::string  productId, std::string  amount) {
    this->id = std::move(id);
    this->customerId = std::move(customerId);
    this->productId = std::move(productId);
    this->amount = std::move(amount);
}


