#ifndef NODE_
#define NODE_
using namespace std;

template <class T>
class node {
  public:
    T  data;
    node<T> * next;
    node() { next = nullptr;}
    node(T item) {
      data = item;
      next = nullptr;
    }
};

#endif