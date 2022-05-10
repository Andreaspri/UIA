//
// Created by Nixxen on 08.09.2021.
//

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "myString.h"

// Function definitions
// Dynamically allocate memory to the size of a string based on user input
char *create_string(){
    char *user_input;
    user_input=(char *) calloc(1, sizeof(char));
    int i=0, ii=0;
    while(* (user_input + ii) != '\n'){
        scanf("%c", (user_input + i));
        ii = i;
        i++;
        user_input = static_cast<char *>(realloc(user_input, (i + 1) * sizeof(char)));
    }
    // Strip the \n from the input
    user_input[strcspn(user_input, "\r\n")] = 0;
    return user_input;
}

// Returns the length of a string from a given char pointer, based on string '\0' terminator
int string_length(char *str) {
    int length = 0;

    // Check for array termination
    while (*str != '\0') {
        length++;
        str++;
    }
    return length;
}