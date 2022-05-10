//
// Created by Nixxen on 23.10.2021.
//

#include <cstdio>
#include <laae.h>
#include <cstdlib>
#include <stdexcept>
#include "parsetree.h"
#include "myString.h"

bool IsLeafNode(TreePtr tree) {
    /* returns true if tree points to a leaf node */
    return tree->isLeaf;
}

bool IsVariableNum(TreePtr tree) {
    /* returns true if tree points to a node that has a variable */
    return tree->isVariable;
}

void GetVariable(TreePtr tree){
    /* Ask for user input and overwrite tree value with this value.
     * Should only be called on leaf nodes, never on inner nodes.*/
    printf("Input a value for variable <%c>\n",tree->number);
    char *new_number_string = create_string();
    int new_number = GetNum(new_number_string);
    free(new_number_string);
    tree->number = new_number;
    tree->isVariable = false;
}

int LeafValue(TreePtr tree) {
    /* returns number at leaf node */
    if (IsVariableNum(tree)){
        // Leaf is a variable node. Get variable input from user.
        GetVariable(tree);
    }
    return tree->number;
}

char NodeOperator(TreePtr tree) {
    /* returns operator at internal tree node */
    return tree->op;
}

TreePtr LeftTree(TreePtr tree) {
    /* returns left subtree of a node */
    return tree->leftTree;
}

TreePtr RightTree(TreePtr tree) {
    /* returns right subtree of a node */
    return tree->rightTree;
}

TreePtr BuildLeaf(int val, bool is_variable) {
    /* build a leaf node in the parse tree and return */
    /* the pointer to the node */
    // Numbers
    auto tree = (TreePtr) malloc(sizeof(struct TreeNode));
    if (tree == nullptr)
        throw std::invalid_argument("Error! Out of memory, unable to allocate memory for node.\n");
    else
    {
        if (is_variable)
            tree->isVariable = true;
        else
            tree->isVariable = false;
        tree->isLeaf = true;
        tree->number = val;
        tree->leftTree = nullptr;
        tree->rightTree = nullptr;
        tree->op = 0;
        return tree;
    }
}

TreePtr BuildNode(TreePtr leftTree, TreePtr rightTree, char op) {
    /* build an internal node in the parse tree and */
    /* return the pointer to the node */
    // +, -, *, /
    // Requires left tree, right tree, operator
    auto tree = (TreePtr) malloc(sizeof(struct TreeNode));
    if (tree == nullptr)
        throw std::invalid_argument("Error! Out of memory, unable to allocate memory for node.\n");
    else
    {
        tree->isLeaf = false;
        tree->isVariable = false;
        tree->number = INT_MIN;
        tree->leftTree = leftTree;
        tree->rightTree = rightTree;
        tree->op = op;
        return tree;
    }
}



TreePtr ParseExpression(char *expression) {
    // <expression> ::= <term> |<expression> + <term> | <expression> – <term>.
    TreePtr exprTree, tempTree;
    char op;

    exprTree = ParseTerm(expression);
    while ((NotEmpty(expression))
           && ((NextChar(expression) == '+')
               || (NextChar(expression) == '-'))) {
        op = GetNextChar(expression);
        tempTree = ParseTerm(expression);
        exprTree = BuildNode(exprTree, tempTree, op);
    }
    return exprTree;
}



TreePtr ParseTerm(char *expression) {
    // <term> ::= <factor> | <term> * <factor> | <term> / <factor>.
    TreePtr exprTree, tempTree;
    char op;

    exprTree = ParseFactor(expression);
    while ((NotEmpty(expression))
           && ((NextChar(expression) == '*')
               || (NextChar(expression) == '/'))) {
        op = GetNextChar(expression);
        tempTree = ParseFactor(expression);
        exprTree = BuildNode(exprTree, tempTree, op);
    }
    return exprTree;
}

TreePtr ParseFactor(char *expression) {
    // <factor> ::= <variable> | <value> | ( <expression> ).
    TreePtr exprTree;
    int number;
    if (NotEmpty(expression) && (NextChar(expression) != '(')){
        // Check if next is char or num
        if (IsNum(NextChar(expression))){
            number = GetNum(expression);
            exprTree = BuildLeaf(number, false);
        }
        else{
            // Squish char into int. Need bool to handle logic.
            number = GetNextChar(expression);
            exprTree = BuildLeaf(number, true);
        }
        return exprTree;
    }
    else{
        GetNextChar(expression); // skip '('
        exprTree = ParseExpression(expression);
        GetNextChar(expression); // skip ')'
        return exprTree;
    }
}

double EvalExpressionTree(TreePtr exprTree) {
    double result;

    if (IsLeafNode(exprTree))
        result = LeafValue(exprTree);
    else {
        switch (NodeOperator(exprTree)) {
            case '+':
                result = EvalExpressionTree(LeftTree(exprTree)) +
                         EvalExpressionTree(RightTree(exprTree));
                break;
            case '-':
                result = EvalExpressionTree(LeftTree(exprTree)) -
                         EvalExpressionTree(RightTree(exprTree));
                break;
            case '*':
                result = EvalExpressionTree(LeftTree(exprTree)) *
                         EvalExpressionTree(RightTree(exprTree));
                break;
            case '/':
                result = EvalExpressionTree(LeftTree(exprTree)) /
                         EvalExpressionTree(RightTree(exprTree));
                break;
            default:
                result = 0;
                fprintf(stderr, "Error in evaluating expression tree\n");
        }
    }
    return result;
}


void PrintBinaryTreeStructure(TreePtr root, int depth){
    if (root!= nullptr){
        // Print right tree first(top)
        PrintBinaryTreeStructure(root->rightTree, depth + 1);

        for (int i = 0; i < depth; i++) {
            printf("\t");
        }
        // Print root node
        if (IsLeafNode(root))
            if (IsVariableNum(root))
                printf("%c\n", root->number);
            else
                printf("%d\n", root->number);
        else{
            printf("%c", root->op);
            if (root->leftTree && root->rightTree){
                printf("{\n");
            }
            else if (root->leftTree){
                printf("v\n");
            }
            else
                printf("^\n");
        }

        // Print left tree last (bottom)
        PrintBinaryTreeStructure(root->leftTree, depth + 1);
    }
}