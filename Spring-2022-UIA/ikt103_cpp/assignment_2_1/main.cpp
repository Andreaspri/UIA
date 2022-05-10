#include <iostream>
#include "Controller//MainController.h"

int main() {

    MainController mainController;

    while (true)
    {
        std::cout << "1. Add student" << std::endl;
        std::cout << "2. Edit student" << std::endl;
        std::cout << "3. Remove student" << std::endl;
        std::cout << "4. Add test" << std::endl;
        std::cout << "5. Edit test" << std::endl;
        std::cout << "6. Remove test" << std::endl;
        std::cout << "7. Add test result" << std::endl;
        std::cout << "8. Edit test result" << std::endl;
        std::cout << "9. Remove test result" << std::endl;
        std::cout << "10. Show all info" << std::endl;
        std::cout << "11. Exit" << std::endl;
        int choice;
        std::cin >> choice; std::cin.ignore();

        switch (choice) {
            case 1:
            {
                mainController.addStudent();
                break;
            }
            case 2:
            {
                mainController.editStudent();
                break;
            }
            case 3:
            {
                mainController.removeStudent();
                break;
            }
            case 4:
            {
                mainController.addTest();
                break;
            }
            case 5:
            {
                mainController.editTest();
                break;
            }
            case 6:
            {
                mainController.removeTest();
                break;
            }
            case 7:
            {
                mainController.addTestResult();
                break;
            }
            case 8:
            {
                mainController.editTestResult();
                break;
            }
            case 9:
            {
                mainController.removeTestResult();
                break;
            }
            case 10:
            {
                mainController.showAll();
                break;
            }
            case 11:
            {
                return 0;
            }
            default:
            {
                std::cout << "Invalid choice" << std::endl;
                break;
            }
        }

    }

}
