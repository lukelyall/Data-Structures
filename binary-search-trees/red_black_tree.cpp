/*
 * red_black_tree.cpp
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
  int color;
  Node* left;
  Node* right;
};

class RedBlackTree {
  public:
    RedBlackTree() {
      root = nullptr;
    }

  private:
    Node* root;
};

int main() {
  RedBlackTree redblacktree;

  return 0;
}