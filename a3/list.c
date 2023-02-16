/** @file list.c
 *  @brief Implementation of a linked list.
 *
 * Based on the implementation approach described in "The Practice
 * of Programming" by Kernighan and Pike (Addison-Wesley, 1999).
 *
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"
#include "list.h"

/**
 * Function:  new_node
 * -------------------
 * @brief  Allows to dynamically allocate memory for a new node to be added to the linked list.
 *
 * This function should confirm that the argument being passed is not NULL (i.e., using the assert library). Then,
 * It dynamically allocates memory for the new node using emalloc(), and assign values to attributes associated with the node (i.e., val and next).
 *
 * @param val The value to be associated with the node.
 *
 * @return node_t* A pointer to the node created.
 *
 */
node_t *new_node(char *a, char *s, char *y, char *p, char *d, char *e)
{
    assert(a != NULL);

    node_t *temp = (node_t *)emalloc(sizeof(node_t));

    temp->artist = strdup(a);
    temp->songtitle = strdup(s);
    temp->year = strdup(y);
    temp->popularity = strdup(p);
    temp->dancebility = strdup(d);
    temp->energy = strdup(e);
    
    temp->next = NULL;

    return temp;
}

/**
 * Function:  add_front
 * --------------------
 * @brief  Allows to add a node at the front of the list.
 *
 * @param list The list where the node will be added (i.e., a pointer to the first element in the list).
 * @param new The node to be added to the list.
 *
 * @return node_t* A pointer to the new head of the list.
 *
 */
node_t *add_front(node_t *list, node_t *new)
{
    new->next = list;
    return new;
}

/**
 * Function:  add_end
 * ------------------
 * @brief  Allows to add a node at the end of the list.
 *
 * @param list The list where the node will be added (i.e., a pointer to the first element in the list).
 * @param new The node to be added to the list.
 *
 * @return node_t* A pointer to the head of the list.
 *
 */
node_t *add_end(node_t *list, node_t *new)
{
    node_t *curr;

    if (list == NULL)
    {
        new->next = NULL;
        return new;
    }

    for (curr = list; curr->next != NULL; curr = curr->next)
        ;
    curr->next = new;
    new->next = NULL;
    return list;
}

/**
 * Functions:  add_inorderpop, add_inorderdanceability, add_inorderenergy
 * ----------------------
 * @brief  Allows to add a new node to the list respecting an order.
 *
 * @param list The list where the node will be added (i.e., a pointer to the first element in the list).
 * @param new The node to be added to the list.
 *
 * @return node_t* A pointer to the node created.
 *
 */

node_t *add_inorderpop(node_t *list, node_t *new){
    node_t *prev = NULL;
    node_t *curr = NULL;

    if (list == NULL)
    {
        return new;
    }

    for (curr = list; curr != NULL; curr = curr->next)
    {
        
        if (atoi(new->popularity) < atoi(curr->popularity))
        {
            prev = curr;
        }
        else
        {
            if ((atoi(new->popularity) == atoi(curr->popularity)) && (strcmp(new->songtitle, curr->songtitle) < 0)) { 
                prev = curr;
            }
            else{
                break;
            }
        }
    }

    new->next = curr;
    if (prev == NULL)
    {
        return (new);
    }
    else
    {
        prev->next = new;
        return list;
    }

}
node_t *add_inorderdanceability(node_t *list, node_t *new){
    node_t *prev = NULL;
    node_t *curr = NULL;

    if (list == NULL)
    {
        return new;
    }

    for (curr = list; curr != NULL; curr = curr->next)
    {
        
        if (atof(new->dancebility) < atof(curr->dancebility))
        {
            prev = curr;
        }
        else
        {
            if ((atof(new->dancebility) == atof(curr->dancebility)) && (strcmp(new->songtitle, curr->songtitle) < 0)) { 
                prev = curr;
            }
            else{
                break;
            }
        }
    }

    new->next = curr;
    if (prev == NULL)
    {
        return (new);
    }
    else
    {
        prev->next = new;
        return list;
    }

}

node_t *add_inorderenergy(node_t *list, node_t *new){
    node_t *prev = NULL;
    node_t *curr = NULL;

    if (list == NULL)
    {
        return new;
    }

    for (curr = list; curr != NULL; curr = curr->next)
    {
        
        if (atof(new->energy) < atof(curr->energy))
        {
            prev = curr;
        }
        else
        {
            if ((atof(new->energy) == atof(curr->energy)) && (strcmp(new->songtitle, curr->songtitle) < 0)) { 
                prev = curr;
            }
            else{
                break;
            }
        }
    }

    new->next = curr;
    if (prev == NULL)
    {
        return (new);
    }
    else
    {
        prev->next = new;
        return list;
    }

}

/**
 * Function:  add_inorder 
 * ---------------------
 * @brief  calls the other functions depending on metric
 *
 * @param list The list where the node will be added (i.e., a pointer to the first element in the list).
 * 
 * @param new The node to be added to the list.
 * 
 * @param metric 0,1,2 depending on the the input
 *
 * @return node_t* A pointer to the node created.
 *
 */

node_t *add_inorder(node_t *list, node_t *new, int metric)
{
    
    if(metric == 0) {
        list = add_inorderpop(list, new);
    }
    else if(metric == 1) {
        list = add_inorderdanceability(list, new);
    }
    else if(metric == 2) {
        list = add_inorderenergy(list, new);
    }
    return list;
}

/**
 * Function:  peek_front
 * ---------------------
 * @brief  Allows to get the head node of the list.
 *
 * @param list The list to get the node from.
 *
 * @return node_t* A pointer to the head of the list.
 *
 */
node_t *peek_front(node_t *list)
{
    return list;
}

/**
 * Function:  remove_front
 * -----------------------
 * @brief  Allows removing the head node of the list.
 *
 * @param list The list to remove the node from.
 *
 * @return node_t* A pointer to the head of the list.
 *
 */
node_t *remove_front(node_t *list)
{
    if (list == NULL)
    {
        return NULL;
    }

    return list->next;
}

/**
 * Function: apply
 * --------------
 * @brief  Allows to apply a function to the list.
 *
 * @param list The list (i.e., pointer to head node) where the function will be applied.
 * @param fn The pointer of the function to be applied.
 * @param arg The arguments to be applied.
 *
 */
void apply(node_t *list,
           void (*fn)(node_t *list, void *),
           void *arg)
{
    for (; list != NULL; list = list->next)
    {
        (*fn)(list, arg);
    }
}
