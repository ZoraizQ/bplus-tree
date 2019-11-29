#ifndef __BTREE_H
#define __BTREE_H
#include <string>
#include <sstream>
using namespace std;

stringstream ss; // Needed for display function, ignore

int DEG = -1; // Global variable for degree

// A B+Tree node 
class Node {

	int *key; // An array of keys 
	string* value; // NULL if node is leaf, otherwise an array of strings containing values corresponding to the keys in this node
	Node **children; // An array of child pointers
	int size;	 // Current number of keys 
	bool isLeaf; // Is true when node is leaf. Otherwise false 
public: 
	Node(); // Constructor 

	// Make B+Tree friend of this so that we can access private members of this class in BTree functions 
	friend class BPlusTree;
}; 

// A B+Tree 
class BPlusTree{

	Node *root; // Pointer to root node 
	public: 
		
		// Constructor (Initializes tree as empty) 
		BPlusTree(int _m);

		// function to traverse the tree depth first and return string 
		string display();

		// helper function for display
		void traverse(Node* cursor);

		// the main function that inserts a new key in this tree 
		void insert(int k); 

		// function to search a key in this tree 
		Node* search(int k); 

		// function to delete node containing particular key
		void remove(int k); 
};

#endif