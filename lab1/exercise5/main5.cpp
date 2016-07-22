#include "myArray.h"

int main(){
	myArray A(5);
	for(int i=0;i<5;i++)
		A.addToArray(i+1);
	cout<<A.size()<<endl;
	cout<<A.getValue(2)<<endl;
	
	myArray B(10);
	for(int i=0;i<5;i++)
		B.addToArray(i+1);
	cout<<B.size()<<endl;
	cout<<B.getValue(8)<<endl;
	return 0;
}
