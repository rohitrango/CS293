#include "myArray.h"

int main(){
	int temp[]={1,5,3,7,2};
	myArray A(5);
	myArray C(5);
	for(int i=0;i<5;i++)
		A.addToArray(i+1);
	for(int i=0;i<5;i++)
		C.addToArray(i+1);

	myArray B(temp,5);
	
	cout<<A.isEqual(B)<<endl;
	cout<<A.isEqual(C)<<endl;
	
}
