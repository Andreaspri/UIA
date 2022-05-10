//
// Created by Andreas on 31.03.2022.
//


#include "Database.h"
#include <iostream>
#include <sqlite3.h>
#include <limits>


Database::Database() {
    const char *table;

    SQLite::Statement(db,"DROP TABLE IF EXISTS Students").exec();

    table = "CREATE TABLE IF NOT EXISTS Students("  \
      "id INTEGER PRIMARY KEY," \
      "name           TEXT," \
      "email          TEXT," \
      "year           INT);";

    SQLite::Statement(db, table).exec();


}


void Database::add_student() {

    std::string name;
    std::string email;
    int year;
    std::string command;
    int id;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Name:" << std::endl;
    std::getline(std::cin,name);
    std::cout << "Email:" << std::endl;
    std::cin >> email;
    std::cout << "Year:" << std::endl;
    std::cin >> year;


    command = "SELECT * FROM Students ORDER BY id DESC LIMIT 1;";

    SQLite::Statement idQuery(db,command);


    if (idQuery.tryExecuteStep() == SQLITE_DONE)
        id = 1;
    else
        id = idQuery.getColumn("id").getInt()+1;



    command = "INSERT INTO Students(id,name,email,year) "
              "VALUES (?,?,?,?)";


    SQLite::Statement insert(db,command);

    insert.bind(1,id);
    insert.bind(2,name);
    insert.bind(3,email);
    insert.bind(4,year);

    insert.exec();


    command = "SELECT * FROM Students ORDER BY id DESC LIMIT 1;";

    SQLite::Statement query(db,command);



    query.tryExecuteStep();
    std::cout << "Added student: ";
    std::cout << "id: ";
    std::cout << query.getColumn("id");
    std::cout << ", name: ";
    std::cout << query.getColumn("name");
    std::cout << ", email: ";
    std::cout << query.getColumn("email");
    std::cout << ", year: ";
    std::cout << query.getColumn("year") << std::endl;


}



void Database::read_all_student() {
    std::string command;

    command = "SELECT * FROM Students";

    SQLite::Statement query(db,command);


    if (query.tryExecuteStep() != SQLITE_ROW)
    {
        std::cout << "No students found" << std::endl;
        return;
    }

    do
    {
        std::cout << "id: ";
        std::cout << query.getColumn("id");
        std::cout << ", name: ";
        std::cout << query.getColumn("name");
        std::cout << ", email: ";
        std::cout << query.getColumn("email");
        std::cout << ", year: ";
        std::cout << query.getColumn("year") << std::endl;
    }while (query.tryExecuteStep() == SQLITE_ROW);

}


void Database::get_student_by_id() {
    std::string command;
    int id;

    std::cout << "Id: " << std::endl;
    std::cin >> id;


    command = "SELECT * FROM Students WHERE id =" + std::to_string(id);

    SQLite::Statement query(db,command);

    if (query.tryExecuteStep() != SQLITE_ROW)
    {
        std::cout << "Student not found" << std::endl;
        return;
    }


    query.tryExecuteStep();
    std::cout << "id: ";
    std::cout << query.getColumn("id");
    std::cout << ", name: ";
    std::cout << query.getColumn("name");
    std::cout << ", email: ";
    std::cout << query.getColumn("email");
    std::cout << ", year: ";
    std::cout << query.getColumn("year") << std::endl;
}

void Database::edit_student() {
    std::string name;
    std::string email;
    int year;
    int id;
    std::string command;

    std::cout << "Id:" << std::endl;
    std::cin >> id;


    SQLite::Statement check(db,"SELECT * FROM Students WHERE id = " + std::to_string(id));
    if (check.tryExecuteStep() == SQLITE_DONE)
    {
        std::cout << "Student not found" << std::endl;
        return;
    }


    std::cout << "Name:" << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin,name);
    std::cout << "Email:" << std::endl;
    std::cin >> email;
    std::cout << "Year:" << std::endl;
    std::cin >> year;

    command = "UPDATE Students"
              " SET name = '" + name +
              "', email = '" + email +
              "', year = " + std::to_string(year) +
              " WHERE id = " + std::to_string(id) + ";";

    SQLite::Statement(db,command).exec();


    std::cout << "Student was edited successfully" << std::endl;


}

void Database::remove_student()
{
    std::string id;
    std::cout << "Id: " << std::endl;
    std::cin >> id;

    std::string command = "DELETE FROM Students WHERE id = " + id;

    int response = SQLite::Statement(db,command).exec();

    if (!response)
    {
        std::cout << "Student not found" << std::endl;
    }
    else
        std::cout << "Student was removed successfully" << std::endl;

}

void Database::search()
{
    std::string input;
    std::string command;

    std::cout << "Search string: " << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin,input);

    command = "SELECT * FROM Students WHERE name LIKE '" + input + "';";

    SQLite::Statement query(db,command);

    if (query.tryExecuteStep() == SQLITE_DONE)
        std::cout << "No results for " + input;
    else
    {
        do
        {
            std::cout << "id: ";
            std::cout << query.getColumn("id");
            std::cout << ", name: ";
            std::cout << query.getColumn("name");
            std::cout << ", email: ";
            std::cout << query.getColumn("email");
            std::cout << ", year: ";
            std::cout << query.getColumn("year") << std::endl;
        }while (query.tryExecuteStep() == SQLITE_ROW);
    }

}

