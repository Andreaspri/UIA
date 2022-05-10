//
// Created by Andreas on 30.01.2022.
//


#include "MainController.h"

void MainController::addStudent() {
    std::string name;
    std::string email;
    std::cout << "Enter name: " << std::endl;
    std::getline(std::cin, name);
    std::cout << "Enter email: " << std::endl;
    std::getline(std::cin, email);
    Student student(name, email);
    db.addStudent(student);
}

void MainController::addTest() {
    std::string courseName;
    std::string testName;
    std::string date;
    std::cout << "Enter course name: " << std::endl;
    std::getline(std::cin, courseName);
    std::cout << "Enter test name: " << std::endl;
    std::getline(std::cin, testName);
    std::cout << "Enter date: " << std::endl;
    std::getline(std::cin, date);
    Test test(courseName, testName, date);
    db.addTest(test);
}

void MainController::addTestResult() {
    auto students = db.printStudentsMenu();

    int input;
    std::cout << "Student choice: " << std::endl;
    std::cin >> input; std::cin.ignore();
    if (input > students.size() || input < 1) {
        return;
    }
    Student student = students.at(input);

    auto tests = db.printTestsMenu();
    std::cout << "Test choice: " << std::endl;
    std::cin >> input; std::cin.ignore();
    if (input > tests.size() || input < 1) {
        return;
    }
    Test test = tests.at(input);

    std::string grade;
    std::cout << "Enter grade: " << std::endl;
    std::getline(std::cin, grade);
    TestResult testResult = TestResult(student.id, test.id, grade);
    db.addTestResult(testResult);
}

void MainController::editStudent() {
    std::map<int, Student> students = db.printStudentsMenu();
    int input;

    std::cin >> input; std::cin.ignore();
    if (input > students.size() || input < 1) {
        return;
    }
    Student student = students.at(input);
    std::cout << "Enter name: " << std::endl;
    std::getline(std::cin, student.name);
    std::cout << "Enter email: " << std::endl;
    std::getline(std::cin, student.eMail);
    db.editStudent(student);
}

void MainController::editTest() {
    std::map<int, Test> tests = db.printTestsMenu();
    int input;

    std::cin >> input; std::cin.ignore();
    if (input > tests.size() || input < 1) {
        return;
    }
    Test test = tests.at(input);
    std::cout << "Enter course name: " << std::endl;
    std::getline(std::cin, test.courseName);
    std::cout << "Enter test name: " << std::endl;
    std::getline(std::cin, test.testName);
    std::cout << "Enter date: " << std::endl;
    std::getline(std::cin, test.dateTime);
    db.editTest(test);
}

void MainController::editTestResult() {
    auto students = db.printStudentsMenu();


    int input;
    std::cout << "Student choice: " << std::endl;
    std::cin >> input; std::cin.ignore();
    if (input > students.size() || input < 1) {
        return;
    }
    Student student = students.at(input);

    auto tests = db.printTestsMenu();
    std::cout << "Test choice: " << std::endl;
    std::cin >> input; std::cin.ignore();
    if (input > tests.size() || input < 1) {
        return;
    }
    Test test = tests.at(input);

    std::string grade;
    std::cout << "Enter grade: " << std::endl;
    std::getline(std::cin, grade);
    TestResult testResult = TestResult(student.id, test.id, grade);
    db.editTestResult(testResult);
}

void MainController::removeStudent() {
    std::map<int, Student> students = db.printStudentsMenu();
    int input;

    std::cin >> input; std::cin.ignore();
    if (input > students.size() || input < 1) {
        return;
    }
    Student student = students.at(input);
    db.removeStudent(student.id);
}

void MainController::removeTest() {
    std::map<int, Test> tests = db.printTestsMenu();
    int input;

    std::cin >> input; std::cin.ignore();
    if (input > tests.size() || input < 1) {
        return;
    }
    Test test = tests.at(input);
    db.removeTest(test.id);
}



void MainController::removeTestResult() {
    auto students = db.printStudentsMenu();

    int input;
    std::cout << "Student choice: " << std::endl;
    std::cin >> input; std::cin.ignore();
    if (input > students.size() || input < 1) {
        return;
    }
    Student student = students.at(input);

    auto tests = db.printTestsMenu();
    std::cout << "Test choice: " << std::endl;
    std::cin >> input; std::cin.ignore();
    if (input > tests.size() || input < 1) {
        return;
    }
    Test test = tests.at(input);

    db.removeTestResult(student.id, test.id);

}

void MainController::showAll() {
    std::cout << "Student details:" << std::endl;
    db.printStudents();
    std::cout << "Test details:" << std::endl;
    db.printTests();
    std::cout << "Test results:" << std::endl;
    db.printTestResults();
}










