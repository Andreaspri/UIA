//
// Created by Nixxen on 23.10.2021.
//

#ifndef PROJECT_6___EXPRESSION_PARSING_AND_EVALUATION_LAAE_H
#define PROJECT_6___EXPRESSION_PARSING_AND_EVALUATION_LAAE_H

/*
 * Lexical Analysis of Arithmetic Expressions
 * Here, we only concern ourselves with the lexical analysis of arithmetic expressions.
 * We will need a few auxiliary functions for the lexical analysis of expressions as follows:
*/

bool NotEmpty(const char *expression);
/* returns true if expression is not empty string*/

void DeleteFirstNCharacters(char *expression, int startIndex);
/* Iterate through the char array and move each char one to the left (other than the first)*/

void ExtractCharacters(const char *expression, int end_index, char *return_target);
/* Iterate through the char array until index, copying each element to return_target at the same index */

char NextChar(const char *expression);
/* returns next character in expression, but nothing is consumed */

char GetNextChar(char *expression);
/* returns next character in expression, but a character is consumed */

bool IsNum(char ch);
/* checks whether ch is a character between ‘0’ and ‘9’ */

int GetNum(char *expression);
/* returns value of next integer in expression, and integer is consumed */

void EvalExpression(char *expression, int *result);
/* evaluates a given expression */

void EvalTerm(char *expression, int *result);
/* evaluates a given term */

void EvalFactor(char *expression, int *result);
/* evaluates a given factor */


#endif //PROJECT_6___EXPRESSION_PARSING_AND_EVALUATION_LAAE_H
