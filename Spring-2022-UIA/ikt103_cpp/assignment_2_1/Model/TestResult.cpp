//
// Created by Andreas on 30.01.2022.
//

#include "TestResult.h"

#include <utility>

TestResult::TestResult(int StudentId, int TestId, std::string Grade)
{
    studentId = StudentId;
    testId = TestId;
    grade = std::move(Grade);
}

void TestResult::print(const Test& test) const
{
    std::cout << "student id = " << studentId << ", ";
    std::cout << "course name = " << test.courseName << ", ";
    std::cout << "test id = " << test.id << ", ";
    std::cout << "test name = " << test.testName << ", ";
    std::cout << "grade = " << grade << std::endl;
}

