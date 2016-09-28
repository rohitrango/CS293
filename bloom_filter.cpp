#include <iostream>
#include <functional>
#include <bitset>
#include <unordered_map>
using namespace std;

struct bloom_hash{			// functor
	public:
		hash<int> myhash;
		int operator()(int x, int i, int m) {
			return (myhash(x+i))%m;
		}
};

struct bloom_filter{
	private:
		bool* filter;
		int hash_number;
		int bool_size;
		bloom_hash hasher;

	public:
		bloom_filter(int m, int k) {		// m sized bool array and k hash functions
			filter = new bool[m];
			hash_number = k;
			bool_size = m;
			for(int i=0;i<m;i++)
				filter[i] = false;
		}

		~bloom_filter() {
			delete[] filter;
		}

		void insert(int x) {
			for(int i=0;i<hash_number;i++) {
				filter[hasher(x,i,bool_size)] = true;
			}
		}

		bool lookup(int x) {
			for(int i=0;i<hash_number;i++) {
				if(!filter[hasher(x,i,bool_size)]) {
					return false;
				}
			}
			return true;
		}

		void deleteElement(int x) {
			for(int i=0;i<hash_number;i++) {
				filter[hasher(x,i,bool_size)] = false;
			}
		}
};


int main() {
	unordered_map<int,bool> checker;		// this will report false positives
	int t,a,b, ctr,choice;				//ctr = counter, choice = values to insert/del/lookup
	char ch;							//choice char
	bool testcase;						// run the current testcase
	int inserts,deletes;
	int falseP,falseN;
	cin>>t;

	for(int i=0;i<t;i++) {
		cin>>a>>b;
		bloom_filter myFilter(a,b);

		inserts = deletes = 0;
		falseP = falseN = 0;
		testcase = true;
		
		while(testcase) {
			cin>>ch;
			switch(ch) {
				case 'i':					// insert elements					
					cin>>ctr;
					inserts+=ctr;
					for(int j=0;j<ctr;j++) {
						cin>>choice;
						myFilter.insert(choice);
						checker[choice] = true;	//insert in the unordered_map
					}
					break;
				
				case 'e':					// terminate testcase
					testcase = false;
					break;

				case 'd': 					// delete elements
					cin>>ctr;
					deletes+=ctr;
					for(int j=0;j<ctr;j++) {
						cin>>choice;
						myFilter.deleteElement(choice);
						checker.erase(choice);	//signifies that the element was deleted
					}
					break;

				case 'l':					//lookup
					cin>>choice;
					if(checker[choice] and !myFilter.lookup(choice))
						falseN++;
					else if(!checker[choice] and myFilter.lookup(choice))
						falseP++;
					printf("l %d %d\n",choice,int(myFilter.lookup(choice)));
					break;

				case 'r':					//report
					printf("r %d %d %d %d\n", falseP, falseN, inserts, deletes);
					break;
			}		

		}
	}	
}