#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <stdexcept>

#include "LinkedBag.cpp"

using namespace std;


enum node_state {EMPTY, OCCUPIED, REMOVED};

template <class T>
struct item_t {
	LinkedBag<T> *data;
	node_state state;
};

template <class T>
class HashTable {

public:
	HashTable(unsigned int (*f)(const T&), unsigned int capacity);

	~HashTable();

	HashTable(const HashTable& other);

	// Similar to copy constructor, but check for self
	// assignment, if not, clear and copy all data.
	HashTable<T> operator= (const HashTable& other);

	bool find(T thing) const;

	unsigned int size() const;

	unsigned int capacity() const;

	bool isFull() const;

	void insert(T thing);

	void remove(T thing);

	void clear_table();

private:
	unsigned int the_size;
	unsigned int the_capacity;
	item_t<T>* table;
	unsigned int (*hashfn)(const T& thing);
};


#endif
