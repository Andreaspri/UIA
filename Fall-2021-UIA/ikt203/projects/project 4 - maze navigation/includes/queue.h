//
// Created by Andreas on 22.09.2021.
//

#ifndef PROJECT_4___MAZE_NAVIGATION_QUEUE_H
#define PROJECT_4___MAZE_NAVIGATION_QUEUE_H
#define MIN_QUEUE_SIZE 20
#define DIMENSIONS 2
#define INDEX_CORRECT 1
#define MAX_QUEUE_SIZE 5000

typedef struct QueuePosition {
    int x;
    int y;
} Position;


typedef struct QueueRecord {
    int capacity;
    int front;
    int rear;
    int size;
    Position *array;
} Queue;


Queue *make_empty_queue(int);
void empty_queue(Queue *);
int is_empty(Queue *);
int is_full(Queue *);
void enqueue(Queue *, int , int);
Position dequeue(Queue *);
int successor(Queue *, int );
Position inspect_front_of_queue(Queue *);
Position *inspect_rear_of_queue(Queue *);
int queue_size(Queue*);

#endif //PROJECT_4___MAZE_NAVIGATION_QUEUE_H
