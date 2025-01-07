#include <stdlib.h>
#include <stdio.h>
#include "pri_queue.h"
/** @file pri_queue.c */
static Node_ptr_t head = NULL;
/**
 * Insert a Node into a priority queue.
 * @param priority
 * @param data
 * @author 
 */

void PQ_insert(int priority, char * data) {
 //FIX THIS

 //Create new node to insert
 Node_ptr_t newNode, newTemp;
 newNode = (Node_ptr_t)malloc(sizeof(Node_t));
 newNode -> data = data;
 newNode -> priority = priority;
 
 //Check if the first head node is empty
 if (head == NULL){
     newNode -> next = NULL;
     head = newNode; 
 } 
 
 //Check if newNode_priority greater than head, swap if so
 else if (head-> priority <  newNode->priority){
     newNode->next = head;
     head = newNode;
 }
 
 // Else do the following... 
 else {
     for (newTemp = head; newTemp-> next->next != NULL && newNode->priority  < newTemp->priority; newTemp = newTemp->next){
         
     }
     newNode->next = newTemp->next;
     newTemp->next = newNode;
    }
}

/**
 * Delete and return the node with the highest priority.
 * @return The highest priority Node.
 */
Node_ptr_t PQ_delete() {
  //FIX THIS

  //Create a new temp
  Node_ptr_t temp = head;

  head = head->next;

    return temp;
}

/**
 * Do NOT modify this function.
 * @return A pointer to the head of the list.  (NULL if list is empty.)
 */
Node_ptr_t PQ_get_head() {
    return head;
}

/**
 * Do NOT modify this function.
 * @return the number of items in the queue
 */
int PQ_get_size() {
    int size = 0;
    Node_ptr_t tmp;
    for(tmp = head; tmp != NULL; tmp = tmp->next, size++);
    return size;
}
