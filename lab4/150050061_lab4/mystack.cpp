#include "mystack.h"

Stack::Stack() {
	size = 0;
	head = NULL;
}

Stack::~Stack() {
	// destroyNodeUtil(head);
}

void Stack::destroyNodeUtil(node* head) {
	if(head==NULL)
		return;
	destroyNodeUtil(head->next);
	delete head;
}

int Stack::top() {
	if(head==NULL) 
		return -1;
	return head->data;
}

int Stack::pop() {
	if(head==NULL)
		return -1;
	
	size--;
	int data = head->data;
	head = head->next;
	return data;
}

bool Stack::empty() {
	if(size==0)
		return true;
	return false;
}

void Stack::push(int val) {
	node* newNode = new node;
	newNode->data = val;
	newNode->next = head;
	head = newNode;
	size++;
}
