#include "myArray.h"

int main(){
	int temp[]={1,5,3,7,2};
	myArray A(10);
	for(int i=0;i<10;i++)
		A.addToArray(i+1);
	cout<<A.isSorted()<<endl;
	myArray B(temp,5);
	cout<<B.isSorted()<<endl;
	cout<<A.binarySearch(5)<<endl;
	cout<<A.binarySearch(20)<<endl;
	return 0;
}
