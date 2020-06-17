# BPlus-Tree

A B+ tree of degree ​ m ​ is a balanced tree in which each node can hold a maximum of ​ m ​ keys
and ​ m+1​ pointers​. 

![BPlusTree](https://iq.opengenus.org/content/images/2018/06/b--search.jpg)

**Helper functions created**: split(), borrow(), borrowChildren(), addKey(), deleteKey(), mergeWithParent()

## Functions:
#### Create a tree:
```
BPlusTree ​ tree​ ( ​ 3 ​ ); ​ // creating a tree of degree 3
tree.insert(​ 5 ​ ); //inserting a key
tree.insert(​ 10​ );
tree.insert(​ 14​ );
tree.insert(​ 32​ );
tree.insert(​ 9 ​ );
tree.insert(​ 21​ );
tree.insert(​ 1 ​ );
tree.insert(​ 11​ );
tree.insert(​ 15​ );
tree.insert(​ 16​ );
```

#### Display tree:
```
tree.display();
// {15}​ ​ {9}{11}​ ​ {1}{5}​ ​ {9}{10}​ ​ {11}{14}​ ​ {21}​ ​ {15}{16}​ ​ {21}{32}
```

#### Search a key:
```
tree.search(5); //returns Node* if found else null
```

#### Remove a key:
```
tree.remove(5); //removes Node containing the key 5
```
