#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    char *data;
    struct Node *next;
    struct Node *previous;
};

struct Node *insert(struct Node *current, char *data);
void printtree(struct Node *node, int level);
struct Node **search(struct Node **arrayofpointer, char *data);
struct Node *delete (struct Node *head, char *data);

int main(void)
{
    struct Node *head = (struct Node *)malloc(sizeof(struct Node));
    head->data = "5";
    head->next = NULL;
    head->previous = NULL;
    insert(head, "2");
    insert(head, "c");
    insert(head, "w");
    insert(head, "z");
    insert(head, "u");
    insert(head, "a");
    insert(head, "2"); // duplicate value
    insert(head, "3");
    insert(head, "1");
    printtree(head, 0);
    struct Node **arrayofpointer = (struct Node **)malloc(2 * sizeof(struct Node *));
    *arrayofpointer = head;
    printf("Search for \"c\": %s\nparent of  \"c\": %s\n",
           (*search(arrayofpointer, "c"))->data,
           (*(search(arrayofpointer, "c") + 1))->data);
    head = delete (head, "5");
    delete (head, "3");
    printtree(head, 0);
    return 0;
}

void printtree(struct Node *node, int level)
{
    struct Node *previous = node->previous;
    struct Node *next = node->next;
    if (next != NULL)
    {
        printtree(next, 1 + level);
    }
    for (int i = 0; i < level; i++)
    {
        printf("\t");
    }
    printf("%s\n", node->data);
    if (previous != NULL)
    {
        printtree(previous, 1 + level);
    }
}

struct Node *insert(struct Node *current, char *data)
{
    char *currentdata = current->data;
    int comparedvalue = strcmp(currentdata, data);
    // printf("%d , %s, %s\n", comparedvalue, currentdata, data);
    if (comparedvalue > 0)
    {
        // current > new
        // printf("current < new\n");
        struct Node *previous = current->previous;
        if (previous != NULL)
        {
            return insert(current->previous, data);
        }
        else
        {
            previous = current->previous = (struct Node *)malloc(sizeof(struct Node));
            previous->data = data;
            return previous;
        }
    }
    else if (comparedvalue < 0)
    {
        // current < new
        struct Node *next = current->next;
        if (next != NULL)
        {
            return insert(current->next, data);
        }
        else
        {
            next = current->next = (struct Node *)malloc(sizeof(struct Node));
            next->data = data;
            return next;
        }
    }
    else
    {
        printf("Cannot insert since the value is duplicated with the list\n");
        return NULL;
    }
}

struct Node **search(struct Node **arrayofpointer, char *data)
{
    struct Node *current = *(arrayofpointer);
    char *currentdata = current->data;
    int comparedvalue = strcmp(currentdata, data);
    if (comparedvalue < 0)
    {
        // current < new
        struct Node *next = current->next;
        *(arrayofpointer) = next;
        *(arrayofpointer + 1) = current;
        if (next != NULL)
        {
            return search(arrayofpointer, data);
        }
        else
        {
            printf("Cannot find value\n");
            return arrayofpointer;
        }
    }
    else if (comparedvalue > 0)
    {
        // current > new
        struct Node *previous = current->previous;
        *(arrayofpointer) = previous;
        *(arrayofpointer + 1) = current;
        if (previous != NULL)
        {
            return search(arrayofpointer, data);
        }
        else
        {
            printf("Cannot find value\n");
            return arrayofpointer;
        }
    }
    else
    {
        return arrayofpointer;
    }
}

// just needed head
struct Node *delete (struct Node *head, char *data)
{
    struct Node **arrayofpointer = (struct Node **)malloc(2 * sizeof(struct Node *));
    *arrayofpointer = head;
    struct Node **result = search(arrayofpointer, data);
    struct Node *node = *result;
    struct Node *parentnode = *(result + 1);
    free(arrayofpointer);
    free(result);
    if (node != NULL)
    {
        struct Node *next = node->next;
        struct Node *previous = node->previous;
        int comparedresult = parentnode == NULL ? 0 : strcmp(node->data, parentnode->data);
        if (next == NULL)
        {
            if (previous == NULL)
            {
                if (comparedresult < 0)
                {
                    // node is on the left of parent
                    parentnode->previous = NULL;
                }
                else if (comparedresult > 0)
                {
                    // node is on the right of parent
                    parentnode->next = NULL;
                }
            }
            else
            {
                if (comparedresult < 0)
                {
                    // node is on the left of parent
                    parentnode->previous = previous;
                }
                else if (comparedresult > 0)
                {
                    // node is on the right of parent
                    parentnode->next = previous;
                }
                else
                {
                    return previous;
                }
            }
        }
        else if (previous == NULL)
        {
            if (comparedresult < 0)
            {
                // node is on the left of parent
                parentnode->previous = next;
            }
            else if (comparedresult > 0)
            {
                // node is on the right of parent
                parentnode->next = next;
            }
            else
            {
                return next;
            }
        }
        else
        {
            // 2 parents == complex case
            struct Node *temp = next;
            struct Node *parentoftemp = node;
            previous = next->previous;
            while (previous != NULL)
            {
                parentoftemp = temp;
                temp = previous;
                next = previous->next;
                previous = previous->previous;
            }
            temp->previous = node->previous;
            parentoftemp->previous = NULL;
            if (temp->next == NULL && parentoftemp->data != node->data)
            {
                temp->next = node->next;
            }
            if (comparedresult < 0)
            {
                // node is on the left of parent
                parentnode->previous = temp;
            }
            else if (comparedresult < 0)
            {
                // node is on the right of parent
                parentnode->next = temp;
            }
            else
            {
                return temp;
            }
        }
        free(node);
        return parentnode;
    }
    else
    {
        return NULL;
    }
}