#ifndef PROJECT_4___MAZE_NAVIGATION_QUEUE_WAVE_FRONT_H
#define PROJECT_4___MAZE_NAVIGATION_QUEUE_WAVE_FRONT_H
#include <queue.h>

class Current_queue
{
    // Access Specifier
    Queue *queue_struct;
    public:
        // Empty constructor
        Current_queue(int size) {
            queue_struct = (Queue *)make_empty_queue(size);
        }

        void empty_current_queue(){
            empty_queue(queue_struct);
        }

        bool empty(){
            return is_empty(queue_struct);
        }

        bool full(){
            return is_full(queue_struct);
        }

        void add_to_queue(int x, int y){
            enqueue(queue_struct, x, y);
        }

        Position remove_first_element_from_queue(){
            return dequeue(queue_struct);
        }

        Position front_of_queue(){
            return inspect_front_of_queue(queue_struct);
        }

        Position rear_of_queue(){
            return *inspect_rear_of_queue(queue_struct);
        }

        int size_of_queue(){
            return queue_size(queue_struct);
        }
};

#endif //PROJECT_4___MAZE_NAVIGATION_QUEUE_WAVE_FRONT_H
