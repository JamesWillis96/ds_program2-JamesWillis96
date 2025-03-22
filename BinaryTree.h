#ifndef BINARYTREE_
#define BINARYTREE_
#include "BinaryNode.h"

#include <iostream>
using namespace std;

template <class T>
class BinarySearchTree {
  private:
    BinaryNode<T> * root;
    int size;
 
    BinaryNode<T> *find (T item, BinaryNode<T> *t) ;
    bool insert(T item, BinaryNode<T> *&t) ;
    void remove (T item, BinaryNode<T> *&t);
 
    void clear(BinaryNode<T> *& t) ;
 
 
  public:
    BinarySearchTree() { root =nullptr; size=0;  }  //end constructor
    ~BinarySearchTree() { clear(root); }

    BinaryNode<T> * find(T item) {
      return find (item, root);
    }

    bool insert (T item);
    BinaryNode<T> *findMax (BinaryNode<T> *t) ;
    BinaryNode<T> *findMin (BinaryNode<T> *t) ;

    int getSize() { return size;}
    int isEmpty() { return size ==0;}
};


template <class T>
BinaryNode<T> * BinarySearchTree<T>:: find (T item,  BinaryNode<T> *t) {
  //so what code goes here?

  //this return is left only for compiler reason, you should remove it.
    return nullptr;
}

template <class T>
bool BinarySearchTree<T>:: insert (T item) {

  bool inserted = insert(item, root);
  if (inserted) size++;  
  return inserted;
}

template <class T>
bool BinarySearchTree<T>:: insert (T item, BinaryNode<T> *&t) {
  //so what goes here?

    return false;   
}


template <class T>
void BinarySearchTree<T>:: clear(BinaryNode<T> *& t) {

  if (t == nullptr) 
    return;
  else {
    clear(t->left);
    clear(t->right);
    delete(t);
    t = nullptr;
  }
}

template <class T>
BinaryNode<T> * BinarySearchTree<T>::findMin (BinaryNode<T> *t) {
      if ( t == nullptr )
            return nullptr;
      else if ( t -> left == nullptr )
            return t;
      return findMin (t -> left);
}

template <class T>
BinaryNode<T>* BinarySearchTree<T>::findMax (BinaryNode<T> *t) {
      if ( t == nullptr )
            return nullptr;
      else if ( t -> right == nullptr )
            return t;
      return findMax (t ->right);
}

template <class T>
void BinarySearchTree<T>::remove (T item, BinaryNode<T> *&t) {
  if ( t == nullptr) return;   // Item not found; do nothing

  //so what is the rest of the code?
}


#endif