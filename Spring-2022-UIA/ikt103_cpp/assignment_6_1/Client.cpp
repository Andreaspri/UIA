//
// Created by Andreas on 30.03.2022.
//

#include "Client.h"
#include <iostream>


void Client::read_all_students() {


    auto request = client.request(methods::GET, uri_builder(U("students")).to_string())
            .then([](const http_response response)
                  {
                      if (response.status_code() != 200)
                          ucout << "Error: " << response.status_code() << std::endl;


                      return response.extract_json();
                  })

            .then([](json::value json_object_array)
                  {

                      for(auto& student : json_object_array.as_array())
                      {
                          ucout << "id: " << student[U("id")].as_integer() << ", ";
                          ucout << "name: " << student[U("name")].as_string() << ", ";
                          ucout << "email: " << student[U("email")].as_string() << ", ";
                          ucout << "year: " << student[U("year")].as_integer() << std::endl;
                      }
                  });

    request.wait();

}

void Client::get_student_by_id()
{

    std::cout << "Enter id: " << std::endl;
    std::string id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, id);



    auto request = client.request(methods::GET, uri_builder(U("students")).append_path(utility::conversions::to_string_t(id)).to_string())
            .then([](const http_response response)
                  {
                    if (response.status_code() != 200) {
                        ucout << "Student not found" << std::endl;
                    }
                        return response.extract_json();
                  })

            .then([](json::value json_object)
            {
                if (!json_object[U("id")].is_null())
                {
                    ucout << "id: " << json_object[U("id")].as_integer() << ", ";
                    ucout << "name: " << json_object[U("name")].as_string() << ", ";
                    ucout << "email: " << json_object[U("email")].as_string() << ", ";
                    ucout << "year: " << json_object[U("year")].as_integer() << std::endl;
                }
            });

    request.wait();
}

void Client::add_student() {
    std::string name;
    std::string email;
    int year;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Name: " << std::endl;
    std::getline(std::cin, name);

    std::cout << "Email: " << std::endl;
    std::getline(std::cin, email);

    std::cout << "Year: " << std::endl;
    std::cin >> year;

    json::value student;

    student[U("name")] = json::value::string(utility::conversions::to_string_t(name));
    student[U("email")] = json::value::string(utility::conversions::to_string_t(email));
    student[U("year")] = json::value::number(year);

    auto request = client.request(methods::POST,
                         uri_builder(U("students/")).to_string(),
                         student.serialize(), U("application/json"))
            .then([](const http_response response)
                  {
                      if (response.status_code() != 201) {
                          ucout << "Error: " << response.status_code() << std::endl;
                      }
                      return response.extract_json();
                  })

            .then([](json::value json_object)
                  {
                      if (!json_object[U("id")].is_null())
                      {
                          ucout << "Added student: ";
                          ucout << "id: " << json_object[U("id")].as_integer() << ", ";
                          ucout << "name: " << json_object[U("name")].as_string() << ", ";
                          ucout << "email: " << json_object[U("email")].as_string() << ", ";
                          ucout << "year: " << json_object[U("year")].as_integer() << std::endl;
                      }
                  });
    request.wait();
}

void Client::edit_student()
{
    int id;
    std::string name;
    std::string email;
    int year;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Id: " << std::endl;
    std::cin >> id;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Name: " << std::endl;
    std::getline(std::cin, name);

    std::cout << "Email: " << std::endl;
    std::getline(std::cin, email);

    std::cout << "Year: " << std::endl;
    std::cin >> year;

    std::string string_id = std::to_string(id);


    json::value student;

    student[U("id")] = json::value::number(id);
    student[U("name")] = json::value::string(utility::conversions::to_string_t(name));
    student[U("email")] = json::value::string(utility::conversions::to_string_t(email));
    student[U("year")] = json::value::number(year);

    auto request = client.request(methods::PUT, uri_builder(U("students")).
    append_path(utility::conversions::to_string_t(string_id)).to_string(), student.serialize(), U("application/json"))
            .then([](const http_response response)
                  {
                      if (response.status_code() != 200)
                          ucout << "Student not found" << std::endl;
                      else
                          ucout << "Student was edited successfully" << std::endl;

                  });
    request.wait();
}

void Client::remove_student()
{

    std::string id;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Id: " << std::endl;
    std::getline(std::cin, id);



    auto request = client.request(methods::DEL, uri_builder(U("students")).append_path(utility::conversions::to_string_t(id)).to_string())
            .then([](const http_response response)
                  {
                      if (response.status_code() != 204) {
                          ucout << "Student not found" << std::endl;
                      } else
                          ucout << "Student was removed successfully" << std::endl;
                  });


    request.wait();
}
