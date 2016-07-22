#include "myArray.h"

// this exerise is use to test correct implementation
// of the different constructors of the myArray class.

int main(){

int temp[5]={1,2,3,4,5};

myArray A;
A.setArrayLimit(5);

for(int i=0;i<5;i++)
	A.addToArray(i+1);

myArray B(5);
for(int i=0;i<5;i++)
	B.addToArray(i+1);

myArray C(temp, 5);
for(int i=0;i<5;i++)
	C.addToArray(i+1);

A.printArray();
B.printArray();
C.printArray();

return 0;

}
