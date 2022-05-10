#include <iostream>
#include <cstdio>
#include <list>
#include "rapidjson/include/rapidjson/filereadstream.h"
#include "rapidjson/include/rapidjson/document.h"
#include "student.h"

int main() {

    FILE* f = fopen("students.json", "r");

    char readBuffer[65536];
    rapidjson::FileReadStream is(f, readBuffer, sizeof(readBuffer));


    rapidjson::Document d;

    d.ParseStream(is);

    fclose(f);


    std::list<Student*> students;

    // add all student to students list
    for (int i = 0; i < d.Size(); i++) {
        auto* student_t = new Student();
        student_t->name = d[i]["name"].GetString();
        student_t->id = d[i]["id"].GetInt();
        student_t->age = d[i]["age"].GetInt();
        student_t->attendance = d[i]["attendance"].GetInt();
        students.push_back(student_t);
    }

    // sort students by age;
    students.sort(Student::compareByAge);

    //print youngest student
    std::cout << "Youngest: " << students.front()->name << std::endl;

    // print oldest student
    std::cout << "Oldest: " << students.back()->name << std::endl;

    // calculate average student age

    int sum = 0;
    for (auto& student : students) {
        sum += student->age;
    }
    std::cout << "Average age: " << sum / students.size() << std::endl;

    // print students with attendance less than 30%

    for (auto& student : students) {
        if (student->attendance < 30) {
            std::cout << "Bad student: " << student->name << std::endl;
        }
    }


    return 0;
}
