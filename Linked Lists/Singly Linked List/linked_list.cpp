#include <iostream>

/*
 * linked_list.cpp
 *
 *  Created on: May 4, 2024
 *      Author: Luke Lyall
 * 
 *  Average Time Complexity:
 *      Read: O(n)
 *      Search: O(n)
 *      Insert: O(1)
 *      Delete: O(1)
 */

struct Node {
  int data; // any data type can be added
  struct Node *next; // what a node points to
};

class LinkedList {
  public:
    LinkedList() {
      head = nullptr;
      tail = nullptr;
    }

    void createNode(int data) {
      Node *temp = new Node;
      temp->data = data;
      temp->next = nullptr;

      if (head == nullptr){
        head = temp;
        tail = temp;
      }
      else {
        tail->next = temp;
        tail = temp;
      }
    }

    void deleteFirstData(int data) {
      Node *current = head;
      Node *previous = head;

      while(current != nullptr) {
        if(current->data == data) {
          if(previous == nullptr) { // check if deleting the first node
            head = current->next;
          }
          else {
            previous->next = current->next;
          }
          delete current;
          return; // exit function
        }
        previous = current;
        current = current->next;
      }
    }

    void printLinkedList() {
      Node *current = head;

      while(current != nullptr) {
        std::cout << current->data << "\n";
        std::cout << current->next << "\n\n";
        current = current -> next;
      }
    }

  private:
    Node* head;
    Node* tail;
};

int main() {
  LinkedList linkedlist;

  linkedlist.createNode(15);
  linkedlist.createNode(22);
  linkedlist.createNode(19);

  linkedlist.deleteFirstData(22);

  linkedlist.printLinkedList();

  return 0;
}