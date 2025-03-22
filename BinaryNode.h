#ifndef BINARYNODE_
#define BINARYNODE_
using namespace std;

template <class T>
class BinaryNode {
  public:
    T  data;
    BinaryNode<T> * left;
    BinaryNode<T> * right;
    BinaryNode() { left= nullptr; right=nullptr; data=T(0);}
    BinaryNode(T item) {
      data = item;
      left = nullptr;
      right = nullptr;
    }
};

#endif