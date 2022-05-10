#include <iostream>
#include <cmath>
#include "laae.h"
#include "parsetree.h"
#include "myString.h"

int main() {
    // Lower precedence should be towards the top. Need to implement the parsing recursively.

    //char expression[] = "1+(20+4/2)";
    printf("Enter a valid string input and press enter.\n");
    char *expression = create_string();
    printf("Input expression is: %s\n", expression);
    double result = 0;
    double *result_ptr = &result;
    TreePtr exprTree;
    exprTree = ParseExpression(expression);
    printf("The tree structure before parsing:\n");
    PrintBinaryTreeStructure(exprTree,0);
    result = EvalExpressionTree(exprTree);
    // Print result with two digits
    printf("The result is: %.2f\n", result);
    printf("The tree structure after parsing:\n");
    PrintBinaryTreeStructure(exprTree,0);
    return 0;
}
// Example of a valid input: 1+(20+4/2)
// Example of a valid input: a-c*(b-10)+5*(d/7)+e/(f+20)
// Example of a valid input: 1+2*3-(4/5)

/*
 * Deliverables

Your program will have the following functionality:

1.	Read the expression from left to right and check whether it is syntactically correct arithmetic expression.
    You will use a recursive descent approach (more on this during the tutorials).
2.	Build a parse tree for the expression. This parse tree will be a binary tree where nodes either hold values or operators.
3.	Prompt the user for providing values for variables.
4.	Evaluate the expression by traversing the tree (in which order do you have to traverse this tree?)
5.	Print the parse tree.
6.	Print the structure of the parse tree.
*/

/*
 * Arithmetic expression formal grammar:
<expression> ::= <term> |<expression> + <term> | <expression> – <term>.
<term> ::= <factor> | <term> * <factor> | <term> / <factor>.
<factor> ::= <variable> | <value> | ( <expression> ).
<value> ::= <variable> | <integer>.

 ^ Means, reduce using recursive calls until we are left with only one variable integer.
 */

/*
 * Aspect	Marks (Total 100)
Getting the next symbol                             10
Parsing expressions                             	10
Parsing terms	                                    10
Parsing factors	                                    10
Implementation of access routines for parse tree	20
Evaluation of the expression tree                  	20
Displaying the parse tree as a tree                	20

Extra Marks
Implementation of a threaded binary expression tree	20
*/
