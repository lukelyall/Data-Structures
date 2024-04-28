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

  binarysearchtree.printInOrder();

  return 0;
}