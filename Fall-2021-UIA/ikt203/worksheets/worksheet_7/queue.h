//
// Created by Andreas on 16.10.2021.
//

#ifndef WORKSHEET_7_QUEUE_H
#define WORKSHEET_7_QUEUE_H



typedef struct TreeNode Tree;
typedef struct QueueNode Node;
typedef struct Queue_ Queue;

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



Tree* deQueue(Queue* queue);
void enQueue(Queue* queue, Tree* tree_node);
Queue* makeQueue();

#endif //WORKSHEET_7_QUEUE_H
