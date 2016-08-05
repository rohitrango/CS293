#include "myArray.h"

// this exerise is use to test correct implementation
// of the different constructors of the myArray class.

int main(){

int temp[5]={1,2,3,4,5};

myArray A;
A.setArrayLimit(5);

for(int i=0;i<5;i++)
	A.addToArray(5-i*i);

myArray B(5);
for(int i=0;i<5;i++)
	B.addToArray(i+1);

myArray C;
C = A+B;

A.printArray();
B.printArray();
C.printArray();

return 0;

}
