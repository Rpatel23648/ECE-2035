//=================================================================
// Implementation for DLL module.
//
// Copyright 2025 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================
#include <stdlib.h>
#include <stdio.h>
#include "doubly_linked_list.h"

LLNode* create_llnode(void* data) {
    LLNode* newNode = (LLNode*)malloc(sizeof(LLNode)); //Allocates enough memory for Doubly Linked List Node
    newNode->data = data; // Insterts data into node
    newNode->prev = NULL; // Set prev to null bc its a shell to put into a list
    newNode->next = NULL; // Set next to null bc its a shell to put into a list
    return newNode; 
}

DLinkedList* create_dlinkedlist(void) {
    DLinkedList* newList = (DLinkedList*)malloc(sizeof(DLinkedList)); // Allocates enough memory for Doubly Linked List
    newList->head = NULL; //  Sets head to null bc its a shell to put into a list
    newList->tail = NULL; //  Sets tail to null bc its a shell to put into a list
    newList->size = 0; // Sets size to 0 bc its a shell to put into a list
    return newList;
}

int getSize(DLinkedList* dLinkedList){
  return dLinkedList->size; //gets size of list
}

LLNode* getHead(DLinkedList* dLinkedList){
  return dLinkedList -> head; //gets head of list
}

LLNode* getTail(DLinkedList* dLinkedList){
  return dLinkedList -> tail; //gets tail of list
}

LLNode* getNext(LLNode* node){
  return node -> next; // gets next node in list
}

LLNode* getPrev(LLNode* node){
  return node -> prev; // gets previous node in list
}

void* getData(LLNode* node){
  return node -> data; // gets node data and returns it
}

void insertAfter(DLinkedList* dLinkedList, LLNode* prev_node, void* data){
  if (prev_node == NULL) {
    printf("the given previous node cannot be NULL"); // checks if the previous node is null
    return;
  }
  if (prev_node->next == NULL) {
    LLNode* newNode = create_llnode(data); // creates a new node
    prev_node-> next = newNode; // sets the next node of the previous node as the new node
    newNode->prev = prev_node; // sets the previous node of the new node as the previous node
    dLinkedList->tail = newNode; // sets the tail of the list as the new node
    dLinkedList->size++; // increments the size of the list
    return;
  }
  LLNode* newNode = create_llnode(data);
  newNode->next = prev_node->next; //takes the next node after prev_node and sets it as the next node of the new node
  newNode -> prev = prev_node; // takes the new node and sets its previous node as the prev_node
  prev_node -> next = newNode; // sets the next for prev_node as the new node
  newNode->next->prev = newNode;
  dLinkedList -> size++; // increments the size of the list
  return;
}

void insertBefore(DLinkedList* dLinkedList, LLNode* next_node, void* data){
  if (next_node == NULL) {
    printf("the given next node cannot be NULL"); //  checks if the next node is null
    return;
  }
  if (next_node->prev == NULL) {
    LLNode* newNode = create_llnode(data);
    newNode->next = next_node; // Set newNode's next to next_node
    next_node->prev = newNode; // Update next_node's prev to newNode
    dLinkedList->head = newNode; // Update the head of the list
    dLinkedList->size++; // Increment the size of the list
    return;
  }
  LLNode* newNode = create_llnode(data); // Create a new node
  newNode->prev = next_node->prev; // Set newNode's prev to next_node's prev
  newNode->next = next_node; // Set newNode's next to next_node
  next_node->prev->next = newNode; // Update the next pointer of the previous node
  next_node->prev = newNode; // Update next_node's prev to point to newNode
  dLinkedList -> size++; // increments the size of the list
  return;
}

void insertHead(DLinkedList* dLinkedList, void* data){
  if (dLinkedList == NULL) {
    printf("The entered list cannot be NULL"); // checks if the list is null
    return;
  }
  if(dLinkedList->head == NULL){
    LLNode* newNode = create_llnode(data); // creates a new node
    dLinkedList->head = newNode; // sets the head of the list to the new node
    dLinkedList->tail = newNode; // sets the tail of the list to the new node
    dLinkedList->size++;  // increments the size of the list
  } else {
    insertBefore(dLinkedList, dLinkedList->head, data); // inserts the new node before the head of the list
  }
}

void insertTail(DLinkedList* dLinkedList, void* data){
  if (dLinkedList -> tail == NULL) {
    LLNode* newNode = create_llnode(data); // creates a new node
    dLinkedList->head = newNode; // sets the head of the list to the new node
    dLinkedList->tail = newNode; // sets the tail of the list to the new node
    dLinkedList->size++; // increments the size of the list
  } else {
    insertAfter(dLinkedList, dLinkedList->tail, data); // inserts the new node after the tail of the list
  }
}

void deleteNode(DLinkedList* dLinkedList, LLNode* Node){
  if (Node == NULL) {
    printf("The entered node cannot be NULL"); // Checks if the node is null
    return;
  }
  if (Node == dLinkedList->head) {
    if (Node->next == NULL) { // Only node in the list
        dLinkedList->head = NULL;
        dLinkedList->tail = NULL;
    } else {
        dLinkedList->head = Node->next; // Update the head
        Node->next->prev = NULL;
    }
  }
  // Case 2: If Node is the Tail
  else if (Node == dLinkedList->tail) {
    if (Node->prev == NULL) { // Only node in the list
        dLinkedList->head = NULL;
        dLinkedList->tail = NULL;
    } else {
        dLinkedList->tail = Node->prev; // Update the tail
        Node->prev->next = NULL;
    }
}
// Case 3: Node is in the Middle
else {
    Node->prev->next = Node->next;
    Node->next->prev = Node->prev;
}

// Decrease the size of the list
if (dLinkedList->size > 0) {
    dLinkedList->size--;
}

// Free the data if it is dynamically allocated
if (Node->data != NULL) {
    free(Node->data);
    Node->data = NULL; // Set to NULL to avoid dangling pointers
}

// Free the node itself
free(Node);
}
  

void destroyList(DLinkedList* dLinkedList){
  LLNode* current = dLinkedList -> head;
  LLNode *next;
  while (current != NULL) { // Loop through the list
    next = current -> next;
    if (current -> data != NULL) { // Free the data if it is dynamically allocated
      free(current -> data);
    }
    free(current); // Free the node itself
    current = next;
  }
  dLinkedList -> head = NULL; // Sets head to null
  dLinkedList -> tail = NULL; // Sets tail to null
  dLinkedList -> size = 0;  // Sets size to 0
  free(dLinkedList); // Free the list itself
  return;
} 

DLinkedList* split(DLinkedList* dLinkedList, LLNode* Node) {
  if (Node == NULL) {
    printf("The entered node cannot be NULL"); // Checks if the node is null
    return NULL;
  }
  if (Node == dLinkedList -> tail) { // If the node is the tail, we can't split it further
    return NULL;
  }
  DLinkedList* secondList = create_dlinkedlist(); // Create a new list for the second half
  secondList -> head = Node -> next; // Set the head of the second list to the node after the split node
  secondList -> tail = dLinkedList -> tail; // Set the tail of the second list to the tail of the original list
  secondList -> size = 0; // Initialize the size of the second list to 0

  dLinkedList -> tail = Node; // Set the tail of the original list to the split node
  if (Node -> next != NULL) {
    Node -> next -> prev = NULL; // Set the previous pointer of the next node to NULL
  }
  Node -> next = NULL; // Set the next pointer of the split node to NULL
  LLNode* curr = secondList -> head;
  while (curr != NULL) { // Loop through the second list to update the size
    secondList -> size++;
    curr = curr -> next;
  }
  dLinkedList -> size -= secondList -> size; // Updtae the size of the original list by subtracting the size of the second list
  return secondList;
}
