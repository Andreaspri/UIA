//
// Created by Andreas on 31.10.2021.
//

#include "tree.h"




#include <stdio.h>
#include <stdlib.h>



Stack* CreateStack()
{
    Stack* stack= (Stack*) malloc(sizeof (Stack));
    stack->size = 0;
    stack->head = NULL;
    return stack;
}

int EmptyStack(Stack* stack)
{
    return stack->size == 0;
}


void PushStack(Stack* stack,Tree* tree)
{
    Node* node = (Node*)malloc(sizeof (Node));
    node->tree_node = tree;
    if (stack->head)
    {
        node->next = stack->head;
        stack->head = node;
    } else
    {
        node->next = NULL;
        stack->head = node;
    }
    stack->size++;
}

Tree* PopStack(Stack* stack)
{
    if (EmptyStack(stack))
    {
        printf("Stack is empty");
        return NULL;
    }
    Node* node = stack->head;
    if (stack->size == 1)
        stack->head = NULL;
    else
        stack->head = stack->head->next;
    Tree* tree = node->tree_node;
    free(node);
    stack->size--;
    return tree;
}




Queue* makeQueue()
{
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    queue->size = 0;
    queue->tail = NULL;
    queue->head = NULL;
    return queue;
}



void enQueueFront(Queue* queue, Tree* tree_node)
{
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->tree_node = tree_node;


    if (queue->size == 0)
    {
        queue->head = new_node;
        queue->tail = new_node;
        new_node->next = NULL;
    } else
    {
        new_node->next = queue->head;
        queue->head = new_node;
    }
    queue->size++;
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






Tree* MakeTreeNode(int val)
{
    struct TreeNode* new_tree = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (new_tree == NULL)
        printf("Out of memory...");
    new_tree->left = NULL;
    new_tree->right = NULL;
    new_tree->val = val;
    return new_tree;
}



void RecursiveInsertBinarySearchTree(Tree* tree, int val)
{
    if (tree->val == INT_MIN)
    {
        tree->val = val;
        return;
    }
    else
    {
        if (val < tree->val)
        {
            if (tree->left == NULL)
            {
                Tree* new_node = MakeTreeNode(val);
                tree->left = new_node;
            }
            else
            {
                RecursiveInsertBinarySearchTree(tree->left, val);
            }
        }
        else if (val > tree->val)
        {
            if (tree->right == NULL)
            {
                Tree* new_node = MakeTreeNode(val);
                tree->right = new_node;
            }
            else
            {
                RecursiveInsertBinarySearchTree(tree->right, val);
            }
        }
        else if (val == tree->val)
        {
            if (tree->left == NULL)
            {
                Tree* new_node = MakeTreeNode(val);
                tree->left = new_node;
            }
            else
            {
                RecursiveInsertBinarySearchTree(tree->left, val);
            }
        }
    }
}
void IterativeInsertBinarySearchTree(Tree* tree, int val) {

    if (tree->val == INT_MIN) {
        tree->val = val;
        return;
    }

    Tree *node = tree;
    while (1) {
        if (val < node->val) {
            if (node->left == NULL) {
                node->left = MakeTreeNode(val);
                return;
            } else
                node = node->left;
        } else if (val > node->val) {
            if (node->right == NULL) {
                node->right = MakeTreeNode(val);
                return;
            } else
                node = node->right;
        } else if (val == node->val) {
            if (node->left == NULL) {
                Tree *new_node = MakeTreeNode(val);
                node->left = new_node;
                return;
            } else
                node = node->left;
        }
    }
}

Tree* IterativeInsert(Tree* t, int val)
{
    Tree *insert,*search,*parent;
    insert = (Tree*) malloc(sizeof (Tree));
    insert->val = val;
    insert->left = NULL;
    insert->right = NULL;

    if (t == NULL)
        return insert;

    search = t;
    do {
        parent = search;

        if(val < parent->val)
            search = parent->left;
        else if (val > parent->val)
            search = parent->right;
    } while (search);

    if (val < parent->val)
        parent->left = insert;
    else if (val > parent->val)
        parent->right = insert;

    return t;

}

void InOrderTraversal(Tree *t)
{
    Tree* current;
    Stack* stack = CreateStack();
    PushStack(stack,t);
    current = t->left;

    while (!EmptyStack(stack))
    {
        while (current->left)
        {
            current = current->left;
            PushStack(stack,current);
        }
        printf("%d\n", (current = PopStack(stack))->val);

        while (!(current->left) && (current->right) && (current = current->right))
        {
            PushStack(stack,current);
        }
    }
}




void recursive_tree_to_array(Tree* tree, int* array, int* index) {
    int flag = 0;
    if (tree->left != NULL) {
        recursive_tree_to_array(tree->left, array, index);
    }
    else
    {
        array[*index] = tree->val;
        *index += 1;
        flag = 1;
    }

    if (tree->right != NULL)
    {
        if (!flag) {
            array[*index] = tree->val;
            *index += 1;
            recursive_tree_to_array(tree->right, array, index);
        }
        else
            recursive_tree_to_array(tree->right, array, index);
    }
    else if (!flag)
    {
        array[*index] = tree->val;
        *index += 1;
    }

}





void iterative_tree_to_array(Tree* tree, int* array) {
    Queue *queue = makeQueue();
    enQueueFront(queue, tree);
    int index = 0;


    while (queue->head->tree_node->left != NULL)
        enQueueFront(queue, queue->head->tree_node->left);

    while (queue->size > 0)
    {
        Tree* node = deQueue(queue);
        array[index] = node->val;
        index++;
        if (node->right != NULL)
        {
            enQueueFront(queue,node->right);
            while (queue->head->tree_node->left != NULL)
                enQueueFront(queue, queue->head->tree_node->left);
        }
    }
}

struct TreeNode *BuildNewTree(struct TreeNode *t)
{
    struct TreeNode *temp;

    if (t != NULL)
    {
        temp =  (struct TreeNode*)malloc(sizeof(struct TreeNode));

        if (temp == NULL)
            printf("Out of memory space!!!\n");
        else
        {
            temp->val = t->val;

            temp->right = BuildNewTree(t->left);

            temp->left = BuildNewTree(t->right);
        }
        return temp;
    }
    else
        return NULL;
}





struct ListNode* IterativeReverseList(struct ListNode* p)
{
    struct ListNode *previous, *reverse, *successor;
    if ((p == NULL) || (p->next == NULL))
        return p;
    else
    {
        previous = NULL;
        reverse = p;
    }
    while (reverse->next)
    {
        successor = reverse->next;

        reverse->next = previous;

        previous = reverse;

        reverse = successor;
    }

    reverse->next = previous;

    return reverse;
}



struct ListNode* RecursiveReverseList(struct ListNode* previous, struct ListNode* current)

{

    struct ListNode* successor; /* declaration of a local variable */

    if (current == NULL)
        return previous;

    else
    {
        successor = RecursiveReverseList(current,current->next);
        current->next = previous;

        return successor;
    }
}
