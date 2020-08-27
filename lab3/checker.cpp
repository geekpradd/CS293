#include <iostream>
#include <ctime>
using namespace std;
int n = 20;
long long dp[21][20];

long long get_rank(long long p[]){
	long long rank = 0;
	int mx = 0;
	for (int i=0; i<n; ++i){
		rank += p[i]*dp[i+1][mx];
		mx = max(p[i], mx);
	}
	return rank;
}

void test(){
	int t = 1000000;
	while (t--){
		srand(time(NULL));
		long long mm =51724158235371;
		long long r = rand()%mm;
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
		long long rs = get_rank(p);
		if (rs != r){
			cout << "wrong" << endl;
			break;
		}
	}
}

int main(){
	cin.tie(NULL); ios_base::sync_with_stdio(false);
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
	test();

	return 0;
}