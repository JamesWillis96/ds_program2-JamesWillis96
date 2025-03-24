#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>
using namespace std;

enum Color { RED, BLACK };

template <class T>
class RedBlackNode {
  public:
    T data;
    Color color;
    RedBlackNode* left;
    RedBlackNode* right;
    RedBlackNode* parent;

    RedBlackNode(T value) : data(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <class T>
class RedBlackTree {
  private:
    RedBlackNode<T>* root;
    int size;

    void leftRotate(RedBlackNode<T>*& root, RedBlackNode<T>*& pt) {
        RedBlackNode<T>* pt_right = pt->right;
        pt->right = pt_right->left;
        if (pt->right != nullptr)
            pt->right->parent = pt;
        pt_right->parent = pt->parent;
        if (pt->parent == nullptr)
            root = pt_right;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_right;
        else
            pt->parent->right = pt_right;
        pt_right->left = pt;
        pt->parent = pt_right;
    }

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

    void insertFixUp(RedBlackNode<T>*& root, RedBlackNode<T>*& pt) {
        RedBlackNode<T>* parent_pt = nullptr;
        RedBlackNode<T>* grand_parent_pt = nullptr;

        while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {
            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;

            if (parent_pt == grand_parent_pt->left) {
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
        root->color = BLACK;
    }

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

    void inOrderHelper(RedBlackNode<T>* root) {
        if (root == nullptr)
            return;

        inOrderHelper(root->left);
        cout << root->data << " ";
        inOrderHelper(root->right);
    }

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

    void clearHelper(RedBlackNode<T>*& node) {
        if (node == nullptr)
            return;

        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
        node = nullptr;
    }

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