#include "myArray.h"

// this exerise is use to test correct implementation
// of the different constructors of the myArray class.

int main(){


	myArray A(10);
	for(int i=0;i<10;i++)
		A.addToArray(i+1);
	A.deleteFromArray();
	A.deleteFromArray(5);
	A.deleteFromArray();
	A.printArray();
	A.deleteFromArray(5);
	A.printArray();
	return 0;
}
