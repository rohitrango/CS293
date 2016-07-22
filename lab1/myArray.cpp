#include "myArray.h"

myArray::myArray() {
	arr = NULL;
	arrLimit = lastIndex = -1;	//Since nothing is specified yet
}

myArray::myArray(int n) {
	arr = new int[n];
	arrLimit = n;
	lastIndex = -1;		//since there are no elements now
}

//assuming that the size of array 'a' is 'n'
myArray::myArray(int *a, int n) {		//size of array
	arr = new int[n];
	for(int i=0;i<n;i++)
		arr[i] = a[i];
	arrLimit = n;
	lastIndex = n-1; // lastIndex points to the final element
}

void myArray::setArrayLimit(int n) {
	if(arrLimit==-1) {
		arrLimit = n;
		// delete[] arr; 		//delete if already exists
		arr = new int[n];
	}
}

void myArray::addToArray(int a) {
	if(lastIndex>=arrLimit-1) {
		return;		//size limit exceeded, do nothing
	}
	else {
		lastIndex+=1;
		arr[lastIndex] = a;		//increment last index and assign 
	}
}

void myArray::addToArray(int *a,int k) {
	int i=0;
	while(lastIndex<arrLimit-1 and i<k) {				
	// add till either myArray fills or second array is done
		lastIndex++;
		arr[lastIndex]=a[i];
		i++;
	}
}

void myArray::printArray() {
	for(int i=0;i<=lastIndex;i++) {
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}

void myArray::deleteFromArray() {
	if(lastIndex==-1) {
		return;				//empty list, do nothing
	}
	else {
		lastIndex--;
	}
}

void myArray::deleteFromArray(int k) {
	if(k <= lastIndex+1) {
		lastIndex-=k;
	}
	else {
		lastIndex=-1;
	}
}

bool myArray::isSorted() {			
	//checks if sorted is true
	// zero and one element arrays are trivially sorted
	// bool sorted = true;
	for(int i=0;i<lastIndex;i++) {
		if(arr[i]>arr[i+1])
			return false;
	}
	return true;
}

bool myArray::binarySearch(int a) {
	//since we dont have a sorting function now, we just check if its sorted. If not, just return false
	if(!isSorted()) 
		return false;

	if(lastIndex==-1)
		return false;

	int beg=0,end=lastIndex,mid;		// beginning, middle and end
	//trivial binary search
	while(beg<=end) {
		mid = (beg+end)/2;
		if(arr[mid]==a) {
			return true;
		}
		else if(arr[mid]>a) {
			end = mid-1;
		}
		else if(arr[mid]<a) {
			beg = mid+1;
		}
	}
	return false;
}

bool myArray::isEqual(myArray A) {
	//check if sizes are equal
	if(lastIndex!=A.lastIndex)
		return false;

	//check for inequality anywhere
	for(int i=0;i<=lastIndex;i++) {
		if(arr[i]!=A.arr[i])
			return false;
	}

	return true;
}

int myArray::getValue(int index) {
	if(index > lastIndex) {
		cout<<"INDEX OUT OF BOUND";
		return -1;
	}
	else {
		return arr[index];
	}
}

int myArray::size() {
	//simple, return the current size of the array
	return lastIndex+1;
}


//change this asap
myArray myArray::operator+(myArray& A) {
	
	if(lastIndex == A.lastIndex and arrLimit==A.arrLimit) {    			
	//assuming the 'current sizes' and 'max sizes' are equal.
		myArray summed(arrLimit);			//the sum array will have max size as these 2 array's current size
		for(int i=0;i<=lastIndex;i++) {
			summed.addToArray(arr[i]+A.arr[i]);
		}
		// summed.printArray();
		return summed;
	}	
	else {
		myArray zeroArray;
		return zeroArray;
	}
}

myArray::~myArray() {
	// delete[] arr;
	// Since modern day compilers have a garbage collector function as well, (as suggested by my TA), this function better be empty.
}