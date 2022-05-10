#include <iostream>
#include "rapidcsv/src/rapidcsv.h"
#include "classes/Customers.h"
#include "classes/Products.h"
#include "classes/Orders.h"




int main() {

    std::vector<Customers> customers;
    std::vector<Products> products;
    std::vector<Orders> orders;

    rapidcsv::Document doc("customers.csv");


    std::vector<int> customer_ids = doc.GetColumn<int>("id");

    for (int i = 0; i < customer_ids.size(); i++) {
        auto customer = doc.GetRow<std::string>(i);
        customers.emplace_back(customer[0],customer[1],customer[2]);
    }

    doc = rapidcsv::Document("products.csv");

    std::vector<int> product_ids = doc.GetColumn<int>("id");

    for (int i = 0; i < product_ids.size(); i++) {
        auto product = doc.GetRow<std::string>(i);
        products.emplace_back(Products(product[0],product[1],product[2]));
    }

    doc = rapidcsv::Document("orders.csv");

    std::vector<int> order_ids = doc.GetColumn<int>("id");

    for (int i = 0; i < order_ids.size(); i++) {
        auto order = doc.GetRow<std::string>(i);
        orders.emplace_back(Orders(order[0],order[1],order[2],order[3]));
    }

// print every customer
    for (auto & customer : customers) {
        std::cout << "Customer: " << customer.name << ", " << customer.address << std::endl;
    }
    // print every product
    for (auto & product : products) {
        std::cout << "Product: " << product.name << ", " << product.price << std::endl;
    }

    // print total amount per product
    for (auto & product : products) {
        int total_amount = 0;
        for (auto & order : orders) {
            if (order.productId == product.id) {
                total_amount += std::atoi(order.amount.c_str());
            }
        }
        std::cout << product.name << " amount: " << total_amount << std::endl;
    }

    // print total spent per product
    for (auto & product : products) {
        float total_spent = 0;
        for (auto & order : orders) {
            if (order.productId == product.id) {
                total_spent += std::atoi(order.amount.c_str()) * std::stof(product.price);
            }
        }
        std::cout << product.name << " gross income: " << total_spent << std::endl;
    }

// print total spent per customer
    for (auto & customer : customers) {
        float total_spent = 0;
        for (auto & order : orders) {
            if (order.customerId == customer.id) {
                for (auto & product : products) {
                    if (order.productId == product.id) {
                        total_spent += std::atoi(order.amount.c_str()) * std::stof(product.price);
                    }
                }
            }
        }
        std::cout << customer.name << " money spent: " << total_spent << std::endl;
    }

    return 0;


}
