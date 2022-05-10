//
// Created by Andreas on 30.01.2022.
//

#include <map>
#include "Database.h"

void Database::addStudent(Student student) {
    student.id = auto_increment_students_id++;
    students.push_back(student);
}

void Database::addTest(Test test) {
    test.id = auto_increment_tests_id++;
    tests.push_back(test);
}

void Database::addTestResult(const TestResult& testResult) {
    testResults.push_back(testResult);
}

void Database::editStudent(const Student& student) {
    for (auto & i : students) {
        if (i.id == student.id) {
            i = student;
            break;
        }
    }

}

void Database::editTest(const Test& test) {
    for (auto & i : tests) {
        if (i.id == test.id) {
            i = test;
            break;
        }
    }
}

void Database::editTestResult(const TestResult& testResult) {
    for (auto & i : testResults) {
        if (i.testId == testResult.testId && i.studentId == testResult.studentId) {
            i = testResult;
            break;
        }
    }
}

void Database::removeStudent(int studentId) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i].id == studentId) {
            students.erase(students.begin() + i);
            break;
        }
    }
// Remove all test related to student
    for (int i = 0; i < testResults.size(); i++) {
        if (testResults[i].studentId == studentId) {
            testResults.erase(testResults.begin() + i);
            i--;
        }
    }
}

void Database::removeTest(int testId) {
    for (int i = 0; i < tests.size(); i++) {
        if (tests[i].id == testId) {
            tests.erase(tests.begin() + i);
            break;
        }
    }
// Remove all test results related to test
    for (int i = 0; i < testResults.size(); i++) {
        if (testResults[i].testId == testId) {
            testResults.erase(testResults.begin() + i);
            i--;
        }
    }
}

void Database::removeTestResult(int studentId, int testId) {
    for (int i = 0; i < testResults.size(); i++) {
        if (testResults[i].studentId == studentId && testResults[i].testId == testId) {
            testResults.erase(testResults.begin() + i);
            break;
        }
    }
}

void Database::printStudents() {
    for (auto & student : students) {
        student.print();
    }
}

void Database::printTests() {
    for (auto & test : tests) {
        test.print();
    }
}

void Database::printTestResults() {
    std::map<int, Test> testMap;
    for (auto & test : tests) {
        testMap.insert({test.id, test});
    }

    for (auto & testResult : testResults) {
        testResult.print(testMap.find(testResult.testId)->second);
    }
}

std::map<int, Student> Database::printStudentsMenu() {
    std::map<int, Student> studentMap;
    for (int i = 0; i < students.size(); i++) {
        students[i].print_menu(i + 1);
        studentMap.insert({i+1, students[i]});
    }
    return studentMap;
}

std::map<int, Test> Database::printTestsMenu() {
    std::map<int, Test> testMap;
    for (int i = 0; i < tests.size(); i++) {
        tests[i].print_menu(i + 1);
        testMap.insert({i+1, tests[i]});
    }
    return testMap;
}












