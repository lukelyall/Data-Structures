# Singly Linked Lists

## Average Time Complexity
- Read: O(n)
- Search: O(n)
- Insert: O(1)
- Delete: O(1)

## Implementation
A linked list is used to store elements such as ints, doubles, strings, etc. Every element of a linked list is stored as a node with a data value and next pointer. The data value is used to store the value of the element and the next pointer connects the nodes together by pointing to the next node in the list. The first node in a linked list is called the head and the last node in a linked list is called the tail. The tail node's pointer will always point to NULL or nullptr indicating that the list is over.

### Linked List Declaration
In C++, a linked list can be implemented with the following:
``` C++
struct Node {
  int data; // any data type can be added
  struct Node *next; // what a node points to
};
```
This definition will be used to create every node in the linked list because as previously mentioned every node has a data value and next pointer. The line: `struct Node *next` is a self-referencing pointer meaning it will point to a part of the struct Node.

### Creating a Node
``` C++
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
```
This createNode function takes in an element value and creates a temporary node containing that value and pointing to null. Before assigning the next pointer, it has to be determined whether or not there is anything in the linked list, if not then the newly created node becomes the head and tail of the linked list. If there is already a node in the linked list then the current tail's next pointer is assigned to temp and the temp node becomes the new tail.

### Printing the Linked List
``` C++
void printLinkedList() {
      Node *current = head;

      while(current != nullptr) {
        std::cout << current->data << "\n";
        std::cout << current->next << "\n\n";
        current = current -> next;
      }
    }
```
The above implementation simply sets the current pointer to head and loops through the list until it becomes a nullptr meaning there is nothing more to the list.