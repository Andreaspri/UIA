//
// Created by Andreas on 28.01.2022.
//
#include <iostream>
#include <utility>
#include "Student.h"


Student::Student(std::string Name, std::string Email)
{
    name = std::move(Name);
    eMail = std::move(Email);
}

void Student::print() const {
    std::cout << "student id = " << id << ", ";
    std::cout << "name = " << name << ", ";
    std::cout << "email = " << eMail << std::endl;
}

void Student::print_menu(int choice) const {
    std::cout << "choice = " << choice << ": ";
    std::cout << "name = " << name << ", ";
    std::cout << "email = " << eMail << std::endl;

}






