#include <stdlib.h>
#include <stdio.h>
#include "pri_queue.h"
/** @file pri_queue.c */
static Node_ptr_t head = NULL;
/**
 * Insert a Node into a priority queue.
 * @param priority
 * @param data
 * @author Arshia Rahim
 */

void PQ_insert(int priority, char * data) {
 //FIX THIS

 //Create new node to insert
 Node_ptr_t newNode = malloc(sizeof(Node_t));
 newNode-> priority = priority;
 newNode-> data = data;
 newNode-> next = NULL;

 // Create Temporary node to use
 Node_ptr_t temp = malloc(sizeof(Node_t));
 Node_ptr_t curr = malloc(sizeof(Node_t));
 Node_ptr_t NodeInsert = malloc(sizeof(Node_t));

 // Check if head is NULL, if yes then insert node as head
 if (head == NULL){
     head = malloc(sizeof(Node_t));
     NodeInsert =  newNode;
 }

 //If the priority of new node is greater than the currect head's priority
 //Then push new node to head, and previous head moves back to PQ
 //First store old head onto temp code
 else {
    if (priority > head->priority){
        temp->data = head->data;
        temp->priority = head->priority;
        temp->next = temp->next;

    //Make new node the head, and make the next node the previous head
    //Which was stored in temp node
        head = newNode;
        head->next = temp;

    //Traverse list until you reach the end, or find a node with
    //a lower priority than the new node
        }
        else {
            NodeInsert = newNode;
            curr = head;
            while(curr -> next != NULL & NodeInsert -> priority < curr->next->priority){
                curr = curr->next;
            }

    //Insert at the end of the PQ

            if (curr->next == NULL){
                curr->next = NodeInsert;
                NodeInsert->next = NULL;
            }

    //Insert in the middle of PQ (If new node's PQ higher than an existing node's PQ)
            else {
                temp = malloc(sizeof(Node_t));
                temp = curr->next;
                curr->next = NodeInsert;
                NodeInsert->next = temp;
            }
        }
    }
 }

/**
 * Delete and return the node with the highest priority.
 * @return The highest priority Node.
 */
Node_ptr_t PQ_delete() {
  //FIX THIS

  //Create a new temp
  Node_ptr_t temp = malloc(sizeof(Node_t));

  temp = head;
  head = head->next;
  free(temp);

    return NULL;
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


