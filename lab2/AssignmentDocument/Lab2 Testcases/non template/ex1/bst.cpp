#include "bst.h"
using namespace std;
BST::BST() {
	root = NULL;
}

void BST::destroyNodeUtil(BSTNode* node) {
	if(node==NULL)
		return;
	destroyNodeUtil(node->left);
	destroyNodeUtil(node->right);
	delete node;
}

BST::~BST() {
	destroyNodeUtil(root);
}

bool BST::search(int val) const {
	BSTNode* curNode = root;
	while(curNode!=NULL) {
		if(curNode->data == val)
			return true;
		else if(curNode->data > val) //go to left tree
			curNode = curNode->left;
		else
			curNode = curNode->right;
	}
	return false;
}

void BST::insert(int val) {

	if(search(val))			//if val exists, dont add it
		return;

	BSTNode* prevNode = NULL;
	BSTNode* curNode = root;
	bool isRightNode = false;

	while(curNode!=NULL) {
		prevNode = curNode;
		if(curNode->data > val) { //join it in the left subtree
			isRightNode = false;
			curNode = curNode->left;
		}
		else {
			isRightNode = true;
			curNode = curNode->right;
		}
	}

	curNode = new BSTNode();
	curNode->left = NULL;
	curNode->right = NULL;
	curNode->data = val;

	if(prevNode==NULL)
		root = curNode;
	else {
		if(isRightNode)
			prevNode->right = curNode;
		else 
			prevNode->left = curNode;
	}

}

void BST::remove(int val) {
	if(search(val)) {
		
		//proceed to the node to delete
		BSTNode* prevNode = NULL;
		BSTNode* curNode = root;
		
		while(curNode->data != val) {
			if(curNode->data < val) {
				prevNode = curNode;
				curNode = curNode->right;
			}
			else {
				prevNode = curNode;
				curNode = curNode->left;
			}
		}
		
		// we have the curNode now, time to check whether its a leaf or not
		if(curNode->left == NULL && curNode->right == NULL) {
			//its a leaf
			if(prevNode==NULL) {		//root has no child, delete it
				root = NULL;
				return;
			}

			if(prevNode->right == curNode)
				prevNode->right = NULL;
			else if(prevNode->left == curNode)			
				prevNode->left = NULL;
			delete curNode;
		}
		
		// if the node to be deleted has a single child, replace the node by its child and replace h
		else if(curNode->left == NULL && curNode->right != NULL) {

			if(prevNode==NULL) {
				//root has a single child
				root = root->right;
				return;
			}

			if(prevNode->left == curNode) {
				prevNode->left = curNode->right;
			}
			else if(prevNode->right == curNode) {
				prevNode->right = curNode->right;
			}
			// curNode = curNode->right; 
		}
		else if(curNode->left != NULL && curNode->right == NULL) {
			// curNode = curNode->left;

			if(prevNode==NULL) {
				root = root->left;
				return;
			}

			if(prevNode->left == curNode) {
				prevNode->left = curNode->left;
			}
			else if(prevNode->right == curNode) {
				prevNode->right = curNode->left;
			}
		}

		// if the node has 2 children, find the element nearest to the given element
		else if(curNode->left != NULL && curNode->right != NULL) {
		// find sucessor and replace
			BSTNode* delNode = curNode;
			// prevNode = root;
			// curNode = root->left;
			prevNode = curNode;
			curNode = curNode->right;

			while(curNode->left != NULL) {
				//go to the rightmost left subtree element
				prevNode = curNode;
				curNode = curNode->left;
			}

			delNode->data = curNode->data;
			
			if(prevNode!=delNode)
				prevNode->left = curNode->right;
			else
				prevNode->right = curNode->right;
			// curNode = curNode->right;
		}
	}
}

void BST::rebalance(int val) {
	
	if(search(val)) {			//rebalance only if found
		BSTNode* curNode = root;
		int n = 1;
		
		// count the number of nodes before we reach the rebalancing node
		while(curNode->data!=val) {
			n++;
			if(curNode->data < val)
				curNode = curNode->right;
			else
				curNode = curNode->left;
		}

		if(n==1)			//root is the element, its already rebalanced
			return;

		// store the path in the array arr
		BSTNode** arr = new BSTNode*[n];
		arr[0] = root;
		for(int i=0;i<n-1;i++) {
			if(arr[i]->data < val) 
				arr[i+1] = arr[i]->right;
			else
				arr[i+1] = arr[i]->left;
		}

		BSTNode *upper,*lower,*parent;
		// use tree rotations to iteratively take the element to top
		for(int i=n-1;i>0;i--) {

			if(i>1)
				parent = arr[i-2];

			if(arr[i-1]->left == arr[i]) {		//apply right rotation
				upper = arr[i];
				lower = arr[i]->right;
				arr[i-1]->left = lower;
				upper->right = arr[i-1];
				arr[i-1] = arr[i];
				
				if(i>1) {
					if(parent->right == upper->right)
						parent->right = arr[i-1];
					else if(parent->left == upper->right)
						parent->left = arr[i-1];
					else
						cout<<"Error1\n";
				}	
				else {
					root = arr[0];
				}			
			}
			else if(arr[i-1]->right == arr[i]) {    //apply left rotation
				upper = arr[i];
				lower = arr[i]->left;
				arr[i-1]->right = lower;
				upper->left = arr[i-1];
				arr[i-1] = arr[i];
				if(i>1) {
					if(parent->right == upper->left) 
						parent->right = arr[i-1];
					else if(parent->left == upper->left)
						parent->left = arr[i-1];
					else
						cout<<"Error2\n";
				}	
				else {
					root = arr[0];
				}			
			}
			else
				cout<<"Error3\n";		//debugging
		}

		delete[] arr;
		// cout<<"---------------\n";
		// print();
		// cout<<"---------------\n";
	}
}

int BST::numberOfElements(BSTNode* node) const {
	if(node==NULL)
		return 0;
	else
		return numberOfElements(node->left) + numberOfElements(node->right) + 1;
}

void BST::printroot() const {
	if(root!=NULL)
		cout<<root->data;
	if(root->left!=NULL)
		cout<<" "<<root->left->data;
	if(root->right!=NULL)
		cout<<" "<<root->right->data;
	cout<<endl;
}

//utility function to implement print function
void BST::printUtil(BSTNode* node) const {
	if(node == NULL)
		return;

	printUtil(node->left);
	cout<<node->data<<" ";
	printUtil(node->right);
}

void BST::print() const {
	BSTNode* cur = root;
	printUtil(root);
	cout<<endl;
}