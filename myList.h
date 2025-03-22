#ifndef MYLIST_
#define MYLIST_
#include "node.h"

#include <iostream>
using namespace std;

template <class T>
class myList {
 private:
   int size;
   node<T> * head;
  public:
    myList() 
    { head = nullptr; size=0;  } 
    ~myList(); 
    void insert (T item);
    bool find (T item, long long int & compare);
    void remove();
    T front();
    int getSize() { return size;}
    bool isEmpty() { return size==0;}
    void print();
};

template <class T>
void myList<T>:: insert (T item) {

  //first create a new node object with the item
  node<T> * tmp = new node<T>(item);
  tmp->next = head;
  head = tmp;
  size++;
}
template <class T>
bool myList<T>:: find (T item, long long int & compare) {

  //so search through the list and see if it exists
  //if yes, return true
  node<T> * current = head;
  while (current != nullptr) {
      compare++;
      if (current->data.compare(item) == 0) {
          return true;
      }
      current = current->next;
  }
  //if we search the entire list and don't find it
  return false;
}

template <class T>
void myList<T>:: remove() {
  node <T> * tmp;

  if (head != nullptr)  {
    //something in the list.  move to the next node.
    node<T> * tmp = head;
    head = head->next;
    delete tmp;
    size--;

    //decrement size
    size--;
  }
}

template <class T>
myList<T>:: ~myList() {

 while(!isEmpty())
   remove(); 
}

template <class T>
T myList<T>:: front () {
  if (head != nullptr) {
	return head->data;
  } else {
	return T(0);  //return the zero case here.
  }
}

template <class T>
void myList<T>::print() {
  for (node<T> * tmp = head; tmp != nullptr; tmp = tmp->next) {
    cout << tmp->data;
    if (tmp->next != nullptr)
      cout << " -> ";
    else
      cout << " /\n";
  }
}
#endif
