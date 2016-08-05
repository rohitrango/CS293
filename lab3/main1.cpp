#include "list_of_list.h"
using namespace std;

int main(){

	datastore<float> x;
	char ch;
	cin>>ch;
	while(ch!='q'){
		float val;
		int ctr;
		
		switch(ch) {
			case 'i':
				cin>>ctr;
				// cout<<ctr<<endl;
				for(int i=0;i<ctr;i++) {
					cin>>val;
					// cout<<"val "<<val<<endl;
					x.insert(val);
				}
				break;

			case 'p':
				x.print();
				break;

			case 'd':
				cin>>val;
				x.decrement(val);
				break;

			case 's':
				cin>>val;
				cout<<x.search(val)<<endl;
				break;

			case 'm':
				cout<<x.find_max()<<endl;
				break;

			case 'l':
				x.list_max();
				break;

			case 'z':
				x.list_zero();
				break;

			case 'r':
				x.reset();
				break;

			case 'c':
				cin>>val;
				x.list_count(val);
				break;

			case 'e':
				cin>>val;
				cout<<x.eject(val)<<endl;
				break;

			case 'x':
				cin>>val;
				cout<<x.search(val)<<endl;
				break;

			default:
				cout<<"Some error has occured. Invalid command maybe.\n";
				break;
		}
		// implement rest of the input commands here. eg. for 'i' (insert), 'p' (print) etc 
		cin>>ch;
	}

	return 0;
}
