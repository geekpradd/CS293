#include <iostream>
using namespace std;

int main() {
	int n, k; cin >> n >> k;
	int ar[k];
	bool ok = true;
	int z = 0;
	int mx = 0, mi = 0;
	for (int i = 0; i < k; i++) {
		cin >> ar[i];
		if (ar[i] > n/k+int(bool(n%k))) ok = false;
		if (!ar[i]) z++;
		if (mx < ar[i]) {
			mx = ar[i];
			mi = i;
		}
	}
	if (ok) return 0;
	while (z < k-1) {
		int m = 0,  ind = 0;
		for (int i = 0; i < k; i++) {
			if (m < ar[i] && i^mi) {
				m = ar[i];
				ind = i;
			}
		}
		cout << ind << ' ';
		int x = ar[ind];
		ar[ind] = 0;
		for (int j = 1; j <= k; j++)
			ar[(ind+j)%k] += x/k + int(x%k >= j);
			
		z = 0;
		for (int i = 0; i < k; i++)
			if (!ar[i]) z++;
	}
	cout << mi << endl;
	return 0;
}