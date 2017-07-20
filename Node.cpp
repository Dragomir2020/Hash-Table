#include "Node.h"

template<class T>
Node<T>::Node() : next(nullptr)
{
} // end default constructor

template<class T>
Node<T>::Node(const T& aData) : data(aData), next(nullptr)
{
} // end constructor

template<class T>
Node<T>::Node(const T& aData, Node* nextNodePtr) :
                data(aData), next(nextNodePtr)
{
} // end constructor

template<class T>
void Node<T>::setItem(const T& aData)
{
   data = aData;
} // end setItem

template<class T>
void Node<T>::setNext(Node* nextNodePtr)
{
   next = nextNodePtr;
} // end setNext

template<class T>
T Node<T>::getItem() const
{
   return data;
} // end getItem

template<class T>
Node<T>* Node<T>::getNext() const
{
   return next;
} // end getNext
