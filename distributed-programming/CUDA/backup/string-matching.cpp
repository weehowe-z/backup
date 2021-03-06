#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;


void preKMP(string pattern, unsigned int next[]);
void KMPSearch(string target, string pattern);
void BFSearch(string target, string pattern);

int main(int argc, char const *argv[])
{
	ifstream in("input.txt");
	if (!in) {
		cerr << "error, cannot find input.txt\n";
		return -1;
	}

	string target,pattern;
	in >> target;
	in >> pattern;
	BFSearch(target,pattern);
	KMPSearch(target,pattern);



	ofstream output("output2.txt");
	return 0;
}

void BFSearch(string target, string pattern)
{
	clock_t begin, end;
	double time_spent;

	cout<<"--------------------\n";
	cout<<"Alogrithm:\tBrute Force\n\n";
	begin = clock();

	unsigned int target_len = target.length();
	unsigned int pattern_len = pattern.length();
	unsigned int i = 0;

	while (i <= target_len - pattern_len){
		unsigned int j = 0;
		while (j < pattern_len){
			if ((target[i+j]) != pattern[j]) break;
			++j;
		}
		if (j == pattern_len) {
			cout<<"Match @ position "<< i << endl;
		}
		++i;
	}

	end = clock();
	time_spent = (double)(end - begin)* 1000 / CLOCKS_PER_SEC;
	cout<<"\ntime spent:\t"<<time_spent<<"ms"<<endl;
	cout<<"--------------------\n";
}

void preKMP(string pattern,unsigned int next[])
{
	unsigned int pattern_len = pattern.length();
	unsigned int k; //  longest suffix
    next[0] = 0;
    for (int i = 1; i < pattern_len; ++i)
    {
		while(k > 0 && pattern[i] != pattern[k]) k = next[k-1];
		if (pattern[i] == pattern[k]) ++k;
		next[i] = k;	
    }
}


void KMPSearch(string target, string pattern){
	clock_t begin, end;
	double time_spent;

	cout<<"--------------------\n";
	cout<<"Alogrithm:\tKMP\n\n";
	begin = clock();

	unsigned int target_len = target.length();
	unsigned int pattern_len = pattern.length();
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int *next = new unsigned int[pattern_len];

	preKMP(pattern,next);

	while (i <= target_len - pattern_len){
		// cout<<"OUT target["<<i<<"]\n";
		// cout<<"OUT pattern["<<j<<"]\n";
		while (j < pattern_len){
			// cout<<"inner "<<j<<endl;
			if ((target[i+j]) != pattern[j]) break;
			++j;
		}
		// cout<<"current j "<<j<<endl;
		if (j == 0){
			++i;
		}
		else if  (j == pattern_len) {
			cout<<"Match @ position "<< i << endl;
			j = 0;
			++i;
		}
		else {
			i += j - next[j-1];
			j = next[j-1]; 
			// cout<<"afedfdfd "<<j<<endl;
		}
	}


	delete []next;

	end = clock();
	time_spent = (double)(end - begin)* 1000 / CLOCKS_PER_SEC;
	cout<<"\ntime spent:\t"<<time_spent<<"ms"<<endl;
	cout<<"--------------------\n";

}