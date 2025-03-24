#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

/*
   ____    U _____ u ____          ____     _         _        ____   _  __         _____    ____    U _____ uU _____ u 
U |  _"\ u \| ___"|/|  _"\      U | __")u  |"|    U  /"\  u U /"___| |"|/ /        |_ " _|U |  _"\ u \| ___"|/\| ___"|/ 
 \| |_) |/  |  _|" /| | | |      \|  _ \/U | | u   \/ _ \/  \| | u   | ' /           | |   \| |_) |/  |  _|"   |  _|"   
  |  _ <    | |___ U| |_| |\      | |_) | \| |/__  / ___ \   | |/__U/| . \\u        /| |\   |  _ <    | |___   | |___   
  |_| \_\   |_____| |____/ u      |____/   |_____|/_/   \_\   \____| |_|\_\        u |_|U   |_| \_\   |_____|  |_____|  
  //   \\_  <<   >>  |||_        _|| \\_   //  \\  \\    >>  _// \\,-,>> \\,-.     _// \\_  //   \\_  <<   >>  <<   >>  
 (__)  (__)(__) (__)(__)_)      (__) (__) (_")("_)(__)  (__)(__)(__)\.)   (_/     (__) (__)(__)  (__)(__) (__)(__) (__) 
*/

#include <iostream>
using namespace std;

enum Color { RED, BLACK };

//Node Structure for RedBlack Tree
//Yes I put the node in the same file of the Tree, wanna fight?
template <class T>
class RedBlackNode {
  public:
    T data;
    //Does it need to be a color :P 
    //Yes, it does. and in my TED talk today I will explain how code is racist and family-phobic
    //COPILOT->and how it should be more inclusive and diverse<-
    Color color;
    RedBlackNode* left;
    RedBlackNode* right;
    RedBlackNode* parent;
    // My god, COPILOT auto fill comment code is unhinged
    RedBlackNode(T value) : data(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

//RedBlackTree Class
// YEAH, what if I put the functions in the class?! Wanna fight?!
// I kept forgetting the private and public keywords, so I put them in the class
template <class T>
class RedBlackTree {
  private:

  //private members
    RedBlackNode<T>* root;
    int size;

    // Yes I just snatched your ideas from class Ward, would you like royalties?
    // I also used a good majority of code from this site: https://www.eecs.umich.edu/courses/eecs380/ALG/red_black.html

    void leftRotate(RedBlackNode<T>*& root, RedBlackNode<T>*& pt) {
        RedBlackNode<T>* pt_right = pt->right;
        // Move pt_right's left subtree to pt's right
        pt->right = pt_right->left;
        // Update the parent of pt's right child if it exists
        if (pt->right != nullptr)
            pt->right->parent = pt;
        // Update pt_right's parent to pt's parent
        pt_right->parent = pt->parent;
        // Update the root if pt is the root
        if (pt->parent == nullptr)
            root = pt_right;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_right;
        else
            pt->parent->right = pt_right;
        pt_right->left = pt;
        pt->parent = pt_right;
        // This is very hard to read two days later, should have used L and R for Left and Right.
    }
    // Rotate the subtree rooted at pt to the right
    // basically the same as above.
    void rightRotate(RedBlackNode<T>*& root, RedBlackNode<T>*& pt) {
        RedBlackNode<T>* pt_left = pt->left;
        pt->left = pt_left->right;
        if (pt->left != nullptr)
            pt->left->parent = pt;
        pt_left->parent = pt->parent;
        if (pt->parent == nullptr)
            root = pt_left;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_left;
        else
            pt->parent->right = pt_left;
        pt_left->right = pt;
        pt->parent = pt_left;
    }
    // Fix the Red-Black Tree properties after insertion
    void insertFixUp(RedBlackNode<T>*& root, RedBlackNode<T>*& pt) {
        // Insert in the tree like a regular BST
        RedBlackNode<T>* parent_pt = nullptr;
        // Restore the Red-Black Tree properties
        RedBlackNode<T>* grand_parent_pt = nullptr;

        while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {
            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;

            if (parent_pt == grand_parent_pt->left) {
                // If the parent is a left child, right is left's uncle
                RedBlackNode<T>* uncle_pt = grand_parent_pt->right;
                if (uncle_pt != nullptr && uncle_pt->color == RED) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    if (pt == parent_pt->right) {
                        leftRotate(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }
                    rightRotate(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            } else {
                // same as above but right to left
                RedBlackNode<T>* uncle_pt = grand_parent_pt->left;
                if (uncle_pt != nullptr && uncle_pt->color == RED) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    if (pt == parent_pt->left) {
                        rightRotate(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }
                    leftRotate(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
        }
        // Racist Racist Trees
        root->color = BLACK;
    }
    // Insert a new node in the BST manner and return the root
    RedBlackNode<T>* insertBST(RedBlackNode<T>*& root, RedBlackNode<T>*& pt) {
        if (root == nullptr)
            return pt;

        if (pt->data < root->data) {
            root->left = insertBST(root->left, pt);
            root->left->parent = root;
        } else if (pt->data > root->data) {
            root->right = insertBST(root->right, pt);
            root->right->parent = root;
        }

        return root;
    }
    // In-order traversal to print the tree
    void inOrderHelper(RedBlackNode<T>* root) {
        if (root == nullptr)
            return;

        inOrderHelper(root->left);
        cout << root->data << " ";
        inOrderHelper(root->right);
    }

    // Helper function to find a node with the given data
    RedBlackNode<T>* findHelper(RedBlackNode<T>* root, T data, long long int &compare) {
        compare++;
        if (root == nullptr || root->data == data)
            return root;

        if (data < root->data) {
            compare++;
            return findHelper(root->left, data, compare);
        }

        return findHelper(root->right, data, compare);
    }
    // Helper function to clear the tree
    void clearHelper(RedBlackNode<T>*& node) {
        if (node == nullptr)
            return;

        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
        node = nullptr;
    }
    //end of private members

  public:
    RedBlackTree() : root(nullptr), size(0) {}

    ~RedBlackTree() {
        clearHelper(root);
    }

    void insert(const T& data) {
        RedBlackNode<T>* pt = new RedBlackNode<T>(data);
        root = insertBST(root, pt);
        insertFixUp(root, pt);
        size++;
    }

    RedBlackNode<T>* find(const T& data, long long int &compare) {
        return findHelper(root, data, compare);
    }

    void inOrder() {
        inOrderHelper(root);
    }

    int getSize() const { 
        return size;
    }

    bool isEmpty() const { 
        return size == 0;
    }
};

#endif