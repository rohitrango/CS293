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
	x.printroot();
	x.rebalance(5);
	x.printroot();
	x.rebalance(5);
	x.printroot();
	x.remove(5);
	x.printroot();
	std::cout << x.search(5) << std::endl;
	x.print();
	return 0;
}
