#include <stdio.h>
#include <stdlib.h>

static struct node {
    int value;
    struct node *next;
} *head = NULL;

void *add_to_list(int n);
void *add_to_ordered_list(int n);
void *delete_from_list(int n);
struct node *search_list(int n);
void clear_list(void);
int list_size(void);
void print_node_values(void);


int main(void)
{
    add_to_list(1);
    add_to_list(2);
    add_to_list(3);
    add_to_list(4);
    add_to_list(5);
    print_node_values();
    clear_list();
    printf("\n");

    add_to_ordered_list(1);
    add_to_ordered_list(2);
    add_to_ordered_list(3);
    add_to_ordered_list(4);
    add_to_ordered_list(5);
    print_node_values();
    delete_from_list(4);
    printf("\n");
    print_node_values();
    printf("\n");

    printf("%s\n", search_list(2) ? "Found Node." : "Node not found.");
    printf("%s\n", search_list(4) ? "Found Node." : "Node not found.");

    printf("Number of nodes in list: %d\n", list_size());

    clear_list();
    printf("Number of nodes in list: %d\n", list_size());

    return 0;
}

/* Adds a node to the linked list with the value n */
void *add_to_list(int n)
{
    struct node *new_node;

    if ((new_node = malloc(sizeof(struct node))) == NULL) {
        printf("Error: malloc failed in add_to_list\n");
        exit(EXIT_FAILURE);
    }

    new_node->value = n;
    new_node->next = head;
    head = new_node;
}

/* Delete a node from the linked list. Argument pp is a pointer to a pointer
 * to the first node in the list, n is the value of the node(s) to delete */
void *delete_from_list(int n)
{
    struct node **pp = &head;
    struct node *entry = head;

    while (entry) {
        if (entry->value == n) {
            *pp = entry->next;
            free(entry);
        }
        pp = &entry->next;
        entry = entry->next;
    }
}

/* Search for a node in the linked list. Argument p is a pointer to the
 * first node in the list, int n is the value of the node to find
 * Returns the first node with the matching value that it finds */
struct node *search_list(int n)
{
    struct node *node = head;

    while (node != NULL && node->value != n)
        node = node->next;
    return node;
}

/* Returns the number of nodes in the linked list. Argument p is
 * a pointer to the first node in the list */
int list_size(void)
{
    int count = 0;
    struct node *entry;

    for (entry = head; entry; entry = entry->next, count++)
        ; /* Empty loop body */

    return count;
}

/* Frees all memory allocated to nodes in the linked list */
/* Argument pp is a pointer to the head pointer of the */
/* linked list */
void clear_list(void)
{
    struct node *temp;

    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

/* Inserts a node into list in numerical order by value */
void *add_to_ordered_list(int n)
{
    struct node **pp = &head;
    struct node *entry = head;

    while (entry) {
        if (entry->value >= n) {
            break;
        }
        pp = &entry->next;
        entry = entry->next;
    }

    struct node *new_node;
    if ((new_node = malloc(sizeof(struct node))) == NULL) {
        printf("Error, malloc in insert_into_ordered_list\n");
        exit(EXIT_FAILURE);
    }
    new_node->next = entry;
    new_node->value = n;
    *pp = new_node;
}

/* Prints all the nodes and their values in the list */
/* Argument p is a pointer to the first node in the */
/* linked list. */
void print_node_values(void)
{
    int count = 0;
    struct node *entry = head;
    while (entry) {
        count++;
        printf("Node %d: %d\n", count, entry->value);
        entry = entry->next;
    }
}
