#include "template_bst.h"

int main()
{
	BST<int> x; 
	x.insert(9);
	x.insert(1);
	x.insert(-2);
	x.insert(10);
	x.insert(5);
	x.print();

	return 0;
}
