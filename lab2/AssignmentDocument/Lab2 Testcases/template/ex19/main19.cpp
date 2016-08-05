//char values
#include "template_bst.h"

int main()
{
	BST<char> x; 
	
	x.insert('a');
	x.remove('a');
	x.print();
	x.remove('b');
	x.print();

	return 0;
}
