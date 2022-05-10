//
// Created by Andreas on 31.10.2021.
//

#ifndef WORKSHEET_11_TREE_H
#define WORKSHEET_11_TREE_H



typedef struct TreeNode Tree;
typedef struct QueueNode Node;
typedef struct Queue_ Queue;
typedef struct Stack_ Stack;

struct Stack_
{
    int size;
    Node* head;
};

struct ListNode
{
    int val;
    struct ListNode *next;
};

void InOrderTraversal(Tree *t);
Tree* IterativeInsert(Tree* t, int val);
struct ListNode* IterativeReverseList(struct ListNode* p);
struct ListNode* RecursiveReverseList(struct ListNode* previous, struct ListNode* current);

struct QueueNode
{
    Tree* tree_node;
    Node* next;
};


struct Queue_
{
    int size;
    Node* head;
    Node* tail;
};


struct TreeNode
{
    int val;
    Tree* left;
    Tree* right;
};

void IterativeInsertBinarySearchTree(Tree* tree, int val);
void RecursiveInsertBinarySearchTree(Tree* tree, int val);
Tree* MakeTreeNode(int val);
void recursive_tree_to_array(Tree* tree, int* array, int* index);
void iterative_tree_to_array(Tree* tree, int* array);
struct TreeNode *BuildNewTree(struct TreeNode *t);

#endif //WORKSHEET_11_TREE_H
