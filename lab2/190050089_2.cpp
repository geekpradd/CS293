#include <iostream>
#include <vector>
using namespace std;

int n, k; 

void operate(int a[], int i){
	int dist = a[i];
	a[i] = 0; 
	int common = dist/k;
	int left = dist%k;
	int j = (i+1)%k;;
	for (int l=0; l<left; ++l){
		a[(j+l)%k]++;
	}
	for (int l=0; l<k; ++l){
		a[l] += common;
	}
}

int main(){

	cin >> n >> k;
	int a[k];
	vector<int> max_pos;
	for (int i=0; i<k; ++i){
		cin >> a[i];
	}
	if (k == 0){
		return 0;
	}
	int max_cur = a[0];
	int min_cur = a[0];
	for (int i=1; i<k; ++i){
		max_cur = max(max_cur, a[i]);
		min_cur = min(min_cur, a[i]);
	}
	if ((max_cur - min_cur) <= 1){
		return 0;
	}
	for (int i=0; i<k; ++i){
		if (a[i] == max_cur){
			max_pos.push_back(i);
		}
	}
	int sz = max_pos.size();
	if (sz > 1){
		for (int i=1; i<sz; ++i){
			operate(a, max_pos[i]);
			cout << max_pos[i] << " ";
		}
	}
	int best = max_pos[0];

	int j = 0;
	int count = 0;
	while (a[best] < n){
		if (j == best){
			j = (j+1)%k;
		}
		if (a[j] != 0){
			operate(a, j);
			cout << j << " ";	
			count++;
		}
		
		j = (j+1)%k;
	}
	cout << best << endl;
	return 0;
}