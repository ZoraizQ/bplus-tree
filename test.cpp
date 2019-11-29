#include "btree.cpp"
#include <iostream>

using namespace std;

bool isEqual(string s1, string s2){
	if (s1.length() != s2.length())
		return false;
	bool equal = true;
	for (int i = 0; i < s1.length(); ++i)
	{
		if(s1[i] != s2[i])
			equal = false;
	}
	return equal;
}

// Driver program to test above functions 
int main() 
{ 
	int marks = 0;
	BPlusTree tree1(3);
	tree1.insert(1); 
	tree1.insert(5); 
	tree1.insert(9);
	tree1.insert(10);
	tree1.insert(11);
	tree1.insert(14);
	tree1.insert(15);
	tree1.insert(16);
	tree1.insert(21);
	tree1.insert(32);
	string output = tree1.display();
	string expected = "{15} {9}{11} {1}{5} {9}{10} {11}{14} {21} {15}{16} {21}{32} ";
	if(isEqual(output, expected)){
		cout << "Insert correct" << endl;
		marks+=40;
	}
	else
		cout << "Insert incorrect" << endl;
	
	BPlusTree tree2(4);
	tree2.insert(1); 
	tree2.insert(5); 
	tree2.remove(1);
	tree2.remove(5);
	tree2.insert(11);
	tree2.insert(9);
	tree2.insert(3);
	tree2.insert(10);
	tree2.insert(6);
	tree2.insert(12);
	tree2.remove(9);
	output = tree2.display();
	expected = "{10} {3}{6} {10}{11}{12} ";
	if(isEqual(output, expected)){
		cout << "Remove correct" << endl;
		marks+=40;
	}
	else
		cout << "Remove incorrect" << endl;

	BPlusTree tree3(5);
	tree3.insert(1); 
	tree3.insert(2); 
	tree3.insert(3); 
	tree3.insert(4); 
	tree3.insert(5); 
	tree3.insert(6); 
	tree3.insert(7); 
	tree3.insert(8); 

	if (tree3.search(3) && tree3.search(7) && !tree3.search(12)){
		cout << "Search correct" << endl;
		marks+=20;
	}
	else
		cout << "Search incorrect" << endl;

	cout << "Total: " << marks << '/' << 100 << endl;


	return 0; 
} 