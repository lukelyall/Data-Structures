# Doubly Linked Lists

## Average Time Complexity
- Read: O(n)
- Search: O(n)
- Insert: O(1)
- Delete: O(1)

## Implementation
A doubly linked list is similar to a singly linked list but instead of containing a node with just a data value and next pointer, it contains a data value, next pointer, and previous pointer. If you have not looked at my implementation of a singly linked list and are confused, I would suggest starting there. The previous pointer allows each node to keep track of what is behind it not just what is in front of it.

###  Linked List Declaration
``` C++
struct Node {
  int data; // any data type can be added
  Node *prev; // what is behind a node
  Node *next; // what is in front of a node
};
```
The definition of a node is almost identical to that of a singly linked list but with a previous pointer. When implementing a doubly linked list, it is important to be aware of the previous pointer and to make sure that it properly connects the list.

### Creating a Node
``` C++
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
```
This createNode function works in the same way as a singly linked list but with the previous pointer. The temporary node assigns the previous pointer to nullptr and updates the previous pointer to the tail if a head exists. If a head does not exist then the previous pointer can stay as nullptr.