/*
 * linked_list.cpp
 *
 *  Updated on: May 5, 2024
 *  Created on: May 4, 2024
 *      Author: Luke Lyall
 * 
 *  Average Time Complexity:
 *      Read: O(n)
 *      Search: O(n)
 *      Insert: O(1)
 *      Delete: O(1)
 */

#include <iostream>

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

    void insertHead(int data) {
      Node *temp = new Node;
      temp->data = data;
      temp->next = nullptr;

      Node *previous_head = head;
      temp->next = previous_head;
      head = temp;
    }

    void removeDuplicates(int data) {
      Node *current = head;
      Node *previous = head;
      int repeats = 0;

      while(current != nullptr) {
        if(current->data == data) {
          repeats++;
          if(repeats > 1) {
            Node* temp = current;
            current = previous;
            previous->next = temp->next;
            delete temp;
          }
        }
        previous = current;
        current = current->next;
      }
      std::cout << "found " << repeats -1 << " repeats\n";
    }

    void deleteLastNode() {
      if (isEmpty()) { // empty list
        std::cout << "empty linked list\n";
        return;
      }

      if (head == tail) { // a single node
        delete head;
        head = nullptr;
        tail = nullptr;
        return;
      }

      Node *old_tail = tail;
      Node *previous = head;

      while(previous->next != nullptr) {
        previous = previous->next;
      }

      delete old_tail;
      previous->next = nullptr;
      tail = previous;
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

    bool isEmpty() {
      if(head == nullptr) {
        return true;
      }
      else {
        return false;
      }
    }

    void getLength() {
      int length = 0;
      Node *current = head;
      
      while(current != nullptr) {
        length++;
        current = current->next;
      }
      std::cout << "length: " << length << "\n";
    }

    void searchLinkedList(int data) {
      Node *current = head;

      while(current != nullptr){
        if(current->data == data) {
          std::cout << "found: "<< data << "\n"; 
          return;
        }
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

    void reverse() {
      Node *current = head;
      Node *previous = nullptr;
      Node *next = nullptr;

      while(current != nullptr) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
      }
      head = previous;
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
  linkedlist.createNode(19);
  linkedlist.createNode(19);
  linkedlist.createNode(19);

  linkedlist.insertHead(25);
  linkedlist.deleteFirstData(22);

  linkedlist.removeDuplicates(19);
  linkedlist.searchLinkedList(15);
  linkedlist.getLength();
  linkedlist.printLinkedList();
  linkedlist.reverse();
  linkedlist.printLinkedList();

  return 0;
}