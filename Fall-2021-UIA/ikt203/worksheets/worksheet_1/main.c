#include <stdio.h>
#include <stdlib.h>


struct ListNode{
    int val;
    struct ListNode* next;
};



void ReverseRecursive(struct ListNode**, struct ListNode*, struct ListNode*);

struct ListNode* DynamicBuild(struct ListNode* head, int val){
    struct ListNode* new_item = malloc(sizeof(struct ListNode));

    new_item->val = val;
    new_item->next = head;
    head = new_item;

    return head;
}

void ReverseList(struct ListNode** head)
{
    if (head != NULL)
        ReverseRecursive(head, NULL, *head);
}

void ReverseRecursive(struct ListNode** head,struct ListNode* prev, struct ListNode* curr)
{

    if (curr->next == NULL)
    {

        *head = curr;
        curr->next = prev;
        return;
    }

    struct ListNode* next = curr->next;

    curr->next = prev;

    ReverseRecursive(head,curr,next);


}



void printlist(struct ListNode* head){
    for (struct ListNode* tmp=head; tmp!=NULL;tmp=tmp->next)
    {
        printf("%i\n",tmp->val);
    }
    printf("\n");
}



int main() {

    struct ListNode* head = malloc(sizeof(struct ListNode));
    head = NULL;

    for (int i=0; i<5;i++){
        head = DynamicBuild(head,i);
    }

    printlist(head);

    ReverseList(&head);

    printlist(head);




    return 0;
}
