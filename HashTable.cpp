#include "HashTable.h"
#include <cstddef>
#include <stdexcept>
#include <vector>

//Remove
#include <iostream>

//Constructor
template<class T>
HashTable<T>::HashTable( unsigned int (*f)(const T&), unsigned int capacity){
	//Constructor
	hashfn = f;
	the_capacity = capacity;
	table = new item_t<T>[capacity];
	//Set all elements to NULL and state EMPTY
	for(int i = 0; i < capacity; i++){
		table[i].data = NULL;
		table[i].state = EMPTY;
	}
	// Initalize size to zero
	the_size = 0;
}
//Deconstructor
template<class T>
HashTable<T>::~HashTable() {
	//Call clear
	clear_table();
	delete[] table;
	table = NULL;
}
//Copy Constructor
template<class T>
HashTable<T>::HashTable(const HashTable& other){
	//Not correct just initalizing values to NULL
	hashfn = other.hashfn;
	the_capacity = other.the_capacity;
	the_size = 0;//other.the_size;
	table = new item_t<T>[the_capacity];
	//Set all elements to NULL and state EMPTY
	for(int i = 0; i < the_capacity; i++){
	   if((other.table[i]).state == EMPTY){
		   table[i].data = NULL;
		   table[i].state = EMPTY;
	   }else if (other.table[i].state == OCCUPIED ){
		   //Convert linked bag to vector
   		   vector<T> bagContents  = ((other.table[i]).data)->toVector();
		   //Create new linked bag to copy to
		   LinkedBag<T>* A = new LinkedBag<T>();
   		   for(int j = 0; j < bagContents.size(); j++){
			   //Push back new elements
   		       A->push_back(bagContents[j]);
			   //Add to the size
			   the_size++;
   		   }
		   (table[i].data) = A;
		   (table[i].state) = OCCUPIED;
	   }else if (other.table[i].state == REMOVED ){
		   //Create new linked bag to copy to
		   LinkedBag<T>* A = new LinkedBag<T>();
		   (table[i].data) = A;
		   (table[i].state) = REMOVED;
	   }
	}
}
//Assignment Operator
template<class T>
HashTable<T> HashTable<T>::operator= (const HashTable& other){ 
	if(table == other.table){
		return *this;
	} else {
       // Assignment Operator
	   clear_table();
       hashfn = other.hashfn;
	   the_capacity = other.the_capacity;
	   //Set copy over all elements
	   for(int i = 0; i < the_capacity; i++){
	       if((other.table[i]).state == EMPTY || (other.table[i]).state == REMOVED){
			//Do Nothing
		   }else if((other.table[i]).state == OCCUPIED){
		      vector<T> bagContents  = ((other.table[i]).data)->toVector();
		      for(int i = 0; i < bagContents.size(); i++){
			      //cout << bagContents[i] << endl;
		          insert(bagContents[i]);
		      }
	       }
	   }
	   return *this;
    }
}
//Find
template<class T>
bool HashTable<T>::find(T thing) const{
	unsigned int hash_value = ((*hashfn)(thing))%the_capacity;
	if(table[hash_value].state == OCCUPIED){
	    // Check whether value exists in linked bag at index of hash_value
	    return (table[hash_value].data)->contains(thing);
	} else{
		return false;
	}
}
//Size
template<class T>
unsigned int HashTable<T>::size() const{
	//Find size of hash table
	return the_size;
}
//Capacity
template<class T>
unsigned int HashTable<T>::capacity() const{
	//Return Hash table capacity
	return the_capacity;
}
//Is the table full
template<class T>
bool HashTable<T>::isFull() const{
	//Check whether table is full
	for(int i = 0; i < the_capacity; i++){
	      if(table[i].state == EMPTY || table[i].state == REMOVED){
	      	return false;
	      }	
	}
	return true;
}
//Insert new element into table
template<class T>
void HashTable<T>::insert(T thing){
    //If found check next parameter
	if(!find(thing)){
		//Use hash function to get index
		unsigned int hash_value = ((*hashfn)(thing))%the_capacity;
		//If Empty Create linked bag and push back element
		if(table[hash_value].state == EMPTY){
		     // Add value to linked bag
			//Loop through items in linked bag
			LinkedBag<T>* A = new LinkedBag<T>();
			A->push_back(thing);
			(table[hash_value].data) = A;
			table[hash_value].state = OCCUPIED;
			the_size++;
	    //If occupied insert new element
		}else if(table[hash_value].state == OCCUPIED || table[hash_value].state == REMOVED){
			(table[hash_value].data)->push_back(thing);
			table[hash_value].state = OCCUPIED;
			the_size++;
		}
	//Throw logic error if table is full
	} else if(isFull()){
		throw logic_error("Table is full");
	}
	
}


template<class T>
void HashTable<T>::remove(T thing){
	if(!find(thing)){
		//DNE
	} else if(the_size != 0){
		unsigned int hash_value = ((*hashfn)(thing))%the_capacity;
		table[hash_value].data->remove(thing);
		the_size--;
		if(table[hash_value].data->getCurrentSize() == 0){
			table[hash_value].state = REMOVED;
		}
	}

}
//Clear Hash Table
template<class T>
void HashTable<T>::clear_table(){
	for(int i=0; i<the_capacity; i++){
		if(table[i].state == OCCUPIED || table[i].state == REMOVED){
			//cout << table[i].data << endl;
			(table[i].data)->clear();
			delete table[i].data;
			table[i].data = NULL;
			table[i].state = EMPTY;
			//item_t *entry = htable
		}
	}
	the_size = 0;
}

