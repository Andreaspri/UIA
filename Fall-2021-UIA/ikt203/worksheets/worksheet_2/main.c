


#include <malloc.h>
#include <stdio.h>

typedef struct Stack{
    int capacity;
    int top;
    char* array;
}stack;


int StackSize(stack* size_stack)
{
    return size_stack->top+1;
}

char InspectTopOfStack(stack* ins_stack)
{
    return ins_stack->array[ins_stack->top];
}

void Push(stack* push_stack, char element)
{

    push_stack->array[++push_stack->top] = element;
}

char Pop(stack* pop_stack)
{
    if (pop_stack->top > -1)
        return pop_stack->array[pop_stack->top--];
    return '$';
}



void EmptyStack(stack* rm_stack)
{
    rm_stack->top = -1;
}


stack* CreateStack()
{
    stack* new_stack = malloc(sizeof(stack));
    new_stack->capacity = 50000;
    new_stack->top = -1;
    new_stack->array = malloc(sizeof(char)*new_stack->capacity);

    return new_stack;
}



int main()
{


    stack* my_stack = CreateStack();

    Push(my_stack,'a');

    printf("%c\n", InspectTopOfStack(my_stack));

    printf("%i\n", StackSize(my_stack));

    Push(my_stack,'4');

    printf("%c\n",Pop(my_stack));

    printf("%c\n", InspectTopOfStack(my_stack));

    printf("%i\n", StackSize(my_stack));




    return 0;
}