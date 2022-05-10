#include "queue.h"
#include <iostream>


void empty_queue(Queue *queue){
    queue->rear = 0;
    queue->size = 0;
    queue->front = 1;
}

// Checks if empty.
int is_empty(Queue *queue){
    return !queue->size;
}

// Checks if full.
int is_full(Queue *queue){
    return queue->size == queue->capacity;
}


int successor(Queue *queue, int value){
    value++;
    if (value == queue->capacity){
        value = 0;
    }
    return value;
}

// Queue up another node.
void enqueue(Queue *queue, int x, int y){
    if (is_full(queue))
        printf("The queue is full!");
    else{
        queue->rear = successor(queue, queue->rear);
        queue->array[queue->rear].x = x;
        queue->array[queue->rear].y = y;
        queue->size++;
    }
}

// Dequeue a node in the queue.
Position dequeue(Queue *queue){
    int index;
    if (is_empty(queue)){
        printf("ERROR - Attempting to dequeue from empty queue!\n");
        Position old_position;
        old_position.x = INT_MIN;
        old_position.y = INT_MIN;
        return old_position;
    }
    else{
        index = queue->front;
        queue->front = successor(queue, index);
        // Changing the size of the queue.
        queue->size--;
        // Making a new Position struct to store the old position.
        Position old_position;
        old_position.x = queue->array[index].x;
        old_position.y = queue->array[index].y;
        return old_position;
    }
}



// Make a new empty queue.
Queue *make_empty_queue(int size){
    if (size < MIN_QUEUE_SIZE){
        printf("Size is to small for this static queue.");
        return nullptr;
    }

    else if (size > MAX_QUEUE_SIZE){
        printf("Size is to big for this static queue.");
        return nullptr;
    }

    Queue *queue = (Queue *)malloc(sizeof(Queue));

    if (queue == nullptr){
        printf("Out of memory!");
        return nullptr;
    }

    queue->array = (Position *)malloc(size*sizeof(Position));
    if (queue->array == nullptr){
        printf("Out of memory!");
        return nullptr;
    }

    queue->capacity = size;
    empty_queue(queue);

    return queue;
}


// Returns the front of the queue, without removing the value.
Position inspect_front_of_queue(Queue *queue)
{
    if(is_empty(queue))
    {
        printf("The queue is empty!");
        Position position;
        position.y = INT_MIN;
        position.x = INT_MIN;
        return position;
    }
    else
    {
        return queue->array[queue->front];
    }
}

// Returns the rear of the queue, without removing the value.
Position* inspect_rear_of_queue(Queue* queue)
{
    if(is_empty(queue))
    {
        printf("The queue is empty!");
        Position* position;
        position->y = INT_MIN;
        position->x = INT_MIN;
        return position;
    }
    else
    {
        return queue->array+queue->rear;
    }
}

// Returns the size of the queue.
int queue_size(Queue* queue)
{
    if(is_empty(queue))
    {
        printf("The queue is empty!");
        return 0;
    }
    else
    {
        return queue->size;
    }
}
