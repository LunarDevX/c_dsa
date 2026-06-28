#include <stdio.h>
#include <stdlib.h>

struct node 
{
    int number; 
    struct node *next;
};

struct linkedList
{
    struct node *head;
};

struct listIterator
{
    struct node *node; 
};

struct listIterator iterator(struct linkedList *list);
int hasNext(struct listIterator *it);
int next(struct listIterator *it);

void listinit(struct linkedList *list);

void addFirst(struct linkedList *list,int number); 
void addLast(struct linkedList *list,int number); 
int removeFirst(struct linkedList *list); 
int removeLast(struct linkedList *list); 
void printList(struct linkedList *list); 
void printByIterator(struct linkedList *list); 
void unload(struct linkedList *list); 

/*
Heavily inspired from my univerisity explaining it in Java -- 
Head Node and Last Node -= NULL coming from university as well. 
*/

int main(void)
{

    struct linkedList list;
    listinit(&list);
    addFirst(&list, 1); 
    addFirst(&list, 2);
    addLast(&list, 0); 
    addLast(&list, 20); // 2 -> 1 -> 0 -> 20; 
    
    printByIterator(&list);
    printf("------\n");
    printList(&list);

    int first = removeFirst(&list); 
    printf("First: %i\n", first);
    printList(&list);

    int last = removeLast(&list); 
    printf("Last: %i\n", last);
    printList(&list);

    int slast = removeLast(&list); 
    printf("Last: %i\n", slast);
    printList(&list);

    unload(&list);
    return 0;
}

void listinit(struct linkedList *list)
{
    struct node *head = (struct node *) malloc(sizeof *head); 

    if (head == NULL)
    {
        return; 
    }

    head->next = NULL; 
    list->head = head; 
}

int isEmpty(struct node *ptr)
{
    return ptr->next == NULL;
}

void addFirst(struct linkedList *list, int number)
{
    struct node *t = (struct node *) malloc(sizeof *t); 
    if (t == NULL)
    {
        return; 
    }

    struct node *ptr = list->head;

    t->number = number;
    t->next = ptr->next;
    ptr->next = t; 

}

void addLast(struct linkedList *list, int number) 
{
    struct node *t = (struct node *) malloc(sizeof *t); 
    if (t == NULL)
    {
        return; 
    }
    t->number = number; 
    t->next = NULL;

    struct node *ptr = list->head;
    while(ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = t; 
}

int removeFirst(struct linkedList *list)
{
    struct node *ptr = list->head; 

    if (isEmpty(ptr)) 
    {
        return 1;
    }
    struct node *first = ptr->next;

    int n =  first->number; 
    ptr->next = first->next;
    free(first);
    return n; 
}

int removeLast(struct linkedList *list)
{

    struct node *ptr = list->head; 
    if (isEmpty(ptr))
    {
        return 1; 
    }

    while (ptr->next->next != NULL)
    {
        ptr = ptr->next;
    }

    struct node *last = ptr->next;
    int n = last->number;
    ptr->next = NULL;
    free(last);

    return n; 
}

struct listIterator iterator(struct linkedList *list)
{
    struct listIterator it; 
    it.node = list->head; 
    return it; 
}

int hasNext(struct listIterator *it)
{
    return it->node->next != NULL; 
}

int next(struct listIterator *it)
{
    if (!hasNext(it))
    {
        printf("No such element\n");
        exit(1);
    }

    it->node = it->node->next;
    int n = it->node->number;
    return n;
}

void unload(struct linkedList *list)
{
    struct node *ptr = list->head->next;
    while (ptr != NULL)
    {
        struct node *next = ptr->next;
        free(ptr);
        ptr = next;
    }

    free(list->head);
}

void printByIterator(struct linkedList *list)
{
    struct listIterator it = iterator(list);

    while(hasNext(&it))
    {
        int n = next(&it);
        printf("%i ", n);
    }
    printf("\n");
}

void printList(struct linkedList *list)
{
    for (struct node *ptr = list->head->next; ptr != NULL; ptr = ptr->next)
    {
        printf("%i ", ptr->number);
    }

    printf("\n");
}
