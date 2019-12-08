// C++ program for B-Tree insertion 
#ifndef __BTREE_CPP
#define __BTREE_CPP

#include "btree.h"
#include <iostream>
using namespace std; 

//default constructors
Node::Node(){
   key = new int[DEG]; //array of keys stored in the node (between child ptrs)
   children = new Node*[DEG+1]; //array of child ptrs (1 greater)
   size = 0;
   parent = NULL;
}

BPlusTree::BPlusTree(int _m){ //BPlus Tree of degree m created
   DEG = _m;
   root = NULL;
}

string BPlusTree::display(){
   // Do not edit this function
   ss.str("");
   traverse(root);
   return ss.str();
}

void BPlusTree::traverse(Node* cursor){
   
   // Do not edit this function
   if(cursor!=NULL) //empty tree
   {
      for(int i = 0; i < cursor->size; i++)
      {
         ss<<"{"<<cursor->key[i]<<"}";
      }
      ss<<" ";
      if(cursor->isLeaf != true)
      {
         for(int i = 0; i < cursor->size+1; i++)
         {
            traverse(cursor->children[i]);
         }
      }
   }
}

bool Node::isFull(){
   return size == DEG+1;
}

void Node::printData(){
   cout << "Size: " << size << endl << "Keys: ";
   for (int i = 0; i < DEG; i++){
      cout << key[i] << " ";
   }
   cout << "Left Sibling " << leftsib->key[0] << " Right Sibling " << rightsib->key[0] << endl; 
   cout << endl;
}

pair<Node*,int> Node::getNextChild(int k){
   for (int i = 0; i < size; i++){
      if (k < key[i])
         return make_pair(children[i], i);
   }
   return make_pair(children[size], size);
}

bool Node::addKey(int k){ //only occurs on a leaf node
   if (isFull())
      return false;

   if (size == 0){ // no keys (new node formed)
      key[0] = k;
      children[0] = NULL; //no node to point to
      size++;
      return true;
   }

   for (int i = 0; i < size; i++){
      //handle duplicates
      if (key[i] == k){
         return true;
      }
      
      if (k < key[i]){ //key must be stored before key[i] and keys beyond
         for (int x = size; x > i; x--){ //shift keys to the right of current pos (inclusive) by 1
            key[x] = key[x-1];
         }
         key[i] = k;
         size++;
         return true;
      }
   }

   //key is greater than all the current stored keys
   key[size] = k; 
   size++;
   return true;
}

void Node::deleteKey(int k){ //assumes it is present
   for (int i = 0; i < size; i++){
      if (key[i] == k){
         for (int  j = i; j < size-1; j++){
            key[j] = key[j+1];
            children[j] = children[j+1];
         }
         children[size-1] = children[size];
         size--;
         break;
      }
   }
}

bool Node::borrow(){
   if (leftsib != NULL && leftsib->size > DEG/2){ //can borrow from left
      //get maximum from left
      int leftMax = leftsib->key[leftsib->size-1]; 
      leftsib->deleteKey(leftMax);
      addKey(leftMax);
      return true;
   } 
   else if (rightsib != NULL && rightsib->size > DEG/2){
      int rightMin = rightsib->key[0];
      rightsib->deleteKey(rightMin);
      addKey(rightMin);
      return true;
   }
   return false;
}

int Node::split(){
   Node* left = new Node();
   Node* right = new Node();
   if (isLeaf){
      left->isLeaf = true;
      right->isLeaf = true;
   }
   left->leftsib = leftsib;//old left sibling points to new left
   left->rightsib = right; //since these 2 were made
   right->leftsib = left;
   right->rightsib = rightsib; //old right sibling points to old right
   left->parent = this;
   right->parent = this;
   int mid = (DEG+1)/2;
   int midKey = key[mid];

   //left half of the keys copied to left
   for (int i = 0; i < mid; i++){
      left->key[i] = key[i];
      left->children[i] = children[i];
      left->size++;
   }
   left->children[left->size] = children[mid];
      
   
   //right half copied to right
   if (!isLeaf){   
      mid++; //do not add mid to the right array
   }
   for (int i = mid; i < size; i++){
      right->key[i-mid] = key[i]; //i-mid == index for right node
      right->children[i-mid] = children[i]; 
      right->size++;  
   }
   right->children[size-mid] = children[size];
   //only one key in current node now (midkey that was pushed up)
   delete[] key;
   key = new int[DEG];
   key[0] = midKey;
   size = 1;

   //2 children ptrs only to newly formed left and right
   delete[] children;
   children = new Node*[DEG+1];
   children[0] = left;
   children[1] = right;

   if(isLeaf)
      isLeaf = false;
   
   return midKey;
}

void BPlusTree::mergeWithParent(Node* curr, int index){
   Node* parent = curr->parent;
   int childPivot = curr->key[0];
   bool added = false;
   for (int i = 0; i < parent->size; i++){ //going through the parent's keys
      if (childPivot < parent->key[i]){
         for (int x = parent->size; x > i; x--){ //shift keys to the right of current pos (inclusive) by 1
            parent->key[x] = parent->key[x-1];
         }
         parent->key[i] = childPivot;
         parent->size++;
         for (int x = parent->size; x > i; x--){
            parent->children[x] = parent->children[x-1];
         }
         parent->children[index] = curr->children[0];
         parent->children[index+1] = curr->children[1];
         added = true;
         break;
      }
   }
   if (!added){ //key must be appended at the end
      parent->key[parent->size] = childPivot;
      parent->children[parent->size] = curr->children[0];
      parent->children[parent->size+1] = curr->children[1];
      parent->size++;
   }
}
            
void BPlusTree::insert(int k){
   // Your code here
   // cout << "Inserting " << k << endl;
   if (root == NULL){
      root = new Node();
      root->key[0] = k;
      root->children[0] = NULL;
      root->leftsib = NULL;
      root->rightsib = NULL;
      root->size++;
      root->isLeaf = true;
   }

   Node* curr = root;
   Node* parent = NULL; //will store parent of leaf node
   int index;
   while(!curr->isLeaf){ //get to leaf node
      parent = curr;
      pair<Node*, int> childIndexPair = curr->getNextChild(k);
      curr = childIndexPair.first;
      curr->parent = parent;
      index = childIndexPair.second;
   }

   curr->addKey(k);

   if (curr->isFull()){ //isFull
      curr->split();
      //need to update parent ptrs, mergeWithParent the split node
      if (parent != NULL && !parent->isFull()){
         mergeWithParent(curr, index);

         curr = parent;
         while(curr != NULL && curr->isFull()){ //&& curr->parent != NULL
            k = curr->split();
            if (curr->parent != NULL){
               pair<Node*, int> childIndexPair = curr->getNextChild(k);
               mergeWithParent(curr, childIndexPair.second);
            }
            curr = curr->parent;
         }
      }

   }
} 

Node* BPlusTree::search(int k){
   // Your code here
   // cout << "Searching for " << k << endl;
	if(root == NULL){
		return NULL;
	} 
   else{
		Node* curr = root;
		while(!curr->isLeaf){ //until the leaf node is reached where the key is bound to be present
			bool found = false;
         for(int i = 0; i < curr->size; i++){ //traverse through internal node's children
            if(k < curr->key[i]){ //left child of key i may have k 
               curr = curr->children[i];
               found = true;
					break;
				}
			}
         if (!found)
            curr = curr->children[curr->size]; //just go to the last child of the current node, if none of them matched
		}
      // cout << "got to leaf node starting from " << curr->key[0] << endl; 
		for(int i = 0; i < curr->size; i++){ //traverse keylist of the leaf node narrowed down
			if(k == curr->key[i])
            return curr;
		}
      return NULL; // not found in leaf either
   }
} 


void BPlusTree::remove(int k){
   // Your code here
   // cout << "Removing " << k << endl;
   if (root == NULL){
      cout << "Empty tree, nothing to remove";
      return;
   }
   Node* knode = search(k);
   if (!knode){
      cout << "Key not present";
      return;
   }
   if (knode->parent == NULL){ //only one key, single root
      if (knode->size == 1){
         delete knode;
         root = NULL;
         return;
      }
      else{
         knode->deleteKey(k);
         if (knode->size == 0){
            delete knode;
            root = NULL;
         }
      }
   }
   else{ //on leaf node
      // cout << "on a leaf node " << endl;
      knode->deleteKey(k);
      if(knode->size < DEG/2){// if L drops below the half-full critera
         // cout << "Fallen below minimum" << endl;
         bool borrowed = knode->borrow(); //ask left and right
         if (!borrowed){
            //merge with left
            for (int i = 0; i < knode->leftsib->size; i++){
               knode->leftsib->addKey(knode->key[i]);
            }
            Node* parentk = knode->parent;
            delete knode;
            for (int  j = 0; j < parentk->size; j++){
               parentk->children[j] = parentk->children[j+1];
            }
         }
      }
      Node* curr = knode->parent;
      while(curr != NULL){
         if (curr->size == 1){ //deleting will destroy the node, special case
            curr->key[0] = curr->children[1]->key[0];
         }
         else{
            curr->deleteKey(k);
         }
         curr = curr->parent;
      }
   }
} 

#endif