#include <iostream>
#include "mystack.h"
using namespace std;

int main() {
	Stack A;	//,indexStack;
	int *nextGreatestIndex,*arr;
	int n,tempVal; //,tempIndex
	cin>>n;
	nextGreatestIndex = new int[n];
	arr = new int[n];
	for(int i=0;i<n;i++) {
		nextGreatestIndex[i] = -1;
	}
	for(int i=0;i<n;i++) {
		cin>>arr[i];
	}	

	for(int i=0;i<n;i++) {
		int j=1;
		while(!A.empty()) {
			if(A.top() > arr[i]) {
				break;
			}
			else {
				tempVal = A.pop();
				while(nextGreatestIndex[i-j]!=-1)
					j++;
				// tempIndex = indexStack.pop();
				nextGreatestIndex[i-j] = i;
				
			}
		}
		A.push(arr[i]);
		// indexStack.push(i);
	}

	//print
	for(int i=0;i<n;i++) 
		cout<<arr[i]<<" ";
	cout<<endl;
	for(int i=0;i<n;i++)
		if(nextGreatestIndex[i]!=-1)
			cout<<arr[nextGreatestIndex[i]]<<" ";
		else
			cout<<-1<<" ";
	cout<<endl;
	for(int i=0;i<n;i++)
		cout<<nextGreatestIndex[i]<<" ";
	cout<<endl;

	delete[] arr,nextGreatestIndex;
}

