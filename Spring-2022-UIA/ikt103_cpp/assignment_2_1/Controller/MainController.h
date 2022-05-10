//
// Created by Andreas on 30.01.2022.
//

#ifndef ASSIGNMENT_2_1_MAINCONTROLLER_H
#define ASSIGNMENT_2_1_MAINCONTROLLER_H
#include "../Model/Database.h"


class MainController{
    
private:
    Database db = Database();
public:
    void addStudent();
    void addTest();
    void addTestResult();

    void editStudent();
    void editTest();
    void editTestResult();

    void removeStudent();
    void removeTest();
    void removeTestResult();

    void showAll();
    
            
        };


#endif //ASSIGNMENT_2_1_MAINCONTROLLER_H
