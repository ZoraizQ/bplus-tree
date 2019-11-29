// C++ program for B-Tree insertion 
#ifndef __BTREE_CPP
#define __BTREE_CPP

#include "btree.h"
using namespace std; 

Node::Node(){

   key = new int[DEG];
   children = new Node*[DEG+1];
}

BPlusTree::BPlusTree(int _m){

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
   if(cursor!=NULL)
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
} 

Node* BPlusTree::search(int k){
   // Your code here
} 

void BPlusTree::remove(int k){
   // Your code here
} 

#endif