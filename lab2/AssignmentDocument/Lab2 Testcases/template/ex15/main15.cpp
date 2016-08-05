//skewed bst and rebalance at last node
#include "template_bst.h"

int main()
{
	BST<char> x; 
	x.insert('a');
	x.insert('b');
	x.insert('c');
	x.insert('d');
	x.insert('e');
	x.insert('f');
	x.insert('g');
	x.insert('h');
	x.insert('i');
	x.print();
	x.printroot();
	x.rebalance('i');
	x.print();
	x.printroot();
	
	return 0;
}
