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
				while(nextGreatestIndex[i-j]!=-1 and (i-j)>=0)
					j++;
				if((i-j)>=0)
					nextGreatestIndex[i-j] = i;				
			}
		}
		A.push(arr[i]);
		// indexStack.push(i);
	}

	// for(int i=0;i<n;i++)
	// 	cout<<nextGreatestIndex[i]<<" ";
	// cout<<endl;
	//we have the next greatest values now, implement the water storage algorithm
	unsigned long int water = 0;
	int i=0,nextIndex;
	while(i<n) {
		if(nextGreatestIndex[i]==-1) {		//max element doesnot exist, can't store water here
			int j = i+1;
			if(j>=n)
				break;
			else {
				while(nextGreatestIndex[j]!=-1)
					j = nextGreatestIndex[j];

				water += arr[j]*(j-i-1);
				for(int k=j-1;k>i;k--)
					water -= arr[k];

				i=j;
			}
		}
		else {
			water+= arr[i]*(nextGreatestIndex[i]-i);
			nextIndex = nextGreatestIndex[i];
			while(i<nextIndex) {
				water-= arr[i];
				i++;
			}
		}
	}
	for(int i=0;i<n;i++)
		cout<<arr[i]<<" ";
	cout<<endl;

	cout<<water<<endl;
	delete[] arr,nextGreatestIndex;
}

