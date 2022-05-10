//
// Created by Andreas on 28.01.2022.
//

#ifndef ASSIGNMENT_2_1_STUDENT_H
#define ASSIGNMENT_2_1_STUDENT_H


#include <iostream>

class Student {

public:
    int id{};
    std::string name,eMail;
    Student(std::string Name, std::string Email);
    void print() const;
    void print_menu(int choice) const;
};


#endif //ASSIGNMENT_2_1_STUDENT_H
