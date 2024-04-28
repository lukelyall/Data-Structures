/*
 * doubly_linked_list.cpp
 *
 *  Created on: April 24, 2024
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
  Node *prev; // what is behind a node
  Node *next; // what is in front of a node
};

class DoublyLinkedList {
  public:
    DoublyLinkedList() {
      head = nullptr;
      tail = nullptr;
    }

    void createNode(int data) {
      Node *temp = new Node;
      temp->data = data;
      temp->prev = nullptr;
      temp->next = nullptr;

      if(head == nullptr) {
        head = temp;
        tail = temp;
      }
      else {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
      }
    }

    void deleteFirstData(int data) {
      Node *current = head;

      while(current != nullptr) {
        if(current->data == data) {
          if(current->prev == nullptr) {
            head = current->next;
            if(head != nullptr) { // update the prev of head
              head->prev = nullptr;
            }
          }
          else {
            current->prev->next = current->next;
            if(current->next != nullptr) { // update the prev of next
              current->next->prev = current->prev;
            }
          }
          delete current;
          return;
        }
        current = current->next;
      }
    }

    void printLinkedList() {
      Node *current = head;

      while(current != nullptr) {
        std::cout << "prev: " << current->prev << "\n";
        std::cout << "data: " << current->data << "\n";
        std::cout << "next: " << current->next << "\n\n";

        current = current->next;
      }
    }

  private:
    Node* tail;
    Node* head;
};

int main() {
  DoublyLinkedList doublylinkedlist;

  doublylinkedlist.createNode(15);
  doublylinkedlist.createNode(22);
  doublylinkedlist.createNode(19);

  doublylinkedlist.deleteFirstData(22);

  doublylinkedlist.printLinkedList();

  return 0;
}