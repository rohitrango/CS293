//char values
#include "template_bst.h"

int main()
{
	BST<char> x; 
	x.insert('e');
	x.insert('b');
	x.insert('d');
	x.insert('a');
	x.insert('c');
	x.print();

	return 0;
}
