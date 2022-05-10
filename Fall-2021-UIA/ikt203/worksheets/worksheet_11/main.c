#include <stdio.h>
#include <stdlib.h>
#include "extras/tree.h"



#define SIZE 10


long long bubble_sort(int* array, int size)
{
    int temp;
    long long count = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            count++;
            if (array[j] > array[j+1])
            {
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
    return count;

}


long long insert_sort(int* array,int size)
{
    int temp,j;
    long long count = 0;
    for (int i = 1; i < size; ++i)
    {
        j = i-1;
        temp = array[i];
        while (array[j] > temp && j >= 0)
        {
            array[j+1] = array[j];
            j--;
            count++;
        }
        array[j+1] = temp;
    }
    return count;
}



long long select_sort(int* array, int size)
{
    int temp;
    long long count = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = i; j < size; ++j) {
            count++;
            if (array[i] > array[j])
            {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
    return count;
}

long long merge(int* array, int start, int stop, int middle)
{
    long long count = 0;
    int size_right = stop-middle;
    int size_left = middle - start + 1;
    int left_array[size_left];
    int right_array[size_right];


    for (int i = 0; i < size_left; ++i) {
        left_array[i] = array[start+i];
    }
    for (int i = 0; i < size_right; ++i) {
        right_array[i] = array[middle+i+1];
    }


    int i = 0;
    int j = 0;
    int k = start;

    while (j < size_right && i < size_left) {
        count++;
        if (left_array[i] <= right_array[j]) {
            array[k] = left_array[i];
            i++;
        }
        else {
            array[k] = right_array[j];
            j++;
        }
        k++;
    }


    while (i < size_left) {
        count++;
        array[k] = left_array[i];
        i++;
        k++;
    }


    while (j < size_right) {
        count++;
        array[k] = right_array[j];
        j++;
        k++;
    }

    return count;
}


long long merge_sort(int* array, int start,int stop)
{
    long long count = 0;
    if (start < stop)
    {
    int middle = start+(stop-start)/2;

    count += merge_sort(array, start, middle);
    count += merge_sort(array, middle+1, stop);

    count += merge(array,start,stop,middle);
    }
    return count;
}



void tree_sort(int* array, int size)
{
    int index = 0;
    Tree* tree = MakeTreeNode(INT_MIN);

    for (int i = 0; i < size; ++i)
    {
        IterativeInsertBinarySearchTree(tree,array[i]);
    }

    iterative_tree_to_array(tree, array);

}


void tree_sort_exam(int* array, int size)
{
    int index = 0;
    Tree* tree = NULL;

    for (int i = 0; i < size; ++i)
    {
        tree = IterativeInsert(tree,array[i]);
    }

    InOrderTraversal(tree);

}

void reverse_list_exam()
{
    struct ListNode *node, *head = NULL;
    for (int i = 0; i < SIZE; ++i)
    {
        node = (struct ListNode*) malloc(sizeof (struct ListNode));
        node->val = i;
        node->next = head;
        head = node;
    }

    printf("Initial list: ");
    for (struct ListNode* current = head; current != NULL; current = current->next)
    {
        printf("%i ",current->val);
    }
    printf("\n");

    head = IterativeReverseList(head);

    printf("Reversed list: ");
    for (struct ListNode* current = head; current != NULL; current = current->next)
    {
        printf("%i ",current->val);
    }
    printf("\n");

}







int main() {

    struct TreeNode* tree = MakeTreeNode(INT_MIN);

    for (int i = 0; i < 10; ++i)
    {
        IterativeInsertBinarySearchTree(tree,i%3);
    }
    struct TreeNode* ntree = BuildNewTree(tree);

    int array[SIZE];
//    for (int i = SIZE; i > 0; --i)
//    {
//            array[SIZE-i] = rand()%SIZE;
//    }

    array[0] = 10;
    array[1] = 5;
    array[2] = 6;
    array[3] = 8;
    array[4] = 4;
    array[5] = 7;
    array[6] = 3;
    array[7] = 1;
    array[8] = 2;
    array[9] = 9;


    struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->val = -1;
    head->next = NULL;

    for (int i = 0; i < 10; ++i)
    {
        struct ListNode* current = head;
        while (current->next != NULL)
            current = current->next;
        struct ListNode* new_node = (struct ListNode*)malloc(sizeof(struct ListNode));
        new_node->val = i;
        new_node->next = NULL;
        current->next = new_node;
    }
    head = IterativeReverseList(head);
    head = RecursiveReverseList(NULL,head);



//    printf("Initial array: ");
//    for (int i = 0; i < SIZE; ++i)
//    {
//        printf("%i ",array[i]);
//    }
//    printf("\n");


    //bubble_sort(array,SIZE);
    //tree_sort(array, SIZE);
    //merge_sort(array,0,SIZE-1);
    //tree_sort_exam(array, SIZE);
    //reverse_list_exam();

//    printf("Sorted array: ");
//    for (int i = 0; i < SIZE; ++i)
//    {
//        printf("%i ",array[i]);
//    }
//    printf("\n");



    return 0;
}
