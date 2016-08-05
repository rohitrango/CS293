#include "bst.h"

int main()
{
	BST x; 
	x.insert(1);
	x.insert(2);
	x.insert(3);
	x.insert(4);
	x.insert(5);
	x.insert(6);
	x.insert(7);
	x.insert(8);
	x.insert(9);
	x.print();
	x.printroot();
	x.rebalance(15);
	x.print();
	x.printroot();
	
	return 0;
}
