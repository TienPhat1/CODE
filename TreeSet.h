/* Copyright (C) 2018
* Course: CO2003
* Author: Rang Nguyen
* Ho Chi Minh City University of Technology
*/
#pragma once
#include"AVLNode.h"
class TreeSet
{
private:
	AVLNode * root;
	int count;

protected:
	void clearRec(AVLNode*root);	

public:
	TreeSet();
	~TreeSet();
	void clear();
	void deleteNode(AVLNode* &root);
	// print out the set in ascending order
	friend ostream& operator<<(ostream& os, const TreeSet& t);

	// YOUR TASKS START HERE
	int  insertAVLNode(AVLNode* &proot,int val);
	int maxValueNode(AVLNode* root);
	void copySet(AVLNode* set,AVLNode* &root);
	bool checkcontain(AVLNode* root,int val);
	int findMinKey(AVLNode* root);
	int findMaxKey(AVLNode* root);
	int findMinThanVal(AVLNode* root,int val);
	int deleteAVLNode(AVLNode* &root,int val);
	void subTree(AVLNode* root, int fromVal,int toVal,AVLNode*& newTree);
	int add(int val);		
	bool contains(int val);
	void copy(const TreeSet& set);
	int first();
	int higher(int val);
	int last();
	int lower(int val);
	bool remove(int val);
	TreeSet* subSet(int fromVal, int toVal);
	int size();
	//void _Print(AVLNode *sroot);
	// END HERE
};

