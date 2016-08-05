#include "bst.h"

int main()
{
	BST x; 
	x.insert(9);
	x.insert(1);
	x.insert(-2);
	x.insert(10);
	x.insert(5);
	x.insert(12);
	x.print();

	x.remove(9);
	x.print();

	return 0;
}
