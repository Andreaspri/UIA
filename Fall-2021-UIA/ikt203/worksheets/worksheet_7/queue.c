//
// Created by Andreas on 16.10.2021.
//
#include <stdlib.h>
#include <stdio.h>

#include "queue.h"








Queue* makeQueue()
{
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    queue->size = 0;
    queue->tail = NULL;
    queue->head = NULL;
    return queue;
}


void enQueue(Queue* queue, Tree* tree_node)
{
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->tree_node = tree_node;
    new_node->next = NULL;

    if (queue->size == 0)
    {
        queue->head = new_node;
        queue->tail = new_node;
    } else
    {
        queue->tail->next = new_node;
        queue->tail = new_node;
    }
    queue->size++;
}



Tree* deQueue(Queue* queue)
{
    Node* return_node = queue->head;
    queue->head = queue->head->next;
    Tree* tree_node = return_node->tree_node;
    free(return_node);
    queue->size--;
    return tree_node;
}