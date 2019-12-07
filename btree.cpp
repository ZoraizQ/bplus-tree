// C++ program for B-Tree insertion 
#ifndef __BTREE_CPP
#define __BTREE_CPP

#include "btree.h"
using namespace std; 

//default constructors
Node::Node(){
   key = new int[DEG]; //array of keys stored in the node (between child ptrs)
   children = new Node*[DEG+1]; //array of child ptrs (1 greater)
}

Node::findKeySlot(int k){
   for (int i = 0; i < children.size(); i++){
      if (k < children[i])
         return i;
   }
   return i + 1;
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

            
void BPlusTree::insert(int k){
   // Your code here
   Node* curr = root;
   Node* parent = NULL; //will store parent of leaf node
   while(!curr.isLeaf){ 
      parent = curr;
      
   }
} 

Node* BPlusTree::search(int k){
   // Your code here
} 

void BPlusTree::remove(int k){
   // Your code here
} 

#endif