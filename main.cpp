/* Copyright (C) 2018
* Course: CO2003
* Author: Rang Nguyen
* Ho Chi Minh City University of Technology
*/

#include"TreeSet.h"
#include<fstream>
#include<cstdlib>
void print(ostream& os, AVLNode* root)
{
	if(root!=NULL)
	{
		os << root->key<<"\t";
	os << "hight: "<<root->balance<<"\t";
	if(root->left!=NULL)
		os << "left: "<<root->left->key<<"  ";
	if(root->right!=NULL)
		os << "right: "<<root->right->key;
	os << endl;
	print(os,root->left);
	
	print(os,root->right);
	}
}
// print all elements in the set in ascending order
ostream& operator<<(ostream& os, const TreeSet& tree) {
	if (tree.root == NULL) os << "NULL\n";
	else{
	 	print(os,tree.root);
	}
	return os;
}

int main() {
	TreeSet set, temp, *subSet;
	ifstream ifs;
	ifs.open("input.txt");
	char command; 
	int val;
	try
	{
		while (ifs >> command) {
			switch (command) {
			case 'a': // add an element to the set
				ifs >> val;
				set.add(val);
				break;
			case 'c': // check if an element is in the set or not
				ifs >> val;
				printf("The set contains %d: %d\n", val, set.contains(val));
				break;
			case 'd': // copy thai;
			case 'l': // return the largest elemmainent in the set
				printf("The largest element in the set is: %d\n", set.last());
				break;
			case 'f': // return the largest elemmainent in the set
				printf("The min element in the set is: %d\n", set.first());
				break;
			case 'o': // returns largest element smaller than val.
				ifs >> val;
				printf("The largest element smaller than %d is %d\n", val, set.lower(val));
				break;
			case 'h': // returns largest element smaller than val.
				ifs >> val;
				printf("The min element smaller than %d is %d\n", val, set.higher(val));
				break;
			case 'p': // print the content of the set in ascending order
				cout << set << endl;
				break;
			case 'r': // remove an element from the set
				ifs >> val;
				set.remove(val);
				break;
			case 's': // return the sub set 
				int fromVal, toVal;
				ifs >> fromVal >> toVal;
				subSet = set.subSet(fromVal, toVal);
				cout <<"Subset is: "<< *subSet << endl;
				if (!subSet) delete subSet;
				break;
			case 'z': //returns the size of the set
				printf("The number of elements in the set is: %d\n", set.size());
				break;
			default:
				throw "Wrong input format!";
			}
		}
	}
	catch (char const* s) {
		printf("An exception occurred. Exception type: %s\n", s);
	}

	ifs.close();
	return 0;
	system("pause");
}












