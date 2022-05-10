//
// Created by Andreas on 30.01.2022.
//

#include "Test.h"

#include <utility>


Test::Test(std::string CourseName, std::string TestName, std::string DateTime)
{
    courseName = std::move(CourseName);
    dateTime = std::move(DateTime);
    testName = std::move(TestName);

}

void Test::print() const {
    std::cout << "test id = " << id << ", ";
    std::cout << "course name = " << courseName << ", ";
    std::cout << "test name = " << testName << ", ";
    std::cout << "date = " << dateTime << std::endl;

}

void Test::print_menu(int choice) const {
    std::cout << "choice = " << choice << ", ";
    std::cout << "course name = " << courseName << ", ";
    std::cout << "test name = " << testName << ", ";
    std::cout << "date = " << dateTime << std::endl;

}


