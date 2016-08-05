#include "template_bst.h"

int main()
{
	BST<float> x; 
	x.insert(9.1);
	x.insert(1.9);
	x.insert(-2.1);
	x.insert(10.1);
	x.insert(5.3);
	x.insert(12.2);
	x.print();
	x.printroot();
	x.rebalance(5.1);
	x.printroot();
	x.rebalance(5.3);
	x.printroot();
	x.remove(5.3);
	x.printroot();
	std::cout << x.search(5.3) << std::endl;
	x.print();
	return 0;
}
