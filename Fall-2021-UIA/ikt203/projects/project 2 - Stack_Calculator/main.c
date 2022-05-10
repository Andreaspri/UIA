#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#include <stack.h>
#include <myString.h>


// Function declarations:

void operation(Stack_int*, char);

Stack_str *convert_algebraic(Stack_str *stack, char *values);

void RPN_calculator(Stack_int*);


int main() {
    printf("Enter a calculation. For postfix, one operand and operator at a time.\n"
           "For operator_stack enter the entire string to calculate. It will be converted to postfix.\n");
    printf("\n");
    // Prerequisite to enable usage of rand()
    srand(time(0));

    // Create a stack with random size between min and max stack size
    Stack_int *stack_int = create_stack_int((rand() % (MAXSTACKSIZE - MINSTACKSIZE + 1)) + MINSTACKSIZE);

    //Stack_str *stack_str = algebraic_to_PSN(stack_str_);
    printf("Casio calculator(RPN):\n");

    // Do the calculator magic with the stack as "workspace"
    RPN_calculator(stack_int);

    return 0;
}


// Function definitions:

// Pops integer operators from the given stack and calculates them using the operator given.
void operation(Stack_int *stack, char operator){

    // Pops the two top integers from the main int stack
    int x = pop_int(stack, top_index_int(stack));
    int y = pop_int(stack, top_index_int(stack));

    // Error handling from pop
    if (x == INT_MIN || y == INT_MIN){
        printf("Syntax Error!\n");
        empty_stack_int(stack);
    }

    // Operator handling in order of (y operator x)
    else if (operator == '+')
        push_int(stack, y+x);
    else if (operator == '-')
        push_int(stack, y-x);
    else if (operator == '*')
        push_int(stack, y*x);
    else if (operator == '/'){
        if (x != 0)
            push_int(stack, y/x);
        else{
            printf("Error, not possible to divide by zero!\n");
        }
    }
    else{
        printf("Syntax error!\n");
        empty_stack_int(stack);
    }
}

// The main RPN calculator function
void RPN_calculator(Stack_int *stack) {

    // Repeat as long as the stack is not full
    while (!isFull_int(stack)) {

        // Create a minimalistic sting of input (sized to user input)
        printf("Type your number, operator or infix equation: \n");
        char *values = create_string();
        int last_index = string_length(values) - 1;
        int value = 0;

        // Check if given strings first character is an integer and has a size of 1
        if (!isdigit(values[0]) && last_index == 0){
            // Do the operation on the operator
            operation(stack, values[0]);
        }
        else {
            // We are dealing with a number, or a more complex input

            // Iterate over the user input
            for (int i = 0; i <= last_index; i++) {

                // Checks if character at index i from the END of user input is NOT a number
                if (!isdigit(values[last_index - i])) {
                    // Using stack with strings to print / retrieve data
                    Stack_str *stack_str = create_stack_str(MINSTACKSIZE);
                    stack_str->next = NULL;

                    // Converting to postfix
                    stack_str = convert_algebraic(stack_str, values);
                    if (stack_str == NULL){
                        printf("Syntax error!\n");
                        stack->topOfStack = EMPTYTOS;
                        goto converter;
                    }
                    Stack_str *current_node = stack_str;

                    // Printing postfix equation
                    printf("Converted from infix to postfix\n");
                    // Step through the nodes
                    while (current_node != NULL){
                        // Iterate over the node array and print each character
                        for (int j = 0; j<= top_index_str(current_node); j++)
                            printf("%c", current_node->array[j]);
                        current_node = current_node->next;
                    }
                    printf("\n");

                    // Sets our node back to the operator stack
                    current_node = stack_str;
                    int found_whole_number;

                    // Calculating the answer, while iterating over the nodes from our input
                    while (current_node != NULL){

                        // Resetting state and value.
                        found_whole_number = 0;
                        value = 0;
                        for (int j = 0; j<= top_index_str(current_node); j++)
                            // Converting string to integer using 10.base converting algorithm, and add it to the value.
                            if (isdigit(current_node->array[j])){
                                value += (current_node->array[top_index_str(current_node)-j] - '0') * (pow(10, j));
                                found_whole_number = 1;
                            }
                            else {
                                // Executing the current operation
                                operation(stack, current_node->array[0]);
                            }
                        if (found_whole_number){
                            // Pushing next integer to the stack
                            push_int(stack, value);
                        }
                        current_node = current_node->next;
                    }
                    // Display the current answer from the stack(without touching the stack)
                    printf("Answer: %i\n", stack_peek_int(stack));

                    // Go to the end of this iteration of the loop
                    goto converter;
                }
                else {
                    // Character at index i from the END is an integer, use 10.base algorithm:
                    value += (values[last_index-i] - '0') * (pow(10, i));
                }
            }
            push_int(stack, value);
        }
        // Skip to the next iteration of the while loop
        converter:;

        // Printing the current stack
        printf("\nCurrent stack: \n");
        for (int i = 0; i <= top_index_int(stack); i++) {
            printf("%i ", stack->array[i]);
        }
        printf("\n");
    }
}

// Converts an algebraic string to an RPN string.
Stack_str *convert_algebraic(Stack_str *stack, char *values){

    // Appoint our main stack
    Stack_str *current_stack = stack;
    int last_index = string_length(values) - 1;

    // Create the operator stack
    Stack_str *operator_stack = create_stack_str(MINSTACKSIZE);

    // Create an iterator for our stack logic
    Stack_str *current_operator_stack  = operator_stack;
    current_operator_stack->next = NULL;

    // Initialize variables
    int number_count = 0;
    int operator_count_ = 0;
    int last_i = 0;

    // Loops trough algebraic string.
    for (int i = 0; i<=last_index; i++) {

        if (values[i] == '(') {
            // We found a starting parenthesis

            // Create a new stack and set the iterative operator stack to this stack
            current_operator_stack->next = create_stack_str(MINSTACKSIZE);
            current_operator_stack = current_operator_stack->next;
            current_operator_stack->next = NULL;
        }
        else if (values[i] == ')') {
            // We found a closing parenthesis

            // Get the amount of operators on the current iteration of the operator stack
            int len = top_index_str(current_operator_stack);
            if (len != CHAR_MIN) {

                // Iterate over the current operator stack
                for (int j = 0; j <= len; j++) {

                    // Pop operator from operator stack and push it to the current stack
                    push_str(current_stack, pop_str(current_operator_stack, top_index_str(current_operator_stack)));

                    // Create a new main stack and set the current stack to that stack
                    current_stack->next = create_stack_str(MINSTACKSIZE);
                    current_stack = current_stack->next;
                }
            }
            // Clear the last stack (unused now)
            operator_stack = delete_last_stack(operator_stack);
            current_operator_stack = last_element(operator_stack);

            // Get the current size of the current operator stack
            len = top_index_str(current_operator_stack);
            if (len != CHAR_MIN) {

                // Iterate over the operators in the stack
                for (int j = 0; j <= len; j++) {

                    // Pop the operators from the current operator stack and push them to the main current stack
                    push_str(current_stack, pop_str(current_operator_stack, top_index_str(current_operator_stack)));

                    // Create a new main stack
                    current_stack->next = create_stack_str(MINSTACKSIZE);
                    current_stack = current_stack->next;
                }
            }
        }
        else if (!isdigit(values[i])) {
            // Current index of user input is an operator (not including parenthesis)

            // Increment the operator count and push the operator to the current operator stack
            operator_count_++;
            push_str(current_operator_stack, values[i]);

            // Get the amount of operators on the current operator stack
            int len = top_index_str(current_operator_stack);

            // Check for higher priority operators in the user input
            if ((values[last_i] == '*' || values[last_i] == '/') && (values[i] != '(')) {
                // Pop operator from the current operator stack and push it to the main current stack
                push_str(current_stack, pop_str(current_operator_stack, len));

                // Create a new main stack and set the current stack to that stack
                current_stack->next = create_stack_str(MINSTACKSIZE);
                current_stack = current_stack->next;
                current_stack->next = NULL;
                continue;
            }
            if (len>0){
                for (int j = 0; j<len; j++){
                    push_str(current_stack, pop_str(current_operator_stack, 0));
                    current_stack->next = create_stack_str(MINSTACKSIZE);
                    current_stack = current_stack->next;
                    current_stack->next = NULL;
                }
            }
        }
        else {
            // We are dealing with a number

            // Increment the number count
            number_count++;

            // Push the current number to the current main stack
            push_str(current_stack, values[i]);

            // Iterate over the user input until we find the end of the current number, pushing each part to the stack
            last_i = i;
            while (i != last_index && isdigit(values[i+1])){
                i++;
                push_str(current_stack, values[i]);
            }

            // Create a new main current stack and switch the main stack to that stack
            current_stack->next = create_stack_str(MINSTACKSIZE);
            current_stack = current_stack->next;
        }
    }

    // Check if there are any operators on the operator stack
    if (operator_count(operator_stack) > 0) {

        // Compress the operator stack to one stack element
        Stack_str *operator = operators(operator_stack);

        // Get the number of operators in the compressed stack
        int len = top_index_str(operator);
        for (int i = 0; i <= len; i++) {
            // Pops each operator from the compressed stack and pushes them to the current main stack
            push_str(current_stack, pop_str(operator, top_index_str(operator)));

            // Creates a new stack and sets the current stack to that stack
            current_stack->next = create_stack_str(MINSTACKSIZE);
            current_stack = current_stack->next;
        }

        // NULL-terminates the current stack
        current_stack = NULL;
    }
    // NULL-terminates the current stack
    current_stack = NULL;

    // Error handling. Illegal equation check.
    if (number_count-operator_count_ == 1)
        return stack;
    else
        return NULL;
}