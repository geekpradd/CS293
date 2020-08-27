#include <iostream>
using namespace std;


int main(){
	cin.tie(NULL); ios_base::sync_with_stdio(false);
	int n, t; cin >> n >> t; 
	long long dp[n+1][n];
	for (int i=0; i<n; ++i){
		dp[n][i] = 1;
	}
	for (int i=n-1; i>=1; --i){
		for (int j=i-1; j>=0; --j){
			dp[i][j] = 0;
			for (int k=0; k<=j; ++k){
				dp[i][j] += dp[i+1][j];
			}
			dp[i][j] += dp[i+1][j+1];
		}
	}
	while (t--){
		char type; cin >> type;
		if (type == 'R'){
			long long p[n];
			for (int i=0; i<n; ++i) cin >> p[i];

			long long rank = 0;
			long long mx = 0;
			for (int i=0; i<n; ++i){
				rank += p[i]*dp[i+1][mx];
				mx = max(p[i], mx);
			}
			cout << rank << endl;
		}
		else {
			long long r; cin >> r;
			long long p[n];
			p[0] = 0;
			long long total = 0;
			long long mx = 0;
			for (int i=1; i<n; ++i){
				long long base = dp[i+1][mx];
				long long left = (r-total);
				long long steps = (left/base);
				if (steps <= mx){
					p[i] = steps;
					total += steps*base;
				}
				else {
					p[i] = mx+1;
					mx++;
					total += mx*base;
				}
			}
			for (int i=0; i<n; ++i){
				cout << p[i] << " ";
			}
			cout << endl;
		}
	}

	return 0;
}