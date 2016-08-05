#include "list_of_list.h"

// CONSTRUCTOR AND DESTRUCTOR FUNCTIONS
// These functions and additional helper functions help in initialization and deleting
template<class T>
datastore<T>::datastore() {
	head = NULL;
}

template<class T>
void datastore<T>::deleteItemUtil(item* &i) {
	if(i==NULL)
		return;

	deleteItemUtil(i->next);
	delete i;
}

template<class T>
void datastore<T>::deleteCListUtil(count_list* &i) {
	if(i==NULL)
		return;

	deleteCListUtil(i->next);
	delete i;
}

template<class T>
datastore<T>::~datastore() {
	count_list* start = head;
	while(start!=NULL) {
		deleteItemUtil(start->node);
		start = start->next;
	}
	deleteCListUtil(head);
}

// Interface functions
// These functions help in inserting,searching and deleting the items
template<class T>
int datastore<T>::search(T val) {
	count_list* start = head;
	item* node;
	while(start!=NULL) {		//iterate through the whole list
		
		node = start->node;			//take starting node and iterate through the linked list
		while(node!=NULL) {
			if(node->id == val)
				return start->count;		//return the access count
			node = node->next;
		}
		start = start->next;

	}
	return -1;		//not found
}

template<class T>
void datastore<T>::insert(T val) {
	int accessCount = search(val);		//find the access count of the value we want to add
	int ejected = eject(val);							//eject the value from the datastore
	bool countListExists = false;
	
	if(accessCount==-1)
		accessCount = 1;
	else
		accessCount++;
	
	//search if the new list is present
	count_list* start = head;
	while(start!=NULL) {
		if(start->count == accessCount) {
			countListExists = true;
			break;
		}
		start = start->next;
	}

	if(countListExists) {				//the list with the count exists
		start->num++;
		item* newNode = new item;
		newNode->id = val;
		newNode->next = start->node;
		start->node = newNode;
		// start->num++;
		// if(node==NULL) {
		// 	start->node = new item;
		// 	start->node->id = val;
		// 	start->node->next = NULL;
		// }
		// else {
		// 	while(node->next != NULL) {
		// 		node = node->next;
		// 	}
		// 	node->next = new item;
		// 	node->next->id = val;
		// 	node->next->next = NULL;
		// }
	}
	else {					//the list with the count doesnot exist, make it and add the element to it
		
		if(head==NULL) {	//head is NULL, add a node and insert the value
			head = new count_list;
			head->next = NULL;
			head->num = 1;
			head->count = accessCount;
			
			head->node = new item;
			head->node->id = val;
			head->node->next = NULL;
		}

		else {		//head contains atleast one element
			count_list* prev = NULL;
			start = head;
			
			while((start->count < accessCount )) {
				if(start->next == NULL)
					break;
				else if(start->next->count > accessCount)
					break;
				prev = start;
				start = start->next;	
			}

			//if its the first element to insert
			if(prev == NULL and start->count > accessCount) {
				prev = new count_list;
				prev->count = accessCount;
				prev->num = 1;
				prev->next = head;
				prev->node = new item;
				prev->node->id = val;
				prev->node->next = NULL;
				head = prev;
				return;
			}

			//here we have the start count
			count_list* nextList = start->next;
			if(nextList == NULL) {					//appending another list infront of last access count list
				start->next = new count_list;
				nextList = start->next;
				nextList->count = accessCount;
				nextList->num = 1;
				nextList->next = NULL;
				nextList->node = new item;

				nextList->node->id = val;
				nextList->node->next = NULL;
			}	
			else {			//case like start=1 and nextList=5, insert 2 in between
				count_list* newList = new count_list;
				newList->count = accessCount;
				newList->num = 1;

				newList->node = new item;
				newList->node->id = val;
				newList->node->next = NULL;

				newList->next = nextList;
				start->next = newList;
			}
		//end of outer else
		}
	}
}

template<class T>
int datastore<T>::find_max() {
	if(head==NULL)
		return -1;
	else {
		count_list* s = head;
		while(s->next!=NULL) 
			s = s->next;
		return s->count;
	}
}

template<class T>
void datastore<T>::list_max() {
	if(head==NULL)
		return;
	else {
		count_list* s = head;
		while(s->next!=NULL)
			s = s->next;
		if(s->node == NULL)
			return;
		else {
			item* i = s->node;
			while(i!=NULL) {
				cout<<i->id<<" ";
				i = i->next;
			}
			cout<<endl;
		}
	}
}

template<class T>
void datastore<T>::decrement(T val) {
	
	int accessCount = search(val);
	if(accessCount<=0)
		return;			//do nothing

	int j = eject(val);
	accessCount--;

	//search for the list
	bool listExists = false;
	count_list* start = head;
	while(start!=NULL) {
		if(start->count == accessCount) {
			listExists = true;
			break;
		}
		start = start->next;
	}

	if(listExists) {		//list exists, just add it to the list
		item* newItem = new item;
		newItem->id = val;
		newItem->next = start->node;
		start->node = newItem;
		start->num++;
	}
	else {			//does not exist, create one
		start = head;
		count_list* newList;
		//head cannot be null, otherwise search would have returned -1 and the function would have just returned
		if(head->count > accessCount) {
			newList = new count_list;
			newList->num = 1;
			newList->count = accessCount;
			newList->next = head;
			
			newList->node = new item;
			newList->node->id = val;
			newList->node->next = NULL;
			head = newList;
		}
		else {
			while(true) {
				if(start->next == NULL)
					break;
				else if(start->next->count > accessCount) {
					break;
				}
				start = start->next;
			}
			//we have the start value, create the list
			newList = new count_list;
			newList->num = 1;
			newList->count = accessCount;
			newList->next = start->next;
			
			newList->node = new item;
			newList->node->id = val;
			newList->node->next = NULL;

			start->next = newList;
		}
	}
}

//change this FIRST --> changed
template<class T>
int datastore<T>::eject(T val) {
	int accessCount = search(val);
	if(accessCount==-1)
		return 0;
	
	count_list* start = head, *prevList = NULL;

	while(start!=NULL) {
		
		if(start->count == accessCount) {		//found list, now find the node
			item* prevNode=NULL,*curNode=start->node;
			while(curNode!=NULL) {
				if(curNode->id == val)			//curNode found, delete it
					break;
				prevNode = curNode;
				curNode = curNode->next;
			}

			if(prevNode == NULL) 		//first node
				start->node = start->node->next;
			else
				prevNode->next = curNode->next;
			delete curNode;
			start->num--;
			break;	//from the outer while, since we deleted the element
		}
		else {					//move on to the next list
			prevList = start;
			start = start->next;
		}

	}

	if(start->num <= 0)	{	//time to delete the list altogether, since it doesnot have other nodes
		if(prevList==NULL)	
			head = head->next;
		else
			prevList->next = start->next;
		delete start;
	}

	return 1;
}

template<class T>
void datastore<T>::reset() {
	if(head==NULL)
		return;

	if(head->count != 0) {		//the zero counter doesnot exist, create it
		count_list* newHead = new count_list;
		newHead->count = 0;
		newHead->num = 0;
		newHead->node = NULL;
		newHead->next = head;
		head = newHead;
	}

	count_list* start = head->next;
	
	while(start!=NULL) {

		item* node = start->node;
		while(node!=NULL) {
			item* zeroNode = new item;
			zeroNode->id = node->id;
			zeroNode->next = head->node;
			head->node = zeroNode;
			head->num++;
			node = node->next;
		}
		//inserted all values to the zero node, delete this linked list
		// deleteItemUtil(start->node);
		start = start->next;

	}
	start = head->next;
	head->next = NULL;			//delete the next of head since there are no elements and deallocate memory
}

template<class T>
void datastore<T>::list_zero() {
	//check if the head is a zero counter
	if(head->count==0 and head->num > 0) {	//print the values
		item* s = head->node;
		while(s!=NULL) {
			cout<<s->id<<" ";
			s = s->next;
		}
		cout<<endl;
	}
	else {
		return;
	}
}

template<class T>
void datastore<T>::list_count(int c) {
	count_list* start = head;
	while(start!=NULL) {
		if(start->count == c) {
			if(start->num < 1)	//no elements, do nothing
				return;

			item* node = start->node;
			if(node!=NULL) {
				cout<<c<<" ";
			}
			while(node!=NULL) {
				cout<<node->id<<" ";
				node = node->next;
			}
			cout<<endl;

			return;
		}
		else {
			start = start->next;
		}
	}
}

template<class T>
void datastore<T>::print() {
	if(head==NULL) 
		return;

	count_list* start = head;
	while(start!=NULL) {
		if(start->node!=NULL) {
			item* node = start->node;
			cout<<start->count<<" ";
			while(node!=NULL) {
				cout<<node->id<<" ";
				node = node->next;
			}
			cout<<endl;
		}
		start = start->next;
	}
}



template class datastore<int>;
template class datastore<float>;
template class datastore<char>;