//
// Created by Andreas on 30.01.2022.
//

#ifndef ASSIGNMENT_2_1_TEST_H
#define ASSIGNMENT_2_1_TEST_H

#include <iostream>

class Test {

public:
    int id{};
    std::string courseName, dateTime, testName;
    Test(std::string CourseName, std::string TestName, std::string DateTime);

    void print() const;
    void print_menu(int choice) const;
};


#endif //ASSIGNMENT_2_1_TEST_H
