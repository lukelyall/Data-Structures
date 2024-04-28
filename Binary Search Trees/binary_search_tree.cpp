/*
 * binary_search_tree.cpp
 *
 *  Created on: April 27, 2024
 *      Author: Luke Lyall
 * 
 *  Average Time Complexity:
 *      Read: O(log n)
 *      Search: O(log n)
 *      Insert: O(log n)
 *      Delete: O(log n)
 */

#include <iostream>

struct Node {
  int data;
  Node *left; // left child < parent and all left children < root
  Node *right; // right child > parent and all right children > root
};

class BinarySearchTree {
  public:
    BinarySearchTree() {
      root = nullptr;
    }

    void createNode(Node*& temp, int data) {
      temp = new Node;
      temp->data = data;
      temp->left = nullptr;
      temp->right = nullptr;
    }

    void insertNode(Node*& current, int data) {
      if(current == nullptr) {
        createNode(current, data);
      }
      else {
        if(data > current->data) {
          insertNode(current->right, data);
        }
        else {
          insertNode(current->left, data);
        }
      }
    }

    void insert(int data) {
      insertNode(root, data);
    }

    void removeNode(Node*& current, int data) {
      /*
       * Deleting a node
       *  Cases:
       *    1. No child -> assign parent pointer to null
       *    2. Single child -> replace node with child and update pointers
       *    3. Two children -> inorder successor or inorder predecessor
       */

      if (current == nullptr) {
        return;
      }

      if (current->data < data) {
        removeNode(current->right, data);
      }
      else if (current->data > data) {
        removeNode(current->left, data);
      }
      else {
        // case 1: no child
        if (current->left == nullptr && current->right ==nullptr) {
          delete current;
          current = nullptr;
        }
        // case 2: right child
        else if (current->left == nullptr && current->right != nullptr) {
          Node* temp = current;
          current = current->right;
          delete temp;
        }
        // case 2: left child
        else if (current->left != nullptr && current->right == nullptr) {
          Node* temp =current;
          current = current->left;
          delete temp;
        }
        // case 3: two children
        else {
          // inorder successor - smallest node of the right child
          Node* temp = current->right;
          while (temp->left != nullptr) {
            temp = temp->left;
          }
          current->data = temp->data;
          removeNode(current->right, temp->data);

          /*
           * inorder predecessor - largest of the left child
           * Node* temp = current->left;
           * while (temp->right != nullptr) {
           *  temp = temp->right; 
           * }
           * current->data = temp->data;
           * removeNode(current->left, temp->data);
           */

        }
      }
    }

    void remove(int data) {
      removeNode(root, data);
    }

    bool searchForData(Node* current, int data) {
      if (current == nullptr) {
        return false;
      }
      
      if (current->data == data) {
        return true;
      }

      if (data < current->data) {
        return searchForData(current->left, data);
      }
      else {
        return searchForData(current->right, data);
      }
    }

    void search(int data) {
      if (searchForData(root, data)) {
        std::cout << "found: " << data << "\n";
      }
      else {
        std::cout << "could not find: " << data << "\n";
      }
    }

    // nodes in non-descending order; left child -> root -> right child
    void inOrder(Node* current) {
      if (current != nullptr) {
        inOrder(current->left);
        std::cout << " " << current->data << "\n";
        inOrder(current->right);
      }
    }

    void printInOrder() {
      inOrder(root);
    }

    // root -> left child -> right child
    void preOrder(Node* current) {
      if (current != nullptr) {
        std::cout << current->data << "\n";
        preOrder(current->left);
        preOrder(current->right);
      }
    }

    void printPreOrder() {
      preOrder(root);
    }

    // left child -> right child -> root
    void postOrder(Node* current) {
      if(current != nullptr) {
        postOrder(current->left);
        postOrder(current->right);
        std::cout << current->data << "\n";
      }
    }

    void printPostOrder() {
      postOrder(root);
    }

  private:
    Node* root;
};

int main() {
  BinarySearchTree binarysearchtree;

  /*
              10
          5        15
        3   7   12    18
  */

  binarysearchtree.insert(10);
  binarysearchtree.insert(5);
  binarysearchtree.insert(15);
  binarysearchtree.insert(3);
  binarysearchtree.insert(7);
  binarysearchtree.insert(12);
  binarysearchtree.insert(18);

  std::cout << "INODER\n";
  binarysearchtree.printInOrder();
  std::cout << "PREORDER\n";
  binarysearchtree.printPreOrder();
  std::cout << "POSTORDER\n";
  binarysearchtree.printPostOrder();

  std::cout << "------------------\n";
  binarysearchtree.remove(5);
  binarysearchtree.printInOrder();

  binarysearchtree.search(5);
  binarysearchtree.search(10);
  
  return 0;
}