// LinkedList Node class
#ifndef NODE_
#define NODE_

template <class T>
class Node
{
private:
   T             data; // A data item
   Node<T>*      next; // Pointer to next node
   
public:
   Node();  // Default Constructor
   Node(const T& aData);  // Overloaded constructor
   Node(const T& aData, Node<T>* nextNodePtr); // Overloaded constructor
   void setItem(const T& aData);  // Set data
   void setNext(Node<T>* nextNodePtr); // Set next node pointer
   T getItem() const ;    // get data
   Node<T>* getNext() const ;  // get next node pointer
}; // end Node

#endif
