#ifndef LINKED_BAG_
#define LINKED_BAG_

#include "BagInterface.h"
#include "Node.cpp"

using namespace std;

template <class T>
class LinkedBag : public BagInterface<T>
{
private:
   Node<T>* headPtr;           // Pointer to first node
   int itemCount;           // Current count of bag items
   
   // Returns either a pointer to the node containing a given entry
   // or the null pointer if the entry is not in the bag.
   Node<T>* getPointerTo(const T& target) const;
   
public:
   LinkedBag();     // Default constructor
   LinkedBag(const LinkedBag& aBag); // Copy constructor
   virtual ~LinkedBag();                       // Destructor should be virtual
   int getCurrentSize() const;
   bool isEmpty() const;
   bool add(const T& newEntry);   // Adds to the begining of the list
   bool remove(const T& anEntry);
   void clear();
   bool contains(const T& anEntry) const;
   int getFrequencyOf(const T& anEntry) const;
   vector<T> toVector() const;
   T getAt(const unsigned& pos) const;    // Gets the value at the given position
   void setAt(const T& value, const unsigned& pos);   // Sets the value at the given position
   bool insert(const T& value, const int& pos);	// Inserts a node at the given position
   void push_back(const T& value);    // Adds the value at the end of the list
   void pop_front();    // Removes the first element in the list
   void pop_back();     // Removes the last element in the list
   LinkedBag<T> reverse() const;   // Reverse the given list
}; // end LinkedBag

#endif
