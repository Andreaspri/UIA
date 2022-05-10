
#include <iostream>

#include "Client.h"


int main() {

    int action;

    auto client = Client();


    while (true)
    {
        std::cout << "1. Read all students" << std::endl;
        std::cout << "2. Get student by id" << std::endl;
        std::cout << "3. Add student" << std::endl;
        std::cout << "4. Edit student" << std::endl;
        std::cout << "5. Remove student" << std::endl;
        std::cout << "6. Exit" << std::endl;

        std::cin >> action;

        switch (action) {
            case 1:
            {
                client.read_all_students();
                break;
            }
            case 2:
            {
                client.get_student_by_id();
                break;
            }
            case 3:
            {
                client.add_student();
                break;
            }
            case 4:
            {
                client.edit_student();
                break;
            }
            case 5:
            {
                client.remove_student();
                break;
            }
            case 6:
            {
                return 0;
            }
            default:
                std::cout << "Invalid input" << std::endl;
        }
    }

    return 0;
}
