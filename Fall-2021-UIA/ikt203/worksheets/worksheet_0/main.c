#include <stdio.h>
#include <malloc.h>
#include <string.h>




typedef struct workshop_tools{
    int record;
    char tool_name[20];
    int quantity;
    double cost;
}tools_t;




void swap (int *p, int *q){
    int t = *p;
    *p = *q;
    *q = t;
}

void find_two_largest(int *largest, int *second_largest){
    int temp = -1;
    *largest = 0;
    *second_largest = 0;
    while (temp != 0){
    printf("Enter a value to be stored: \n");
    scanf("%i",&temp);
    if (temp > *largest)
        *largest = temp;
    else if (temp > *second_largest)
        *second_largest = temp;
    }
}


void Reduce (int numerator, int denominator, int *reduced_numerator, int *reduced_denominator){
    int temp;
    int a = numerator;
    int b = denominator;
    while (b != 0){
        temp = b;
        b = a % b;
        a = temp;
    }

    *reduced_numerator = numerator/a;
    *reduced_denominator = denominator/a;

}


void pay_month(int dollars, int *twenties, int *tens, int *fives, int *ones){
    *twenties = (int)dollars / 20;
    dollars %= 20;
    *tens = (int)dollars / 10;
    dollars %= 10;
    *fives = (int)dollars / 5;
    *ones = dollars % 5;

}


int inner_product(int *a, int *b, int n){
    int total = 0;
    for (int i = 0; i < n; i++, a++, b++){
        total += *a * *b;
    }
    return total;
}









tools_t * read_file(int* tool_count)
{
    FILE *file;

    tools_t* tools = (tools_t*) malloc(sizeof(tools_t));

    file = fopen("C:\\Users\\Andreas\\Documents\\C_projects\\worksheets\\worksheet_0\\hardware.dat","r");

    if (file == NULL){
        printf("File didnt open properly");
        return NULL;
    }


    char temp[100] = {0};
    int column_count = 0;

    int i = 0;
    while (!feof(file))
    {
        temp[i] = fgetc(file);
        if (temp[i] == ',')
        {
            temp[i] = 0;
            if (column_count == 0)
                sscanf(temp,"%i",&tools[*tool_count].record);
            else if (column_count == 1)
                strcpy(tools[*tool_count].tool_name,temp);
            else if (column_count == 2)
                sscanf(temp,"%i",&tools[*tool_count].quantity);
            column_count++;
            memset(temp,0,100);
            i = 0;
            continue;
        }
        else if (temp[i] == '\n')
        {
            temp[i] = 0;
            sscanf(temp,"%lf",&tools[*tool_count].cost);
            memset(temp,0,100);
            column_count = 0;
            *tool_count += 1;
            tools = (tools_t*) realloc(tools,sizeof(tools_t)*(*tool_count+1));
            i = 0;
            continue;
        }

        i++;
    }
    sscanf(temp,"%lf",&tools[*tool_count].cost);
    fclose(file);
    return tools;
}


void write_to_file(tools_t* tools,const int tool_count)
{
    FILE* file;
    file = fopen("C:\\Users\\Andreas\\Documents\\C_projects\\worksheets\\worksheet_0\\hardware.dat","w");

    if (file == NULL){
        printf("File didnt open properly");
    }
    for (int i=0;i<tool_count;i++)
        fprintf(file,"%i,%s,%i,%lf\n",tools[i].record,tools[i].tool_name,tools[i].quantity,tools[i].cost);
    fclose(file);
}




void list_tools(tools_t * tools,int tool_count)
{
    for (int i=0;i<tool_count;i++)
    {
    printf("Record: %i, Tool Name: %s, Quantity: %i, Cost: %lf\n",tools[i].record,tools[i].tool_name,tools[i].quantity,tools[i].cost);
    }
}

tools_t* new_tool(tools_t * tools, int* tool_count)
{
    tools = (tools_t*) realloc(tools,sizeof(tools_t)* *(tool_count+1));
    int flag = 1;

    while (flag){
        flag = 0;
        printf("Enter record number: \n");
        scanf("%i",&tools[*tool_count].record);
        getchar();

        for (int i=0;i<*tool_count;i++)
        {
            if (tools[i].record == tools[*tool_count].record)
            {
                printf("Record number already exists\n");
                flag = 1;
                break;
            }
        }
    }

    printf("Enter tool name: \n");
    fgets(tools[*tool_count].tool_name,20,stdin);
    tools[*tool_count].tool_name[strcspn(tools[*tool_count].tool_name, "\n")] = 0;

    printf("Enter quantity: \n");
    scanf("%i",&tools[*tool_count].quantity);
    getchar();

    printf("Enter cost: \n");
    scanf("%lf",&tools[*tool_count].cost);
    getchar();

    *tool_count += 1;

    write_to_file(tools, *tool_count);

    printf("Added tool to database \n");
    printf("Record: %i, Tool Name: %s, Quantity: %i, Cost: %lf\n", \
    tools[*tool_count-1].record,tools[*tool_count-1].tool_name,tools[*tool_count-1].quantity,tools[*tool_count-1].cost);



    return tools;
}


void update_tool(tools_t* tools,int tool_count)
{
    int tool_record;
    printf("Enter record number for the tool you want to edit\n");
    scanf("%i",&tool_record);
    getchar();

    for (int i=0;i<tool_count;i++)
    {
        if (tool_record == tools[i].record)
        {
            printf("Enter tool name: \n");
            fgets(tools[i].tool_name,20,stdin);
            tools[i].tool_name[strcspn(tools[i].tool_name, "\n")] = 0;
            printf("Enter Quantity: \n");
            scanf("%i",&tools[i].quantity);
            getchar();
            printf("Enter cost: \n");
            scanf("%lf",&tools[i].cost);
            getchar();
            write_to_file(tools, tool_count);

            printf("Edited tool to Successfully \n");
            printf("Record: %i, Tool Name: %s, Quantity: %i, Cost: %lf\n", \
            tools[i].record,tools[i].tool_name,tools[i].quantity,tools[i].cost);
        }
    }
    printf("Record does not exist\n");
}

tools_t* delete_record(tools_t* tools, int* tool_count)
{
    int del_rec;
    printf("Enter record number you want to delete: \n");
    scanf("%i",&del_rec);
    getchar();

    for (int i=0;i<*tool_count;i++)
    {
        if (tools[i].record == del_rec)
        {
            if (i == *tool_count-1 && tools[i].record == del_rec)
            {
                tools = (tools_t*) realloc(tools,sizeof(tools_t)* *tool_count-1);
                *tool_count -= 1;
                write_to_file(tools,*tool_count);
                printf("Successfully deleted record %i\n", del_rec);
                return tools;
            }
            else if (tools[i].record == del_rec)
            {
                tools[i] = tools[*tool_count-1];
                tools = (tools_t*) realloc(tools,sizeof(tools_t)* *tool_count-1);
                *tool_count -= 1;
                write_to_file(tools,*tool_count);
                printf("Successfully deleted record %i\n", del_rec);
                return tools;

            }
        }
    }
    printf("The record number does not exist\n");
    return tools;
}

int main() {



    /* Part 1 */
    /* a */
    /*
    int p = 10;
    int q = 20;
    printf("p is: %i and q is: %i\n", p,q);
    swap(&p,&q);
    printf("Now p is: %i and q is: %i",p,q);
    */

    /* b */
    /*
    int largest,second_largest;
    find_two_largest(&largest,&second_largest);
    printf("Largest value stored is %i and second largest value stored is %i", largest, second_largest);
    */

    /* c */
    /*
    int numerator;
    int denominator;
    printf("Enter numerator: \n");
    scanf("%i",&numerator);
    printf("Enter denominator: \n");
    scanf("%i",&denominator);
    printf("The numerator is now %i and the denominator is %i \n", numerator, denominator);
    Reduce(numerator,denominator,&numerator,&denominator);
    printf("After reduce function the numerator is now %i and the denominator is %i \n", numerator, denominator);
    */

    /* d */
    /*
    int twenties;
    int tens;
    int fives;
    int ones;
    int dollars;
    printf("Enter dollars: \n");
    scanf("%i",&dollars);
    pay_month(dollars,&twenties,&tens,&fives,&ones);
    printf("You need to pay %ix$20 + %ix$10 + %ix$5 + %ix$1",twenties,tens,fives,ones);
    */



    /* Part 2 */

    /* a */
    /*
    int n;
    printf("How many elements do you want to store? \n");
    scanf("%i",&n);
    int* arr1 = (int*) malloc(n*sizeof(int));
    int* arr2 = (int*) malloc(n*sizeof(int));
    for (int i = 0; i < n; i++){
        printf("Enter value to be stored in the first array: \n");
        scanf("%i",arr1+i);
    }
    for (int i = 0; i < n; i++){
        printf("Enter value to be stored in the second array: \n");
        scanf("%i",arr2+i);
    }
    printf("Result of inner product is: %i", inner_product(arr1,arr2,n));
    */



    int tool_count = 0;
    int choice;
    tools_t * tools = read_file(&tool_count);


    while (1){
        printf("What do you wanna do? \n"
               "1. List all your tools \n"
               "2. New tool \n"
               "3. Update tool \n"
               "4. Delete tool \n"
               "5. Exit \n");
        scanf("%i",&choice);
        getchar();
        switch (choice) {
            case 1:
                list_tools(tools,tool_count);
                break;
            case 2:
                tools = new_tool(tools,&tool_count);
                break;
            case 3:
                update_tool(tools,tool_count);
                break;
            case 4:
                tools = delete_record(tools,&tool_count);
                break;
            case 5:
                return 0;
            default:
                continue;
        }
    }






    //printf("Tool Count: %i\n",tool_count);

    return 0;
}
