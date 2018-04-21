/*
 * This program illustrates a singly linked list that is
 * dynamically growing.
 */

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct node {
    char *data;
    struct node* next;
};

main()
{
    char line[BUFSIZ];
    struct node *head, *here, *p, *create(char *);

    /* initialize the linked list with a dummy node */
    head = malloc(sizeof(struct node));
    head->next = NULL;
    here = head;

    /* get a line of input and append it to the linked list */
    printf("Enter lines of text:\n");
    while (gets(line) != NULL) {
        if (line[0] == '.')
            break;
        here->next = create(line);
        here = here->next;
    }

    /* print out the lines in the linked list */
    for (p = head->next; p != NULL; p = p->next)
        puts(p->data);
}


/*
 * this function creates a node
 */

struct node *create(char *input)
{
    struct node *q;

    q = malloc(sizeof(struct node));
    q->data = malloc(strlen(input) + 1);
    strcpy(q->data, input);
    q->next = NULL;
    return(q);
}
