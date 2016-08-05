//one element in the tree ..  deleting root.. and performing delete again on empty tree
#include "bst.h"

int main()
{
	BST x; 
	x.insert(1);
	x.remove(1);
	x.print();
	x.remove(2);
	return 0;
}
