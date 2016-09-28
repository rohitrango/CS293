#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

struct wordStructure {
	string word;
	int count;
};

bool cmpStruct(wordStructure a, wordStructure b) {
	if(a.count > b.count)
		return true;
	else if(a.count < b.count)
		return false;
	else {
		if(a.word.compare(b.word) < 0)
			return true;
		else 
			return false;
	}
}

int main() {
	int k,q,m;
	char temp;
	char command[200];
	string word, w1,w2,w3;
	cin >> k >> q >> m;
	// cout<<"k - "<<k<<" q - "<<q<<" m - "<<m<<endl;
	wordStructure* totalList;
	vector<unordered_map< string, int> > wordMap;
	unordered_map<string,int> totalWords;

	wordMap.resize(k);

	for(int i=0;i<k;i++) {				// read from a file and count the words
		cin>>command;
		ifstream fin(command);			// open the file
		while(fin >> word) {			// read the word
			wordMap[i][word]++;			// map it
			totalWords[word]++;			// map it to the bigger hashmap
		}
		fin.close();
		cin>>temp;						// to capture the $
	}
	getline(cin,word);	

	// To print the 'm' most used words
	// Collect the data in a structure and sort it according to the function declared above
	totalList = new wordStructure[totalWords.size()];
	int ii=0;
	for(auto kv : totalWords) {
		totalList[ii].word = kv.first;
		totalList[ii].count = kv.second;
		ii++;
	}
	sort(totalList,totalList+totalWords.size(),cmpStruct);

	for(int i=0;i<m;i++)
		cout<<totalList[i].count<<" "<<totalList[i].word<<endl;
	cout<<"$\n";

	// we have read the words from the files, time to answer the queries.
	for(int i=0;i<q;i++) {

		int index1=-1,index2=-1;
		getline(cin,word);

		for(int j=0;j<word.length();j++) {
			if(word[j]==' ') {
				if(index1==-1)
					index1 = j;
				else
					index2 = j;
			}
			if(index2!=-1)
				break;
		}
		w1 = word.substr(0,index1);
		w2 = word.substr(index1+1,index2-index1-1);
		w3 = word.substr(index2+1);
		// cout << w1 << "-" << w2 << "-" << w3 << endl;
		if(w2=="ONLY") {
			for(int i=0;i<k;i++)
				if(wordMap[i][w1]>0)
					cout<<i<<" ";
		}

		else if(w2=="OR") {
			for(int i=0;i<k;i++)
				if(wordMap[i][w1]>0 or wordMap[i][w3]>0)
					cout<<i<<" ";
		}

		else if(w2=="AND") {
			for(int i=0;i<k;i++)
				if(wordMap[i][w1]>0 and wordMap[i][w3]>0)
					cout<<i<<" ";
		}

		else if(w2=="EXCEPT") {
			for(int i=0;i<k;i++)
				if(wordMap[i][w1]>0 and wordMap[i][w3]==0)
					cout<<i<<" ";
		}

		cout<<"\n$\n";
	}


}


