//
// Created by Andreas on 29.04.2022.
//

#ifndef ASSIGNMENT_4_2_STUDENT_H
#define ASSIGNMENT_4_2_STUDENT_H


#include <string>

class Student {
public:
    int id;
    std::string name;
    int age;
    int attendance;

    static bool compareByAge(Student* first, Student* other);
};


#endif //ASSIGNMENT_4_2_STUDENT_H
