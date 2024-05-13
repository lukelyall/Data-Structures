/*
 * red_black_tree.cpp
 *
 *  Updated on: May 13. 2024
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

/*
 * red black tree properties:
 *  1. root is black
 *  2. every leaf is either red or black
 *  3. children of a red node are black
 *  4. all leaves have the same black depth
 *  5. path from root to descendant leaf node contains same number black nodes
 * 
 * red black tree rules:
 *  1. node is either red or black
 *  2. root is always black
 *  3. no two adjacent red nodes (red node cannot have a red parent or red child)
 *  4. every path from a node to any descendants null nodes have same number black nodes
 *  4. every leaf or null node must be black
 */

struct Node {
  int data;
  int color; // red or black
  Node* left; // left child
  Node* right; // right child
};

class RedBlackTree {
  public:
    RedBlackTree() {
      root = nullptr;
    }

    void createNode(Node*& temp, int data) {
      temp = new Node;
      temp->data = data;
      temp->color = 1; // default to red and update if necessary
      temp->left = nullptr;
      temp->right = nullptr;
    }
    
    // TODO: fix recoloring and rotation of tree after deletion

    void deleteNode(Node*& current, int data) {
      if (current == nullptr) {
        return;
      }  
      if (current->data < data) {
        deleteNode(current->right, data);
      }
      else if (current->data > data) {
        deleteNode(current->left, data);
      }
      else {
        // cases:
        //   no children: delete node
        //   one child: replace node with child
        //   two children: replace node with inorder successor (leftmost of right subtree)
        
        // no children case
        if (current->left == nullptr && current->right == nullptr) {
          delete current;
          current = nullptr;
        }
        else if (current->left != nullptr && current->right != nullptr) {
          Node* successor = findInOrderSuccessor(current);
          current->data = successor->data;
          deleteNode(current->right, successor->data);
        }
        else {
          Node* child = nullptr;
          if (current->left != nullptr) {
            child = current->left;
          }
          else {
            child = current->right;
          }
          delete current;
          current = child;
        }
      }
    }

    void deleteByData(int data) {
      deleteNode(root, data);
    }

    Node* findInOrderSuccessor(Node*& current) {
      if (current == nullptr) {
        return nullptr;
      }
      
      if (current->right != nullptr) {
        current = current->right;
        while (current->left != nullptr) {
          current = current->left;
        }
        return current;
      }
      else {
        return nullptr;
      }
    }

    void fixTree(Node*& current) {
      // fix tree after a delete

      // root case
      if (current == root) {
        current->color = 0;
        return;
      }

      Node* parent = findParent(current);
      Node* sibling = findSibling(current);

      if (sibling != nullptr && sibling->color == 1) {
        parent->color = 1;
        sibling->color = 0;
        if (current == parent->left) {
          Node* grandfather = findGrandfather(current);
          rightRotation(sibling, parent, grandfather);
        }
        else {
          Node* grandfather = findGrandfather(current);
          leftRotation(sibling, parent, grandfather);
        }
      }

      if (parent->color == 0 && (sibling == nullptr || sibling->color == 0)) {
        if (sibling != nullptr) {
          sibling->color = 1;
        }
        fixTree(parent);
        return;
      }

      if (parent->color == 1 && (sibling == nullptr || sibling->color == 0)) {
        if (sibling != nullptr) {
          sibling->color = 1;
        }
        parent->color = 0;
        return;
      } 

      if (current == parent->left && (sibling->left != nullptr && sibling->left->color == 1) && (sibling->right == nullptr || sibling->right->color == 0)) {
        sibling->color = 1;
        sibling->left->color = 0;
        rightRotation(sibling->left, sibling, parent);
      } 
      else if (current == parent->right && (sibling->right != nullptr && sibling->right->color == 1) && (sibling->left == nullptr || sibling->left->color == 0)) {
        sibling->color = 1;
        sibling->right->color = 0;
        leftRotation(sibling->right, sibling, parent);
      }

      if (current == parent->left && sibling->right != nullptr && sibling->right->color == 1) {
        sibling->color = parent->color;
        parent->color = 0;
        sibling->right->color = 0;
        Node* grandfather = findGrandfather(current);
        leftRotation(sibling, parent, grandfather);
      } 
      else if (current == parent->right && sibling->left != nullptr && sibling->left->color == 1) {
        sibling->color = parent->color;
        parent->color = 0;
        sibling->left->color = 0;
        Node* grandfather = findGrandfather(current);
        rightRotation(sibling, parent, grandfather);
      }

    }

    Node* findSibling(Node*& current) {
      if (current == nullptr) {
        return nullptr;
      }
      Node* parent = findParent(current);
      Node* sibling = nullptr;
      if (parent->left == current) {
        sibling = parent->right;
        return sibling;
      }
      else {
        sibling = parent->left;
        return sibling;
      }
    }
    
    void insertNode(Node*& current, int data) {
      // insert same as a bst but call functions for recoloring and rotation
      if(current == nullptr) {
        createNode(current, data);
        if (current == root) {
          current->color = 0;
        }
        else {
          recolor(current);
        }
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

    void recolor(Node*& current) {
      if(current == root) {
        current->color = 0;
      }

      /*
       * check if parent is red or black
       * if black parent keep child red
       * if red parent check the color of the uncle
       *   if the uncle is red change parent and uncle to black, grandfather to red
       *   unless grandfather is root
       *   if uncle is black 4 cases:
       *     1. ll rotation
       *     2. lr rotation
       *     3. rr rotation
       *     4. rl rotation
       */

      else if(current != root) {
        Node* parent = findParent(current);
        if (parent == nullptr && parent->color == 0) {
          return;
        }
        else if (parent->color == 1) {
          Node* uncle = findUncle(parent);
          if (uncle != nullptr && uncle->color == 1) {
            parent->color = 0;
            uncle->color = 0;
            Node* grandfather = findGrandfather(parent);
            if (grandfather != nullptr && grandfather != root) {
              grandfather->color = 1;
              recolor(grandfather);
            }
            else {
              return;
            }
          }
          else if (uncle != nullptr && uncle->color == 0) {
            /* 
             * rotations
             * ll rotation:
             *  1. right rotation of grandfather
             *  2. swap the colors of grandfather and parent
             * lr rotation:
             *  1. left rotate parent
             *  2. Apply ll rotation case
             * rr rotation:
             *  1. left rotation of grandfather
             *  2. Then swap the colours of grandfather and parent
             * rl rotation:
             *  1. Right rotate parent
             *  2. Now apply rr rotation case.
             */
            Node* uncle = findUncle(parent);
            Node* grandfather = findGrandfather(parent);
            if (grandfather->left == parent) {
              if (parent->left == current) {
                rightRotation(current, parent, grandfather);
                int prevColor = parent->color;
                parent->color = grandfather->color;
                grandfather->color = prevColor;
              }
              else {
                parent = findParent(grandfather);
                leftRotation(parent, grandfather, parent);
                rightRotation(current, parent, grandfather);
                int prevColor = current->color;
                current->color = grandfather->color;
                grandfather->color = prevColor;
              }
            }
            else {
              if (parent->right == current) {
                leftRotation(current, parent, grandfather);
                int prevColor = parent->color;
                parent->color = grandfather->color;
                grandfather->color = prevColor;
              }
              else {
                parent = findParent(grandfather);
                rightRotation(parent, grandfather, parent);
                leftRotation(current, parent, grandfather);
                int prevColor = current->color;
                current->color = grandfather->color;
                grandfather->color = prevColor;
              }
            }
          }
        }
      }
    }

    void leftRotation(Node*& current, Node*& parent, Node*& grandparent) {
      // chosen child swaps places with its parent while keeping its right child
      // the left child is switched to be the original parent node
      // the child nodes old left child becomes the right child of the original parent node
      if (grandparent == nullptr) {
        std::cout << "LEFT ROTATION ERROR: grandparent does not exist\n";
        return;
      }
      
      Node* temp = parent->right;
      parent->right = current->left;
      current->left = parent;
      parent = temp;

      if (grandparent->left == current) {
        grandparent->left = temp;
      }
      else {
        grandparent->right = temp;
      }
    }

    void rightRotation(Node*& current, Node*& parent, Node*& grandparent) {
      // chosen child swaps places with its parent while keeping its left child
      // the right child is switched to the original parent node
      // the chld nodes old right child becomes the left child of the original parent node
      if (grandparent == nullptr) {
        std::cout << "RIGHT ROTATION ERROR: grandparent does not exist\n";
        return;
      }
      
      Node* temp = parent->left;
      parent->left = current->right;
      current->right = parent;
      parent = temp;

      if (grandparent->left == current) {
        grandparent->left = temp;
      }
      else {
        grandparent->right = temp;
      }

    }

    Node* findParent(Node*& child) {
      if (root == nullptr || root == child) {
        return nullptr;
      }

      Node* current = root;
      Node* parent = nullptr;

      while (current != nullptr) {
        if (child->data > current->data) {
          parent = current;
          current = current->right;
        }
        else if (child->data < current->data) {
          parent = current;
          current = current->left;
        } 
        else {
          return parent;
        }
      }

      return nullptr;
    }

    Node* findUncle(Node*& parent) {
      if (parent == nullptr) {
        return nullptr;
      }

      Node* grandparent = findGrandfather(parent);
      if (grandparent == nullptr) {
        return nullptr;
      }

      if (grandparent->left == parent) {
        return grandparent->right;
      }
      else {
        return grandparent->left;
      }
    }

    Node* findGrandfather(Node*& parent) { 
      if (parent == nullptr || parent == root) {
        return nullptr;
      }

      Node* current = root;
      Node* grandfather = nullptr;

      while (current != nullptr) {
        if(current->left == parent || current->right == parent) {
          grandfather = current;
          return grandfather;
        }
        else {
          if(parent->data > current->data) {
            current = current->right;
          }
          else if (parent->data < current->data) {
            current = current->left;
          }
        }
      }

      return nullptr;
    }

    void printInOrder(Node* node) {
      if (node == nullptr) {
        return;
      }
      printInOrder(node->left);
      std::cout << node->data << ":" << node->color << "\n";
      printInOrder(node->right);  
    }

    void printInOrderTree() {
      printInOrder(root);
    }

  private:
    Node* root;
};

int main() {
  RedBlackTree redblacktree;

  redblacktree.insert(10);
  redblacktree.insert(5);
  redblacktree.insert(15);
  redblacktree.insert(2);
  redblacktree.insert(7);
  redblacktree.insert(6);
  redblacktree.insert(8);

  // redblacktree.deleteByData(2);

  redblacktree.printInOrderTree();

  return 0;
}