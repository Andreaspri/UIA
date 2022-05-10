#include <cstdio>
#include <cstdlib>
#include <string>
#include <stdexcept>

#ifndef PROJECT_5_AIR_TRAFFIC_CONTROLLER_QUEUE_H
#define PROJECT_5_AIR_TRAFFIC_CONTROLLER_QUEUE_H

#define MAX_QUEUE_SIZE 100

#include "aircraft.h"
#include <vector>

typedef struct node {
    double priority;       // Handled by external class
    void *data;         // Aircrafts, yay!
    int next;
} Node;


typedef struct queue_t {
    int front;
    int tail;
    int size;
    int capacity;
    Node nodeList[MAX_QUEUE_SIZE];
} Queue_struct;


Queue_struct *create_queue();

void make_empty_queue(Queue_struct *queue);

int is_queue_full(Queue_struct *queue);

int is_queue_empty(Queue_struct *);

int queue_size(Queue_struct *queue);

void dequeue(Queue_struct *queue);

void enqueue(Queue_struct *queue, void *data, double priority);

void sorted_enqueue(Queue_struct*, void *, double);

int partition(void *, int, int);

void sort_queue(Queue_struct *queue, int, int);

void swap(int *, int *);

void* peak_top(Queue_struct *);

Node* get_head(Queue_struct *);

void* get_aircraft_index(Queue_struct *, int);

Node* get_node_index(Queue_struct *, int);

void sort_queue(Queue_struct *);

void move_aircrafts_(Queue_struct*);

void new_sort(Queue_struct *);

void sorted_insert(Queue_struct *, void *, double);

Node* get_all_position(Queue_struct *);

class Queue
{
    Queue_struct* queue = create_queue();

public:

    Queue()= default;

    auto peak()
    {
        return *(Aircraft*)peak_top(queue);
    }

    void enQueue(Aircraft* aircraft)
    {
        sorted_insert(queue, aircraft, aircraft->calculate_priority());
    }

    void deQueue()
    {
        ((Aircraft*)queue->nodeList[queue->front].data)->free_aircraft();
        delete (Aircraft*)queue->nodeList[queue->front].data;

        dequeue(queue);
    }

    int size()
    {
        return queue_size(queue);
    }

    int head()
    {
        return queue->front;
    }

    Position get_aircraft_position_by_index(int index) const {
        return ((Aircraft*)get_aircraft_index(queue,index))->get_position();
    }

    void move_aircraft_by_index(int index)
    {
        ((Aircraft*)get_aircraft_index(queue,index))->move();
    }

    void apply_changes_to_aircrafts_by_index(int index)
    {
        ((Aircraft*)get_aircraft_index(queue,index))->apply_random_changes();
    }

    void calculate_priority_by_index(int index)
    {
       get_node_index(queue,index)->priority = ((Aircraft*) get_aircraft_index(queue,index))->calculate_priority();
    }

    void sort()
    {
        new_sort(queue);
    }

    int is_empty()
    {
        return is_queue_empty(queue);
    }

    int check_if_node_is_outside()
    {
        return queue->nodeList[queue->front].priority <=0;
    }

    void apply_changes_to_aircrafts()
    {
        if (!is_queue_empty(queue))
            move_aircrafts_(queue);
    }

    Node* get_all_positions()
    {
        return get_all_position(queue);
    }

    int tail()
    {
        return queue->tail;
    }



};


#endif //PROJECT_5_AIR_TRAFFIC_CONTROLLER_QUEUE_H
