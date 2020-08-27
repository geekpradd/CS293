#include <iostream>
#define DUMP(a) \
    do { std::cout << "[" << #a " = " << (a) << "]" <<  std::endl; } while(false)
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
			int p[n];
			for (int i=0; i<n; ++i) cin >> p[i];

			long long rank = 0;
			int mx = 0;
			for (int i=0; i<n; ++i){
				rank += p[i]*dp[i+1][mx];
				mx = max(p[i], mx);
			}
			cout << rank << endl;
		}
		else {
			int r; cin >> r;
			int p[n];
			p[0] = 0;
			int total = 0;
			int mx = 0;
			for (int i=1; i<n; ++i){
				for (int j=0; j<=(mx+1); ++j){
					int current = dp[i+1][max(j, mx)];
					if (current + total > r){
						p[i] = j;
						mx = max(j, mx);
						break;
					}
					else {
						total += current;
					}
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