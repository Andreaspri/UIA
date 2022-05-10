//
// Created by Nixxen on 23.10.2021.
//

#include <cctype>
#include <cstdlib>
#include <cstring>
#include "myString.h"
#include "laae.h"

bool NotEmpty(const char *expression) {
    /* returns true if expression is not empty string*/
    return (expression[0] != '\0');
}


char NextChar(const char *expression) {
    /* returns next character in expression, but nothing is consumed */
    // Some logic to scan for next char.
    // Return that char
    return expression[0];
}

//char *DeleteFirstNCharacters(char *expression, int startIndex){
//    // Note: This requires recursively returning as well. Use array fixing as workaround.
//    // Increase the start pointer in the char array to the new index.
//    expression += startIndex;
//    return expression;
//}

void DeleteFirstNCharacters(char *expression, int startIndex){
    // Iterate through the char array and move each char one to the left (other than the first).
    int i;
    for (i = startIndex; i < string_length(expression); ++i) {
        expression[i-startIndex] = expression[i];
    }
    expression[i-startIndex] = '\0';
}

char GetNextChar(char *expression) {
    /* returns next character in expression, but a character is consumed */
    // Some logic to scan for next char.
    // Store char in temp
    // Remove char from expression
    // Return temp
    char return_value = '\0';
    if (NotEmpty(expression)){
        return_value = expression[0];
        DeleteFirstNCharacters(expression, 1);
    }
    return return_value;
}


bool IsNum(char ch) {
    /* checks whether ch is a character between ‘0’ and ‘9’ */
    return (ch >= '0' && ch <= '9');
}

void ExtractCharacters(const char *expression, int end_index, char *return_target){
    // Iterate through the char array until index, copying each element to return_target at the same index.
    for (int i = 0; i < end_index; ++i) {
        return_target[i] = expression[i];
    }
}

int GetNum(char *expression) {
    /* returns value of next integer in expression, and integer is consumed */
    int i = 0;
    int maxString = string_length(expression);
    while (IsNum(expression[i]) && i <= maxString)
        i++;
    char number[i+1];
    memset(number, 0, (i+1)*sizeof(number[0]));
    ExtractCharacters(expression, i, number);   // Get characters and store to number
    DeleteFirstNCharacters(expression, i);      // Remove characters from expression
    int returnint = atoi(number);               // Convert to int
    return returnint;                           // Convert to int
}


void EvalExpression(char *expression, int *result) {
    /* Evaluation Logic:
     *  1.	Evaluate the next term in E, and call the result X.
     *  2.	While the next character in E is an operator (“+” or “–”)
     *      a.	Read past the operator.
     *      b.	Evaluate the next term in E, calling the result Y.
     *      c.	Let X be X + Y or X – Y, depending on the operator.
     *  3.	 The value of E is the final value of X.
     */
    // <expression> ::= <term> |<expression> + <term> | <expression> – <term>.
    int temp;
    char op;

    EvalTerm(expression, result);
    while ((NotEmpty(expression))
           && ((NextChar(expression) == '+')
               || (NextChar(expression) == '-'))) {
        op = GetNextChar(expression);
        EvalTerm(expression, &temp);
        if (op == '+')
            *result = *result + temp;
        else
            *result = *result - temp;

    }
}


void EvalTerm(char *expression, int *result) {
    // <term> ::= <factor> | <term> * <factor> | <term> / <factor>.
    int temp;
    char op;

    EvalFactor(expression, result);
    while ((NotEmpty(expression))
           && ((NextChar(expression) == '*')
               || (NextChar(expression) == '/'))) {
        op = GetNextChar(expression);
        EvalFactor(expression, &temp);
        if (op == '*')
            *result = *result * temp;
        else
            *result = *result / temp;
    }
}


void EvalFactor(char *expression, int *result) {
    // <factor> ::= <variable> | <value> | ( <expression> ).
    if (NotEmpty(expression) && (NextChar(expression) != '('))
        *result = GetNum(expression);
    else{
        GetNextChar(expression); // skip '('
        EvalExpression(expression, result);
        GetNextChar(expression); // skip ')'
    }
}


