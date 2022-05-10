//
// Created by Andreas on 30.03.2022.
//

#ifndef ASSIGNMENT_6_1_CLIENT_H
#define ASSIGNMENT_6_1_CLIENT_H


#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/uri.h>


using namespace web;
using namespace web::http;
using namespace web::http::client;


class Client {
public:


    void read_all_students();
    void get_student_by_id();
    void add_student();
    void edit_student();
    void remove_student();



private:
    http_client client = http_client(U("http://localhost:5000"));
};

#endif //ASSIGNMENT_6_1_CLIENT_H
