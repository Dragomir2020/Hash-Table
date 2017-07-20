//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT bag: Link-based implementation.
    @file LinkedBag.cpp */

#include "LinkedBag.h"
#include "Node.h"
#include <cstddef>
#include <stdexcept>

template<class T>
LinkedBag<T>::LinkedBag() : headPtr(NULL), itemCount(0)
{
}  // end default constructor

template<class T>
LinkedBag<T>::LinkedBag(const LinkedBag& aBag)
{
	itemCount = aBag.itemCount;
   Node<T>* origChainPtr = aBag.headPtr;  // Points to nodes in original chain
   
   if (origChainPtr == NULL)
      headPtr = NULL;  // Original bag is empty
   else
   {
      // Copy first node
      headPtr = new Node<T>();
      headPtr->setItem(origChainPtr->getItem());
      
      // Copy remaining nodes
      Node<T>* newChainPtr = headPtr;      // Points to last node in new chain
      origChainPtr = origChainPtr->getNext();     // Advance original-chain pointer
      
      while (origChainPtr != NULL)
      {
         // Get next item from original chain
         T nextItem = origChainPtr->getItem();
              
         // Create a new node containing the next item
         Node<T>* newNodePtr = new Node<T>(nextItem);
         
         // Link new node to end of new chain
         newChainPtr->setNext(newNodePtr);
         
         // Advance pointer to new last node
         newChainPtr = newChainPtr->getNext();

         // Advance original-chain pointer
         origChainPtr = origChainPtr->getNext();
      }  // end while
      
      newChainPtr->setNext(NULL);              // Flag end of chain
   }  // end if
}  // end copy constructor

template<class T>
LinkedBag<T>::~LinkedBag()
{
   clear();
}  // end destructor

template<class T>
bool LinkedBag<T>::isEmpty() const
{
	return itemCount == 0;
}  // end isEmpty

template<class T>
int LinkedBag<T>::getCurrentSize() const
{
	return itemCount;
}  // end getCurrentSize

template<class T>
bool LinkedBag<T>::add(const T& newEntry)
{
   // Add to beginning of chain: new node references rest of chain;
   // (headPtr is null if chain is empty)        
   Node<T>* nextNodePtr = new Node<T>();
   nextNodePtr->setItem(newEntry);
   nextNodePtr->setNext(headPtr);  // New node points to chain
//   Node<T>* nextNodePtr = new Node<T>(newEntry, headPtr); // alternate code

   headPtr = nextNodePtr;          // New node is now first node
   itemCount++;
   
   return true;
}  // end add

template<class T>
vector<T> LinkedBag<T>::toVector() const
{
   vector<T> bagContents;
   Node<T>* curPtr = headPtr;
   int counter = 0;
	while ((curPtr != NULL) && (counter < itemCount))
   {
		bagContents.push_back(curPtr->getItem());
      curPtr = curPtr->getNext();
      counter++;
   }  // end while
   
   return bagContents;
}  // end toVector

template<class T>
bool LinkedBag<T>::remove(const T& anEntry)
{
   Node<T>* entryNodePtr = getPointerTo(anEntry);
   bool canRemoveItem = !isEmpty() && (entryNodePtr != NULL);
   if (canRemoveItem)
   {
      // Copy data from first node to located node
      entryNodePtr->setItem(headPtr->getItem());
      
      // Delete first node
      Node<T>* nodeToDeletePtr = headPtr;
      headPtr = headPtr->getNext();
      
      // Return node to the system
      nodeToDeletePtr->setNext(NULL);
      delete nodeToDeletePtr;
      nodeToDeletePtr = NULL;
      
      itemCount--;
   } // end if
   
	return canRemoveItem;
}  // end remove

template<class T>
void LinkedBag<T>::clear()
{
   Node<T>* nodeToDeletePtr = headPtr;
   while (headPtr != NULL)
   {
      headPtr = headPtr->getNext();

      // Return node to the system
      nodeToDeletePtr->setNext(NULL);
      delete nodeToDeletePtr;
      
      nodeToDeletePtr = headPtr;
   }  // end while
   // headPtr is NULL; nodeToDeletePtr is NULL
   
	itemCount = 0;
}  // end clear

template<class T>
int LinkedBag<T>::getFrequencyOf(const T& anEntry) const
{
	int frequency = 0;
   int counter = 0;
   Node<T>* curPtr = headPtr;
   while ((curPtr != NULL) && (counter < itemCount))
   {
      if (anEntry == curPtr->getItem())
      {
         frequency++;
      } // end if
      
      counter++;
      curPtr = curPtr->getNext();
   } // end while
   
	return frequency;
}  // end getFrequencyOf

template<class T>
bool LinkedBag<T>::contains(const T& anEntry) const
{
	return (getPointerTo(anEntry) != NULL);
}  // end contains

// Gets the value at the given position
template<class T>
T LinkedBag<T>::getAt(const unsigned& pos) const
{
    Node<T>* temp = headPtr;
    unsigned int i = pos;
    while(temp != NULL && i > 0){
      temp = temp->getNext();
      i--;
    }
    // As long as we don't have a NULL temp, return
    // what was desired.
    if(i == 0 && temp !=NULL){
      return temp->getItem();
    }
    throw logic_error("Index invalid");
}  

// Sets the value at the given position  
template<class T>
void LinkedBag<T>::setAt(const T& value, const unsigned& pos)
{
    Node<T>* temp = headPtr;
    unsigned int i = pos;
    while(temp != NULL && i > 0){
      temp = temp->getNext();
      i--;
    }
    // As long as we don't have a NULL temp, return
    // what was desired.
    if(i == 0 && temp !=NULL){
      temp->setItem(value);
      return;		
    }
    throw logic_error("Index invalid");
}

// Inserts a node at the given position
template<class T>
bool LinkedBag<T>::insert(const T& value, const int& pos)
{
    Node<T>* temp = headPtr;
    unsigned int i = pos;  
    bool ret = false;
    while(temp != NULL && i > 1){
      temp = temp->getNext();
      i--;
    }
    // As long as we don't have a NULL temp, return
    // what was desired.
    if(i == 1 && temp !=NULL){
      Node<T>* newNode = new Node<T>(value, temp->getNext());
      temp->setNext(newNode);
      itemCount++;
      ret = true;		
    }else{
      throw logic_error("Index invalid");
    }
    return ret;
}	

// Adds the value at the end of the list    
template<class T>
void LinkedBag<T>::push_back(const T& value)
{
    if(headPtr == NULL){
      add(value);
    }else{
      // Not empty.  Walk down the list and stop on the last one
      Node<T>* temp = headPtr;
      while(temp->getNext() != NULL){
        temp = temp->getNext();
      }
      Node<T>* n = new Node<T>(value);
      // Tack it on the end
      temp->setNext(n);
      itemCount++;
    }
}

// Removes the first element in the list   
template<class T>
void LinkedBag<T>::pop_front()
{
    if(headPtr == NULL)return;
    Node<T>* temp = headPtr;
    headPtr = headPtr->getNext();
    delete temp;
    itemCount--;
}

// Removes the last element in the list   
template<class T>
void LinkedBag<T>::pop_back()
{
    if(headPtr == NULL)return; // Empty list
    if(headPtr->getNext() == NULL){ // One element list
      delete headPtr;
      headPtr = NULL;
      return;
    }
    Node<T>* temp = headPtr;  // Iterate to the second to last.
    while(temp->getNext()->getNext() != NULL){
      temp = temp->getNext();
    }
    delete temp->getNext();
    temp->setNext(NULL);
    itemCount--;
}

// Reverse the given list 
template<class T>
LinkedBag<T> LinkedBag<T>::reverse() const
{
    // Step through this list and add to the front of ret.
	LinkedBag<T> ret;
	Node<T>* temp = headPtr;
	while(temp){
		ret.add(temp->getItem());
		temp = temp->getNext();
	}
	return ret;
}

// private
// Returns either a pointer to the node containing a given entry 
// or the null pointer if the entry is not in the bag.
template<class T>
Node<T>* LinkedBag<T>::getPointerTo(const T& anEntry) const
{
   bool found = false;
   Node<T>* curPtr = headPtr;
   
   while (!found && (curPtr != NULL))
   {
      if (anEntry == curPtr->getItem())
         found = true;
      else
         curPtr = curPtr->getNext();
   } // end while
   
   return curPtr;
} // end getPointerTo


