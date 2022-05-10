#ifndef STATIC_QUEUE_LIBRARY_H
#define STATIC_QUEUE_LIBRARY_H
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
bool is_empty(Queue *);
bool is_full(Queue *);
void enqueue(Queue *, int , int);
Position *dequeue(Queue *);
int successor(Queue *, int );
Position* inspect_front_of_queue(Queue *);
Position* inspect_rear_of_queue(Queue *);
void display_queue(Queue*);
int queue_size(Queue*);

#endif //STATIC_QUEUE_LIBRARY_H
