#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stack
{
    unsigned int capacity;
    int current;
    char **array;
};

struct Stack *createStack(unsigned int capacity);
void insert(struct Stack *stack, char *data);
void deleteTop(struct Stack *stack);
char *openTop(struct Stack *stack);
int isEmpty(struct Stack *stack);
int isFull(struct Stack *stack);
void deleteStack(struct Stack* stack);

int main(void)
{
    struct Stack *stack = createStack(100);
    insert(stack, "test1");
    insert(stack, "test2");
    insert(stack, "test3");
    insert(stack, "test4");
    char *data1 = openTop(stack);
    printf("result : %s\n", data1);
    deleteTop(stack);
    char *data2 = openTop(stack);
    printf("result : %s\n", data2);
    insert(stack, "test5");
    char *data3 = openTop(stack);
    printf("result : %s\n", data3);
    deleteStack(stack);
    return 0;
}

struct Stack *createStack(unsigned int capacity)
{
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->array = (char **)malloc(capacity * sizeof(char *));
    stack->capacity = capacity;
    return stack;
}

void insert(struct Stack *stack, char *data)
{
    if (isFull(stack) == 0)
    {
        char * currentData = (stack->array)[++(stack->current)] = (char *) malloc(sizeof(char));
        strcpy(currentData, data);
    }
    else
    {
        printf("Cannot insert: the stack is full\n");
    }
}

void deleteTop(struct Stack *stack)
{
    if (isEmpty(stack) == 0)
    {
        free((stack->array)[(stack->current)--]);
    }
    else
    {
        printf("Cannot delete: the stack is empty\n");
    }
}

char *openTop(struct Stack *stack)
{
    return (stack->array)[stack->current];
}

int isEmpty(struct Stack *stack)
{
    return (stack->current == 0) ? 1 : 0;
}

int isFull(struct Stack *stack)
{
    return (stack->current == stack->capacity) ? 1 : 0;
}

void deleteStack(struct Stack* stack) {
    char** array = stack->array;
    for(int i = 0; i <= (stack->current); i++) {
        free(array[i]);
    }
    free(stack->array);
    free(stack);
}