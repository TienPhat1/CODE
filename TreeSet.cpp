/* Copyright (C) 2018
* Course: CO2003
* Author: Rang Nguyen
* Ho Chi Minh City University of Technology
*/

#include <iomanip>
#include <cmath>
#include <queue>

#include "TreeSet.h"

int c = 0;
TreeSet::TreeSet()
{
	root = NULL;
	count = 0;
}


TreeSet::~TreeSet()
{
	clear();
}

void TreeSet::clearRec(AVLNode* root) {
	if (root != NULL) {
		clearRec(root->left);
		clearRec(root->right);
		delete root;
	}
}
void TreeSet::clear() {
	clearRec(root);
	root = NULL;
	count = 0;
}

int maxHight(int a, int b); 
//Tìm giá trị lớn nhất
int maxHight(int a, int b) 
{ 
	return (a > b)? a : b; 
} 
//Lấy height của cây
int heightAVLTree(AVLNode *N) 
{ 
	if (N == NULL) 
		return 0; 
	return N->balance; 
} 
AVLNode* rotateLeft(AVLNode* proot)
{
	
	AVLNode* rootright = proot->right;
	AVLNode* rightleft = rootright->left;
	//Perform rotation
	rootright->left = proot;
	proot->right = rightleft;
	
	proot->balance = maxHight(heightAVLTree(proot->left),heightAVLTree(proot->right))+1;
	rootright->balance = maxHight(heightAVLTree(rootright->left),heightAVLTree(rootright->right))+1;
	
	return rootright;
	
}

AVLNode* rotateRight(AVLNode* proot)
{
	
	AVLNode* rootleft = proot->left;
	AVLNode* leftright = rootleft->right;
	//Perform rotation
	rootleft->right = proot;
	proot->left = leftright;
	proot->balance = maxHight(heightAVLTree(proot->left),heightAVLTree(proot->right))+1;
	rootleft->balance = maxHight(heightAVLTree(rootleft->left),heightAVLTree(rootleft->right))+1;
	return rootleft;
	
}
int getBalance(AVLNode* proot)
{
	if(proot == NULL) return 0;
	return  heightAVLTree(proot->left) - heightAVLTree(proot->right);
}
int  TreeSet::insertAVLNode(AVLNode* &proot,int val){
	if (proot == NULL)
	{//start if
		 proot = new AVLNode(val,1);
		return 1;
	}//end if
	if(val < proot->key){
		int test = insertAVLNode(proot->left,val);

	} 
	else if(val > proot->key){
		int test = insertAVLNode(proot->right,val);
	}
	else
		{
			return 0;
		}
	
	int bal = getBalance(proot);
	if(bal > 1 )
		{//start if.1
			if( val < proot->left->key)
			proot= rotateRight(proot);
			else if(val > proot->left->key){
			proot->left = rotateLeft(proot->left);
			proot = rotateRight(proot);
			}
		}//end if.1
	else if(bal < -1 )
		{//start if.2
			if(val > proot->right->key)
			proot = rotateLeft(proot);
			else if( val < proot->right->key){
			proot->right = rotateRight(proot->right);
			proot = rotateLeft(proot);
			}
		}//end if.2
	proot->balance = maxHight(heightAVLTree(proot->left),heightAVLTree(proot->right)) + 1;
	return 1;
	
}

//*****************{BLOCK DELETE}**************************
//HÀM LẤY GIÁ TRỊ LỚN NHÂT
int TreeSet::maxValueNode(AVLNode* root)
{
	AVLNode* current = root->left;
	while(current->right != NULL)
		current =  current->right;
	return current->key;
}
int TreeSet::deleteAVLNode(AVLNode* &root,int val)
{
	if(root == NULL) return 0;
	//Step 1. Biễu diễn kiếu xóa bst chuẩn
	else if(root !=NULL)
	{
		if(root->key > val){

			int test = deleteAVLNode(root->left,val);
			if(!test) return 0;
		}
		else if(root->key < val){
			int test = deleteAVLNode(root->right,val);
			if(!test) return 0;
		}
	//giá trị của node giống với giá trị của val nên xóa node
		else if(root->key == val)
		{//start else
			//node chỉ có 1 con or không có con nào
			if(root->left == NULL && root->right == NULL)
				{//start if 1.1
					AVLNode* dlt = root;
					root = NULL;
					delete dlt;
					return 1;
				}//start if 1.1
			else if(root->left == NULL&& root->right !=NULL)
				{//start if 1.2
					AVLNode* temp = root->right;
					root->key = temp->key;
					--root->balance;
					root->right = NULL;
					delete temp;
					return 1;
				}// end if 1.2
			else if(root->right == NULL&& root->left !=NULL)
				{//start if 1.3
					AVLNode* temp = root->left;
					--root->balance;
					root->key = temp->key;
					root->left = NULL;
					delete temp;
					return 1;
				}//end if 1.3
			//node có cả 2 con
			else if(root->left != NULL && root->right != NULL)
			{
				int tempkey = maxValueNode(root);
				root->key = tempkey;
				deleteAVLNode(root->left,tempkey);
			}
			return 1;
		}//end else
	}
	root->balance = max(heightAVLTree(root->left), heightAVLTree(root->right))+1;
	int balance = getBalance(root);
	if(balance > 1  )
		{//start if.1
			if(getBalance(root->left) >= 0)
				root = rotateRight(root);
			if(getBalance(root->left) < 0)
			{//start if.1.1
				root->left = rotateLeft(root->left);
				root = rotateRight(root);
			}//end if.1.1
		}//end if.1
		if(balance < -1)
		{//start if.2
			if(getBalance(root->right) <= 0)
				root = rotateLeft(root);
			if(getBalance(root->right) > 0)
			{//start if.2.1
				root->right = rotateRight(root->right);
				root = rotateLeft(root);
			}//end if.2.1
		}//end if.2
	return 1;
}
//**************************{BLOCK DELETE}**********************************
//**************************{CHECK CONTAIN VAL}*****************************
//HÀM KIỂM TRA VAL
bool TreeSet::checkcontain(AVLNode* root,int val)
{
	if(root == NULL)
		return false;
	else
	{
		while(root != NULL)
		{
			if(val < root->key )
				root = root->left;
			else if(val > root->key)
				root = root->right;
			else if(val == root->key)
				return true;
		}
	}
	return false;
}
//**************************{CHECK CONTAIN VAL}*****************************

//**************************{FIND MIN-MAX KEY}******************************
//HÀM TÌM KEY BÉ NHẤT
int TreeSet::findMinKey(AVLNode* root)
{
	if(root == NULL)
		return 0;
	else
		{//start else 1
		if(count == 1)
			return root->key;
		else
		{//start else 1.1
			while( root->left !=NULL)
				root = root->left;
			return root->key;
		}//end else 1.1
	}//end else 1
}
//HÀM TÌM GIÁ TRỊ LỚN NHẤT CỦA TREE
int TreeSet::findMaxKey(AVLNode* root)
{	
	if(root == NULL)
	{
		return 0;
	}
	else if(root->left == NULL&& root->right == NULL)
	{
		return root->key;
	}
	else
	{
		while(root->right != NULL)
			root = root ->right;
		return root->key;
	}
}
//**************************{FIND MIN-MAX KEY}******************************
//**************************{FIND MAX-MIN <-> VAL}***************************
int TreeSet::findMinThanVal(AVLNode* root,int val)
{
	int value;
	int c = 0;
	if(root == NULL) return -1;
	else
	{
		// ! ROOT == NULL : ĐỂ CÓ THỂ DUYỆT CẢ NODE LÁ ( VỚI VERSION CŨ THÌ SÓT NODE LÁ => KHÔNG TÌM ĐƯỢC VỚI NODE LỚN NHÂT)
		while(root != NULL)
		{
			// ! GỘP CHUNG GIỮA > VÀ = : VÌ ĐỀU PHẢI DUYỆT NHÁNH TRÁI
			if(val <= root->key)
			{
				root = root->left;
			}
			// ! BỎ IF VÌ KHÔNG CẦN THIẾT NỮA
			else //if(val > root->key)
			{
				value = root->key;
				c++;
				root = root->right;
			}
			// else if(val == root->key)
			// {
			// 	root = root->left;
			// 	while(root->right != NULL)
			// 		root = root->right;
			// 	value = root->key;
			// 	c++;
			// }
		}
	}
	if(c == 0)
		return -1;
	else
		return value;
}

int findMaxValthanKey(AVLNode* root,int val)
{
	int value;
	int c = 0;
	if(root == NULL) return -1;
	else
	{
		// ! ROOT == NULL : ĐỂ CÓ THỂ DUYỆT CẢ NODE LÁ ( VỚI VERSION CŨ THÌ SÓT NODE LÁ => KHÔNG TÌM ĐƯỢC VỚI NODE LỚN NHÂT)
		while(root != NULL)
		{
			if(val < root->key)
			{
				value = root->key; 
				c++;
				root = root->left;
			}
			// ! BỎ IF : GỘP CHUNG GIỮA > VÀ = : VÌ ĐỀU PHẢI DUYỆT NHÁNH PHẢI
			else //if(val > root->key)
			{
				root = root->right;
			}
			// else if(val = root->key)
			// {
			// 	root = root->right;
			// 	while(root->left != NULL)
			// 		root = root->left;
			// 	value = root->key;
			// 	c++;
			// }
		}
	}
	if(c == 0)
		return -1;
	else
		return value;
}

//**************************{FIND MAX-MIN <-> VAL}***************************
//**************************{COPY}*******************************************

void TreeSet::copySet(AVLNode* set,AVLNode* &root)
{
	if(set == NULL) return ;
	else
	{
		AVLNode* newNode = new AVLNode(set->key,set->balance);
		if(root == NULL)
			root = newNode;
		this->count++;
		copySet(set->left,root->left);
		copySet(set->right,root->right);
	}
}
//**************************{COPY}*******************************************

//**************************{SUBTREE}****************************************

void TreeSet::subTree(AVLNode* root, int fromVal,int toVal, AVLNode*& newTree)
{
	if(root == NULL){
		return;
	}
	else 
	{
		
		if(root->key < fromVal) subTree(root->right, fromVal, toVal,newTree);	
		if(root->key >= fromVal && root->key < toVal){
			subTree(root->left, fromVal, toVal,newTree);
			insertAVLNode(newTree,root->key);
			subTree(root->right, fromVal, toVal,newTree);
		}
		if(root->key >= toVal) subTree(root->left, fromVal, toVal,newTree);

	}
	return;
}

//**************************{SUBTREE}***************************************
int TreeSet::add(int val) {
	if(!contains(val)){
		count++;
	 return  insertAVLNode(root, val);
	}
	//cout << "val : "<< val << endl;
	//_Print(root);
	else return 0;
}

bool TreeSet::contains(int val) {
	return checkcontain(root,val);
}
void TreeSet::copy(const TreeSet& set) {
	delete root;
	if(set.root == NULL){
		root = NULL;
		return ;
	}
	else {
		copySet(set.root,root);

	}
}

int TreeSet::first() {	
	if (root == NULL) {
		throw "NoSuchElementException";
	}

	return findMinKey(root);
	
}

int TreeSet::last() {
	if (root == NULL) {
		throw "NoSuchElementException";
	}

	return findMaxKey(root);
}

int TreeSet::higher(int val) {
	return findMaxValthanKey(root,val);
}

int TreeSet::lower(int val) {
	return findMinThanVal(root,val);
}

bool TreeSet::remove(int val) {
	if(contains(val)){
		--count;
		return  deleteAVLNode(root, val);
	}	
	else return 0;

}


TreeSet* TreeSet::subSet(int fromVal, int toVal) {
	TreeSet* newTree = new TreeSet();
	subTree(this->root,fromVal,toVal,newTree->root);
	return newTree;
}

int TreeSet::size() {
	return count;
}




/*
//* PRINT
void TreeSet::_Print(AVLNode *sroot){
	if(sroot == nullptr) return;
        AVLNode *node = sroot;
        queue<AVLNode*> Queue;
        int h = sroot->balance - 1;
        for(int i = 0; i <= h; ++i){
            for(int j = 0; j < pow(2, i); ++j){
                if(i < h){   
                    if(node != NULL){
                        for(int k = 0; k < pow(2, h - i)/2; ++k) cout << "  ";
                        for(int k = 0; k < pow(2, h - i)/2 - 1; ++k) cout << "__";
                        cout << setfill('0') << setw(2) << node->key;
                        for(int k = 0; k < pow(2, h - i)/2 - 1; ++k) cout << "__";
                        for(int k = 0; k < pow(2, h - i)/2 + 1; ++k) cout << "  ";
                        Queue.push(node->left);
                        Queue.push(node->right);
                    }
                    else{
                        for(int k = 0; k < pow(2, h - i + 1); ++k) cout << "  ";
                        Queue.push(NULL);
                        Queue.push(NULL);
                    }  
                }
                else{
                    if(node != NULL){
                        cout << setfill('0') << setw(2) << node->key;
                        cout << "  ";
                    }
                    else
                        cout << "    ";
                } 
                if(Queue.size() > 0){
                    node = Queue.front();
                    Queue.pop(); 
                }             
            }
            cout << endl;
        }
   	}
*/
