#include "bst.h"

int main()
{
	BST x; 
	x.insert(9);
	x.insert(1);
	x.insert(-2);
	x.insert(10);
	x.insert(5);
	x.print();


	std::cout << x.search(5) << std::endl;
	std::cout << x.search(15) << std::endl;
	std::cout << x.search(4) << std::endl;

	return 0;
}
