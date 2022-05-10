//
// Created by Nixxen on 23.10.2021.
//

#ifndef PROJECT_6___EXPRESSION_PARSING_AND_EVALUATION_PARSETREE_H
#define PROJECT_6___EXPRESSION_PARSING_AND_EVALUATION_PARSETREE_H

struct TreeNode
{
    bool isLeaf;
    bool isVariable;
    int number;
    TreeNode* leftTree;
    TreeNode* rightTree;
    char op;
};

typedef TreeNode* TreePtr;

bool IsLeafNode(TreePtr tree);
/* returns true if tree points to a leaf node */

void GetVariable(TreePtr tree);
/* Ask for user input and overwrite tree value with this value.
 * Should only be called on leaf nodes, never on inner nodes.*/

bool IsVariableNum(TreePtr tree);
/* returns true if tree points to a node that has a variable */

int LeafValue(TreePtr tree);
/* returns number at leaf node */

char NodeOperator(TreePtr tree);
/* returns operator at internal tree node */

TreePtr LeftTree(TreePtr tree);
/* returns left subtree of a node */

TreePtr RightTree(TreePtr tree);
/* returns right subtree of a node */

TreePtr BuildLeaf(int val, bool is_variable);
/* build a leaf node in the parse tree and return */
/* the pointer to the node */

TreePtr BuildNode(TreePtr leftTree, TreePtr rightTree, char op);
/* build an internal node in the parse tree and */
/* return the pointer to the node */

TreePtr ParseExpression(char *expression);
/* parses a given expression, returns tree pointer */

TreePtr ParseTerm(char *expression);
/* parses a given term, returns tree pointer */

TreePtr ParseFactor(char *expression);
/* parses a given factor, returns tree pointer */

double EvalExpressionTree(TreePtr exprTree);
/* Evaluates the values in an expression tree */

void PrintBinaryTreeStructure(TreePtr root, int depth);
/* Prints horizontal binary tree structure */

#endif //PROJECT_6___EXPRESSION_PARSING_AND_EVALUATION_PARSETREE_H
