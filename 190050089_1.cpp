#include <iostream>
using namespace std;

long long J(long long n, long long k){
	if (n == 1LL)
		return 0LL;
	if (n < k){
		long long recur = J(n-1, k);
		long long killed = (k-1)%n;
		return (recur+killed+1)%n;
	}
	else {
		long long small_n = n - n/k;
		long long recur = J(small_n, k);
		long long left = n/k; left = left*k;
		long long zero = n - left;
		long long rem_add = (small_n - zero);
		long long transformed = (recur + rem_add) % small_n;
		return (transformed + transformed/(k-1));
	}
	
}

int main(){
	long long n; long long k; 
	cin >> n;
	cin >> k;
	long long ans = J(n, k) + 1;
	cout << ans << endl;
	return 0;
}