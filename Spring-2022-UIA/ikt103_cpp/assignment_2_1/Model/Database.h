//
// Created by Andreas on 30.01.2022.
//

#ifndef ASSIGNMENT_2_1_DATABASE_H
#define ASSIGNMENT_2_1_DATABASE_H

#include <iostream>
#include <vector>
#include <map>

#include "Student.h"
#include "Test.h"
#include "TestResult.h"





class Database {
private:
    int auto_increment_students_id = 1;
    int auto_increment_tests_id = 1;

    std::vector<Student> students;
    std::vector<Test> tests;
    std::vector<TestResult> testResults;


public:

    void addStudent(Student student);
    void addTest(Test test);
    void addTestResult(const TestResult& testResult);

    void editStudent(const Student& student);
    void editTest(const Test& test);
    void editTestResult(const TestResult& testResult);

    void removeStudent(int studentId);
    void removeTest(int testId);
    void removeTestResult(int studentId, int testId);


    std::map<int, Student> printStudentsMenu();
    std::map<int, Test> printTestsMenu();

    void printStudents();
    void printTests();
    void printTestResults();








};


#endif //ASSIGNMENT_2_1_DATABASE_H
