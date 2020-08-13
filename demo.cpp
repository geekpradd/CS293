#include <iostream> 
#include <fstream>
using namespace std; 

int josephus(int n, int k) 
{ 
	if (n == 1) 
		return 1; 
	else
		/* The position returned by josephus(n - 1, k) 
		is adjusted because the recursive call 
		josephus(n - 1, k) considers the 
		original position k % n + 1 as position 1 */
		return (josephus(n - 1, k) + k-1) % n + 1; 
} 

// Driver Program to test above function 
int main() 
{ 
	ofstream fout;
	fout.open("test");
	ofstream ff;
	ff.open("sol");
	fout << (4000-1)*99 << endl;
	for (int i=2; i<=4000; ++i){
		for (int j=2; j<=100; ++j){
			fout << i << " " << j << endl;
			ff << josephus(i, j) << endl;
		}
	}
	fout.close();
	ff.close();

	return 0; 
} 

// This code is contributed by shubhamsingh10 
