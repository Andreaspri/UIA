#include <iostream>
#include "Database.h"
#include <sqlite3.h>


int main() {

    sqlite3 * DB;
    sqlite3_open("school.sqlite", &DB);

    auto db = Database();


    while (true)
    {
        int action = 0;
        std::cout << "1. Read all students" << std::endl;
        std::cout << "2. Get student by id" << std::endl;
        std::cout << "3. Add student" << std::endl;
        std::cout << "4. Edit student" << std::endl;
        std::cout << "5. Remove student" << std::endl;
        std::cout << "6. Search" << std::endl;
        std::cout << "7. Exit" << std::endl;
        std::cin >> action;
        switch (action) {
            case 1:
            {
                db.read_all_student();
                break;
            }
            case 2:
            {
                db.get_student_by_id();
                break;
            }
            case 3:
            {
                db.add_student();
                break;
            }
            case 4:
            {
                db.edit_student();
                break;
            }
            case 5:
            {
                db.remove_student();
                break;
            }
            case 6:
            {
                db.search();
                break;
            }
            case 7:
            {
                sqlite3_close(DB);
                return 0;
            }
            default:
            {
                std::cout << "Invalid input" << std::endl;
            }

        }
    }




}