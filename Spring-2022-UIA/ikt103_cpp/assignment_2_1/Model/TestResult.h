//
// Created by Andreas on 30.01.2022.
//

#ifndef ASSIGNMENT_2_1_TESTRESULT_H
#define ASSIGNMENT_2_1_TESTRESULT_H

#include "Test.h"
class TestResult {

public:
    int studentId, testId;
    std::string grade;
    TestResult(int StudentId, int TestId, std::string Grade);

    void print(const Test& test) const;
};


#endif //ASSIGNMENT_2_1_TESTRESULT_H
