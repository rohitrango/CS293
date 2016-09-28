#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

class Bank {
	map<string,int> accounts;
	map<int,vector<string> > printBalances;
	public:
		bool openAccount(string name);
		bool closeAccount(string name);
		bool deposit(string name, int amt);
		bool withdraw(string name, int amt);
		void print(int a, int b);
};

bool Bank::openAccount(string name) {
	if(accounts.find(name) == accounts.end()) {		// unsuccessful search
		accounts[name] = 0;
		return true;
	}
	return false;
}

bool Bank::closeAccount(string name) {
	
	if(accounts.find(name) == accounts.end()) 		// No account found
		return false;

	if(accounts[name]>0) {		// non-zero balance
		return false;
	}
	accounts.erase(name);
	return true;
}

bool Bank::deposit(string name, int amt) {
	if(accounts.find(name) == accounts.end()) 	//no entry present, return F
		return false;
	else {
		accounts[name] += amt;
		return true;
	}
}

bool Bank::withdraw(string name, int amt) {
	if(accounts.find(name) == accounts.end())		// no entry present
		return false;
	int val = accounts[name];
	if(val < amt)
		return false;
	accounts[name] -= amt;
	return true;
}

void Bank::print(int a, int b) {
	int low = min(a,b);
	int hi = max(a,b);	
	for(map<string,int>::iterator i = accounts.begin(); i!= accounts.end(); i++) {
		if(i->second >= low and i->second <= hi) {
			// cout<<i->first <<" "<< i->second<<endl;				// just checking the order in which they are stored
			printBalances[i->second].push_back(i->first);
		}
	}

	for(auto it = printBalances.begin(); it!=printBalances.end();it++) {
		cout<<it->first<<" ";
		for(auto j = it->second.begin(); j != it->second.end()-1; j++) {
			cout<<*j<<" ";
		}
		cout<<*(it->second.end()-1)<<endl;
	}

	printBalances.clear();
}

//////////////////////////////////////////////////////////////////////////
// Main function here
//////////////////////////////////////////////////////////////////////////

int main() {
	
	Bank DSABank; 
	char choice;
	string name;
	int val1,val2,amt;
	long unsigned int errors = 0;
	bool runTests = true;
	
	while(runTests) {
		
		cin>>choice;
		switch(choice) {
			case 'O':
				cin>>name;
				errors += 1-DSABank.openAccount(name);
				break;

			case 'C':
				cin>>name;
				errors += 1-DSABank.closeAccount(name);
				break;

			case 'E':
				cout<<errors<<endl;
				runTests = false;
				break;

			case 'D':
				cin>>name>>amt;
				errors += 1-DSABank.deposit(name,amt);
				break;

			case 'W':
				cin>>name>>amt;
				errors += 1-DSABank.withdraw(name,amt);
				break;

			case 'P':
				cin>>val1>>val2;
				DSABank.print(val1,val2);
				break;
		}
	}
}