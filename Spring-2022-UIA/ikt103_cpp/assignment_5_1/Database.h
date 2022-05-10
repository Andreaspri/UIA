//
// Created by Andreas on 31.03.2022.
//

#ifndef ASSIGNMENT_5_1_DATABASE_H
#define ASSIGNMENT_5_1_DATABASE_H


#include <string>
#include <SQLiteCpp/SQLiteCpp.h>



class Database {

public:

    Database();


    void read_all_student();
    void get_student_by_id();
    void add_student();
    void edit_student();
    void remove_student();
    void search();


private:
    SQLite::Database db = SQLite::Database("school.sqlite", SQLite::OPEN_READWRITE);


};


#endif //ASSIGNMENT_5_1_DATABASE_H
