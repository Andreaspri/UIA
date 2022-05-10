//
// Created by Andreas on 28.09.2021.
//

#include <cstring>
#include <list>
#include <vector>
#include "queue.h"


Queue_struct *create_queue() {
    // Allocate the new queue
    auto *queue = (Queue_struct *) malloc(sizeof(Queue_struct));

    if (queue == nullptr) {
        printf("Error! No memory left.\n");
        return nullptr;
    }

    queue->capacity = MAX_QUEUE_SIZE;

    make_empty_queue(queue);
    return queue;
}

void make_empty_queue(Queue_struct *queue) {
    // TODO: Create dummy node?
    queue->size = 0;
    queue->front = 0;
    queue->tail = -1;

    // Set nodelist.next for each segment of the length.
    for (int i = 1, p = 0; p < queue->capacity; i++, p++) {
        queue->nodeList[p].next = i;
    }
    queue->nodeList[queue->capacity - 1].next = 0;
}

int is_queue_empty(Queue_struct *queue) {
    return queue->size == 0;
}

int is_queue_full(Queue_struct *queue) {
    return queue->size == queue->capacity;
}


int queue_size(Queue_struct *queue) {
    return queue->size;
}







void dequeue(Queue_struct *queue) {
    if (!is_queue_empty(queue)) {
        // Dequeue element from queue
        // Ensure front never crosses array bounds
        queue->front = queue->nodeList[queue->front].next;
        // Decrease queue size
        queue->size--;
    } else {
        printf("Error. Attempting to dequeue an empty queue!\n");
    }
}



void enqueue(Queue_struct *queue, void *data, double priority) {
    if (!is_queue_full(queue)) {
        printf("Queue size is now: %i\n", queue_size(queue));
        // No sorting yet. Just get it in there.
        // tail.next. Set priority and data
        queue->nodeList[queue->nodeList[queue->tail].next].priority = priority;
        queue->nodeList[queue->nodeList[queue->tail].next].data = data;
        // Update queue tail to the tail.next
        queue->tail = queue->nodeList[queue->tail].next;
        queue->size++;
        // TODO: Resort list on inserts function
    } else
        //printf("Queue_struct is full!\n");
        NULL;
}

// TODO: Sort list function

void* peak_top(Queue_struct *queue)
{
    if (!is_queue_empty(queue))
        return queue->nodeList[queue->front].data;
    else
    {
        printf("Trying to peak at empty queue!\n");
        // TODO: FIX THIS LATER: Need to return something... Add checks to the class
    }
}

Node* get_head(Queue_struct *queue)
{
    return &queue->nodeList[queue->front];
}

void* get_aircraft_index(Queue_struct* queue, int index)
{
    Node* node = get_head(queue);
    int i;
    for (i = 0; i < index; i++) {
        node = &queue->nodeList[node->next];
    }
    return node->data;
}

Node* get_node_index(Queue_struct* queue, int index)
{
    Node* node = get_head(queue);
    int i;
    for (i = 0; i < index; i++) {
        node = &queue->nodeList[node->next];
    }
    return node;
}


Node* get_all_position(Queue_struct* queue)
{


    return queue->nodeList;
}





 // Replaced this code with something of my own. Pretty much the same, but mine works ;)
/*
// Inserts into queue and correct priority location. Assumes queue is already sorted.
void sorted_enqueue(Queue_struct* queue, void *data, double priority){
    // FIXME: Må finne en måte å hente ut "lost nodes" som skal peke til ny front, når front endres.
    if (!is_queue_full(queue)){
        // Add data and priority to end of queue as a temporary node, from now called new_node.
        int new_node = queue->nodeList[queue->tail].next;
        queue->nodeList[new_node].priority = priority;
        queue->nodeList[new_node].data = data;

        // Locate position in queue such that queue->nodelist->priority > priority.
        int temp_node = queue->front;

        int i;
        // Redirect temp_node to the next node in queue, as long as our priority is greater than current priority.
        for (i = 0; i < queue_size(queue) && priority > queue->nodeList[temp_node].priority; ++i) {
            temp_node = queue->nodeList[temp_node].next;
        }

        if (queue_size(queue) == 0){
            // List was empty, set front and tail to new_node
            queue->front = new_node;
            queue->tail = new_node;
        }
        // -1 because we only increment UNTIL queue_size, not TO queue_size.
        else if (i == queue_size(queue)){
            // New node is the biggest in the list. Must update tail.
            queue->tail = new_node;
        }
        else if (i == 0){
            // New node is lower priority than the front node. Replace front.

            // Temporary store the new next, and add it to the tail later.
            int temp_tail = queue->nodeList[new_node].next;

            // Push insert into the list, and make the queue->front push back.
            // Set new_node next to front.
            queue->nodeList[new_node].next = queue->front;

            // Correct the next of the tail
            queue->nodeList[queue->tail].next = temp_tail;

            // Set the front to the new node
            queue->front = new_node;
        }
        else{
            // List has a node already, and new node is not the "biggest". Do some magic.

            // Temporary store the new next, and add it to the tail later.
            int temp_tail = queue->nodeList[new_node].next;

            // Push insert into the list, and make the temp node push front.
            // Set new_node next to temp next
            queue->nodeList[new_node].next = queue->nodeList[temp_node].next;
            // set temp next to new_node (old tail.next).
            queue->nodeList[temp_node].next = new_node;

            // Correct the next of the tail
            queue->nodeList[queue->tail].next = temp_tail;
        }

        // Increment size
        queue->size++;
    }
    else{
        printf("Error. Attempting to insert into full queue.\n");
    }

}
*/



void move_aircrafts_(Queue_struct* queue)
{
    for (int i = queue->front,p=0; p < queue_size(queue); i = queue->nodeList[i].next,p++)
    {
        ((Aircraft*)queue->nodeList[i].data)->move();
        // TODO: Remove changed aircraft and insert it at correct priority instead of later sorting it.
        //  Drastically reduce the chance of the airplane to "mutate"
        ((Aircraft*)queue->nodeList[i].data)->apply_random_changes();
        // TODO: Only do this IF the aircraft changed direction
        queue->nodeList[i].priority = ((Aircraft*)queue->nodeList[i].data)->calculate_priority();
    }
}






void sorted_insert(Queue_struct* queue, void* data, double priority)
{
    if (!is_queue_full(queue))
    {
        // Placing the new node at the end of the array
        int new_node = queue->nodeList[queue->tail].next;
        queue->nodeList[new_node].priority = priority;
        queue->nodeList[new_node].data = data;
        queue->size++;
        if (queue->size == 1)
        {
            queue->tail = new_node;
            return;
        }


        int next_node = queue->front;
        int previous_node = queue->front;
        for (int i = 0; i < queue->size; ++i)
        {
            if(queue->nodeList[new_node].priority < queue->nodeList[next_node].priority)
            {
                break;
            }
            previous_node = next_node;
            next_node = queue->nodeList[next_node].next;
        }

        // This means that the node should be inserted at the front
        if (next_node == previous_node)
        {
            // Getting the node pointing at the front, but only if the list isn't full. If that is the case, the tail points to the front
            if (queue->size != queue->capacity)
            {
                for (int i = queue->tail; queue->nodeList[i].next != queue->front; i = queue->nodeList[i].next)
                {
                    previous_node = queue->nodeList[i].next;
                }
            }
            else
                previous_node = queue->tail;

            // Last node needs to be pointing over the new node
            queue->nodeList[queue->tail].next = queue->nodeList[queue->nodeList[queue->tail].next].next;
            // Making the node previously pointing at the front to point at the new front;
            queue->nodeList[previous_node].next = new_node;
            // The new node should be pointing at the old front
            queue->nodeList[new_node].next = next_node;
            // Setting the front to the new node
            queue->front = new_node;
            return;
        }
        else if (previous_node == queue->nodeList[queue->tail].next)
        {
            queue->tail = new_node;
            return;
        }
        else
        {
            // Last node needs to be pointing over the new node
            queue->nodeList[queue->tail].next = queue->nodeList[queue->nodeList[queue->tail].next].next;

            queue->nodeList[previous_node].next = new_node;

            queue->nodeList[new_node].next = next_node;
            return;

        }
    }
}











void new_sort(Queue_struct* queue)
{
    // No need to sort if the queue size is 0 or 1
    if (queue->size == 0 || queue->size == 1)
        return;

    int index;
    int current_lowest;
    int node_that_the_tail_is_pointing_at;
    int cursor = queue->front;
    int node_pointing_to_front;
    double current_priority;

    // The sorted array will store the nodes in the correct order
    int sorted_arr[queue->size];

    // This vector is going to store nodes that are currently not assigned a position yet.
    // They will be moved out of the container_list and into the sorted array once their position is decided
    std::vector<int> container_list;
    for (int i = 0; i < queue->size; ++i) {
        container_list.push_back(cursor);
        cursor = queue->nodeList[cursor].next;
    }


    // Getting the node pointing to the front if the tail isn't pointing to it
    if (queue->size != queue->capacity)
    {
        for (int i = queue->tail; queue->nodeList[i].next != queue->front; i = queue->nodeList[i].next)
        {
            node_pointing_to_front = queue->nodeList[i].next;
        }
    }

    // Standard bubble sort
    for (int i = 0; i < queue->size; ++i) {
        index = 0;
        cursor = container_list[0];
        current_priority = queue->nodeList[cursor].priority;
        current_lowest = cursor;
        for (int j = 0; j < container_list.size(); ++j) {
            if (queue->nodeList[cursor].priority < current_priority)
            {
                current_priority = queue->nodeList[cursor].priority;
                current_lowest = cursor;
                index = j;
            }
            // It needs to be j+1 because we need the next node. The current node is just j
            // We can't just start j at 1 because that would make the index go out of bounds+
            cursor = container_list[1+j];
        }
        // Popping out nodes that are given a position in the sorted_arr
        container_list.erase(container_list.begin()+index);
        // Giving the node with the current highest priority (lowest number) the correct position in the sorted_arr
        sorted_arr[i] = current_lowest;
    }

    // Different cases for a full and not full queue
    if (queue->size == queue->capacity)
    {
        // Connecting the sorted_arr
        for (int i = 0; i < queue->capacity-1; ++i) {
            queue->nodeList[sorted_arr[i]].next = sorted_arr[i+1];
        }
        // The array is at max size, so the last item in the sorted_arr should be pointing at the first to make it circular
        queue->nodeList[sorted_arr[queue->capacity-1]].next = sorted_arr[0];
        // Tail is the end of the sorted_arr
        queue->tail = sorted_arr[queue->capacity-1];
        // Front is the beginning of the sorted_arr
        queue->front = sorted_arr[0];
    }
    else
    {
        // Getting the node that the tail is pointing at before soring so that the last item in the sorted_arr can point at it
        node_that_the_tail_is_pointing_at = queue->nodeList[queue->tail].next;
        // Connecting the sorted_arr
        for (int i = 0; i < queue->size-1; ++i) {
            queue->nodeList[sorted_arr[i]].next = sorted_arr[i+1];
        }
        // Making the last item in sorted_arr point at whatever the tail was pointing at before
        queue->nodeList[sorted_arr[queue->size-1]].next = node_that_the_tail_is_pointing_at;
        // Setting the node that previous pointed at front to point at the potential new front
        queue->nodeList[node_pointing_to_front].next = sorted_arr[0];
        // Tail is the end of the sorted_arr
        queue->tail = sorted_arr[queue->size-1];
        // Front is the beginning of the sorted_arr
        queue->front = sorted_arr[0];
    }
}





























// SHITTY CODE AHEAD. YOU ARE WARNED


// Error handling is not working...
void error_handling(Queue_struct* queue,int fucked_up_node)
{
    int flag = true;
    int next;int error_array[queue->capacity];
    while (flag) {

        memset(error_array, -1, queue->capacity);

        for (int i = 0; i < queue->capacity; ++i) {
            error_array[queue->nodeList[i].next] = queue->nodeList[i].next;
        }


        next = queue->front;
        for (int i = 0; i < queue_size(queue); i++) {
            if (queue->nodeList[next].next == next) {
                fucked_up_node = next;
                flag = true;
                break;

            }
            flag = false;
            next = queue->nodeList[next].next;
        }


        if (flag){
            for (int i = 0; i < queue->capacity; ++i) {
                if (error_array[i] != i) {
                    queue->nodeList[fucked_up_node].next = i;
                    break;
                }
            }
        }
    }
}

// Bubble sort implementation of queue sort
void sort_queue(Queue_struct *queue)
{
    int fucked_up_node;
    int prev_node_placeholder;
    int next_node_placeholder;
    Node current_node;
    int iterator_inner;
    int iterator_outer;
    double current_priority;
    Node* node_pointing_to_the_first_element;
    bool flag = false;
    Node* prev_node;
    int index;




    for (iterator_outer = 0; iterator_outer < queue_size(queue); iterator_outer++) {
        current_node = *get_node_index(queue,iterator_outer);
        current_priority = current_node.priority;
        next_node_placeholder = current_node.next;
        prev_node_placeholder = 0;
        for (iterator_inner=iterator_outer; iterator_inner < queue_size(queue); iterator_inner++) {
            current_node = *get_node_index(queue,iterator_inner);
            if (current_node.priority < current_priority) {
                prev_node = get_node_index(queue,iterator_inner-1);
                prev_node_placeholder = prev_node->next;
                current_priority = current_node.priority;
                next_node_placeholder = current_node.next;
                index = iterator_inner;

                flag = true;
            }

        }


        fucked_up_node = -1;
        if(flag)
        {

            Node* first_node = get_node_index(queue,iterator_outer);
            for (int k = queue->front, iterator = 0;
                 iterator < queue->capacity; k = queue->nodeList[k].next, iterator++)
            {
                if (queue->nodeList[queue->nodeList[queue->nodeList[k].next].next].next == first_node->next)
                {
                    node_pointing_to_the_first_element = &queue->nodeList[queue->nodeList[k].next];
                    break;
                }
            }

            if (iterator_outer != 0 && first_node->next != prev_node_placeholder)
            {

                int old_node_temp = first_node->next;
                int prev_node_temp = prev_node->next;
                // This is working do not touch
                Node* node_pointing_to_first_node = get_node_index(queue,iterator_outer-1);

                if (prev_node_placeholder == queue->tail)
                    queue->tail = node_pointing_to_the_first_element->next;

                int o_nn = queue->nodeList[node_pointing_to_first_node->next].next; // node_pointing_to_first_node next next
                queue->nodeList[node_pointing_to_first_node->next].next = next_node_placeholder;
                prev_node->next = node_pointing_to_first_node->next;
                node_pointing_to_first_node->next = prev_node_placeholder;
                queue->nodeList[prev_node_placeholder].next = o_nn;
                flag = false;

                // FIRST
                int next;
                next = queue->front;
                for (int i = 0; i < queue_size(queue); i++)
                {
                    if (queue->nodeList[next].next == next)
                    {
                        fucked_up_node = next;
                        break;
                    }
                    next = queue->nodeList[next].next;
                }
                if (fucked_up_node != -1)
                    error_handling(queue, fucked_up_node);

            }
            else
            {



                if (first_node->next == prev_node_placeholder && iterator_outer == 0)
                {



                    // This is not working

                    if (prev_node_placeholder == queue->tail)
                        queue->tail = node_pointing_to_the_first_element->next;

                    queue->nodeList[queue->front].next = next_node_placeholder;
                    queue->nodeList[prev_node_placeholder].next = queue->front;
                    queue->front = prev_node_placeholder;
                    node_pointing_to_the_first_element->next = prev_node_placeholder;
                    flag = false;

                    // SECOND
                    int next;
                    next = queue->front;
                    for (int i = 0; i < queue_size(queue); i++)
                    {
                        if (queue->nodeList[next].next == next)
                        {
                            fucked_up_node = next;
                            break;
                        }
                        next = queue->nodeList[next].next;
                    }
                    if (fucked_up_node != -1)
                        error_handling(queue, fucked_up_node);
                }
                else if (first_node->next == prev_node_placeholder && iterator_outer != 0)
                {


                    // This is working do not touch

                    int node_pointing_to_the_first_element_temp = node_pointing_to_the_first_element->next;
                    int prev_node_temp = prev_node->next;

                    if (prev_node_placeholder == queue->tail)
                        queue->tail = node_pointing_to_the_first_element->next;

                    int temp = node_pointing_to_the_first_element->next;
                    node_pointing_to_the_first_element->next = prev_node_placeholder; // Here old node is the node before the current node
                    queue->nodeList[prev_node_placeholder].next = temp;
                    prev_node->next = next_node_placeholder;
                    flag = false;


                    // THIRD
                    int next;
                    next = queue->front;
                    for (int i = 0; i < queue_size(queue); i++)
                    {
                        if (queue->nodeList[next].next == next)
                        {
                            fucked_up_node = next;
                            break;
                        }
                        next = queue->nodeList[next].next;
                    }
                    if (fucked_up_node != -1)
                        error_handling(queue, fucked_up_node);
                }
                else if (iterator_outer == 0)
                {
                    // This is working do not touch
                    Node* node_pointing_to_current_node = get_node_index(queue,index-1);

                    if (prev_node_placeholder == queue->tail)
                        queue->tail = node_pointing_to_the_first_element->next;

                    if (queue->front == queue->tail && queue_size(queue) == queue->capacity)
                    {
                        queue->nodeList[prev_node_placeholder].next = queue->nodeList[queue->front].next;
                        queue->nodeList[queue->front].next = prev_node_placeholder;
                        node_pointing_to_current_node->next = next_node_placeholder;
                        queue->front = prev_node_placeholder;


                        // FOURTH
                        int next;
                        next = queue->front;
                        for (int i = 0; i < queue_size(queue); i++)
                        {
                            if (queue->nodeList[next].next == next)
                            {
                                fucked_up_node = next;
                                break;
                            }
                            next = queue->nodeList[next].next;
                        }
                        if (fucked_up_node != -1)
                            error_handling(queue, fucked_up_node);


                    }
                    else
                    {
                        node_pointing_to_current_node->next = queue->front;
                        int temp = queue->nodeList[queue->front].next;
                        queue->nodeList[queue->front].next = next_node_placeholder;
                        queue->nodeList[prev_node_placeholder].next = temp;
                        queue->front = prev_node_placeholder;
                        node_pointing_to_the_first_element->next = prev_node_placeholder;
                        flag = false;


                        // FIFTH
                        int next;
                        next = queue->front;
                        for (int i = 0; i < queue_size(queue); i++)
                        {
                            if (queue->nodeList[next].next == next)
                            {
                                fucked_up_node = next;
                                break;
                            }
                            next = queue->nodeList[next].next;
                        }
                        if (fucked_up_node != -1)
                            error_handling(queue, fucked_up_node);
                    }
                }
            }
        }
    }
}








/*
void swap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(void *data, int low, int high){
    // TODO: void pointer fix.
    // This will get the last element in the queue.
    int pivot = data[high];
    // Starting at index -1.
    int i = low-1;

    for (int j = low; j <= high; j++){
        if (data[j] < pivot){
            i++;
            // We don't know the datatype so this is not possible.
            swap(data+i, data+high);

        }
    }

    // Swap the pivot with the last element that has higher priority.
    // Hence, there is only lower priority objects in front of the  pivot, and larger after.
    swap(data+(i+1), data+high);

    // Returns the pivot index.
    return i+1;
}


void sort_queue(Queue_struct *queue, int low, int high){

    if (low < high){
        // Partition index.
        int pi = partition(queue->data, low, high);

        // Going from left to right in the array and sorting.
        sort_queue(queue, low, pi-1);
        sort_queue(queue, pi+1, high);
    }

}


*/




// TODO: Make sorting go brrrr
/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot *//*

void partition(Queue_struct queue, int low, int high) {
    // pivot (Element to be placed at right position)
    int pivot = arr[high];

    int i = (low - 1)  // Index of smaller element and indicates the
    // right position of pivot found so far

    for (int j = low; j <= high - 1; j++) {
    // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++;    // increment index of smaller element
            swap
            arr[i] and arr[j]
        }
    }
    swap
    arr[i + 1]
    and arr[high])
    return (i + 1)
}


*/
/* low  --> Starting index,  high  --> Ending index *//*

void quickSort(Queue_struct queue, int low, int high) {
    if (low < high) {
        */
/* pi is partitioning index, queue[pi] is now at right place *//*

        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);  // Before pi
        quickSort(arr, pi + 1, high); // After pi
    }
}
*/





/*


// Swap two queue elements order
void swap_nodes(Node *x, Node *y)
{
    int temp;

    temp = x->next;
    x->next = y->next;
    y->next = temp;
}

// Quick sort implementation of sort queue
void QuickSort(int low, int high, Queue_struct * queue)
{
    // Initialize variables
    int i = low, j = high;
    double z;

    // FIXME: This does not work for a linked list. Can not find the pivot this way.
    // Set the z middle point
    int split = (low + high) / 2;
    z=queue->nodeList[split].priority;

    // Do while is messy. But should work.
    do
    {
        // Increment i until it is greater than z
        while (queue->nodeList[i].priority < z){
            i = queue->nodeList[i].next;

        }

        // Decrement j until is it lower than z
        while (queue->nodeList[j].priority > z) {
            // Fuck me... We have no previous... Need to iterate from low to high -1, or implement prev.
            Node temporary_workaround = queue->nodeList[i];
            Node previous_node = temporary_workaround;
            while (temporary_workaround.next != z){
                previous_node = temporary_workaround;
                temporary_workaround = queue->nodeList[temporary_workaround.next];
            }
            j = queue->nodeList[previous_node.next].next;
        }

        // Swap nodes if i.pri < j pri
        if (queue->nodeList[i].priority <= queue->nodeList[j].priority)
        {
            swap_nodes(&queue->nodeList[i], &queue->nodeList[j]);
            // Increment i
            i = queue->nodeList[i].next;
            // Decrement j
            Node temporary_workaround = queue->nodeList[i];
            Node previous_node = temporary_workaround;
            while (temporary_workaround.next != z){
                previous_node = temporary_workaround;
                temporary_workaround = queue->nodeList[temporary_workaround.next];
            }
            j = queue->nodeList[previous_node.next].next;
        }
    } while (queue->nodeList[i].priority <= queue->nodeList[j].priority);

    // Recursively call sorts for lower part
    if (low < queue->nodeList[j].priority)
        QuickSort(low, j, queue);

    // Recursively call sorts for higher part
    if (queue->nodeList[i].priority < high)
        QuickSort(i, high, queue);
}


*/









