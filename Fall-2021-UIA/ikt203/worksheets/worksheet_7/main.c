#include <stdio.h>
#include <stdlib.h>

#include "queue.h"




void BFS(Tree* tree)
{
    Queue* queue1 = makeQueue();
    Queue* queue2 = makeQueue();
    enQueue(queue1,tree);
    while (queue1->size != 0 || queue2->size != 0)
    {

            while (queue1->size != 0)
            {
                Tree* node = deQueue(queue1);
                printf("%i ",node->val);
                if (node->left != NULL)
                    enQueue(queue2,node->left);

                if (node->right != NULL)
                    enQueue(queue2,node->right);
            }
            printf("\n");

            while (queue2->size != 0)
            {
                Tree* node = deQueue(queue2);
                printf("%i ",node->val);
                if (node->left != NULL)
                    enQueue(queue1,node->left);

                if (node->right != NULL)
                    enQueue(queue1,node->right);
            }
            printf("\n");
    }

    free(queue1);
    free(queue2);
}



Tree* MakeTreeNode(int val)
{
    struct TreeNode* new_tree = (struct TreeNode*)malloc(sizeof(struct TreeNode));
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
        else
        {
            printf("Node exists already\n");
            return;
        }
    }
}














int main() {

    Tree* binary_tree = MakeTreeNode(257);

    for (int i = 0; i < 10; ++i)
    {
        RecursiveInsertBinarySearchTree(binary_tree, rand()%783);
    }

    BFS(binary_tree);


    return 0;
}
