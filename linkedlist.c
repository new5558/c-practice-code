#include <stdio.h>
#include <stdlib.h>

struct Node
{
    char *data;
    struct Node *next;
    struct Node *previous;
};

void printfromhead(struct Node *head);
void deletenode(struct Node *head);
void printfromanynode(struct Node *any);
struct Node * insert(struct Node *current, char *data);

int main(void)
{
    struct Node *head = malloc(sizeof(struct Node));
    head->data = "test0";

    struct Node* a = insert(head, "test1");
    struct Node* b = insert(a, "test2");
    struct Node* c = insert(b, "test3");
    struct Node* d = insert(c, "test4");
    struct Node* e = insert(d, "test5");
    struct Node* f = insert(e, "test6");

    deletenode(c);
    deletenode(f);
    printfromhead(head);
    // printfromanynode(e);
    return 0;
}

struct Node *insert(struct Node *current, char *data)
{
    struct Node *currenttemp = current;
    struct Node *nexttemp = current->next;
    current = current->next = (struct Node *)malloc(sizeof(struct Node));
    current->previous = currenttemp;
    if (nexttemp != NULL)
    {
        current->next = nexttemp;
        nexttemp->previous = current;
    }
    else
    {
        current->next = NULL;
    }
    current->data = data;
    
    // return next Node
    return current;
}

void deletenode(struct Node *current)
{
    struct Node *currenttemp = current;
    struct Node *previoustemp = current->previous;
    struct Node *nexttemp = current->next;
    if(nexttemp != NULL) {
        nexttemp->previous = previoustemp;
    }
    if(previoustemp != NULL) {
        previoustemp->next = nexttemp;
    }
    free(current);
}

void printfromhead(struct Node *head)
{
    printf("%s\n", head->data);
    if (head->next == NULL)
    {
        return;
    }
    printfromhead(head->next);
}

void printfromanynode(struct Node *any) {
    if(any->previous != NULL) {
        printfromanynode(any->previous);
    } else {
        printfromhead(any);
    }
}