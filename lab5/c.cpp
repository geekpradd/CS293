#include <iostream>
#include <vector>
#define DUMP(a) \
    do { std::cout << "[" << #a " = " << (a) << "]" <<  std::endl; } while(false)
#define ll long long
using namespace std;
int n, m;
// template<class T> ostream& operator<<(ostream &os, vector<T> V) {
//     os << "[ ";
//     for(auto v : V) os << v << " ";
//     return os << "]";
// }
void solve(int k, vector<int> &a, vector<ll> &ans, int set){
	if (k == 0){
		ans[0] = a[set + 0];
		ans[1] = a[set + 0] + a[set + 1];
		return;
	}
	int p = 1 << k;
	vector<ll> incl(p);
	vector<ll> nincl(p);
	solve(k-1, a, nincl, set);
	solve(k-1, a, incl, set + p);
	for (int i = 0; i<p; ++i){
		ans[p + i] = nincl[i] + incl[i];
		ans[i] = nincl[i];
	}
}
void solve2(int k, vector<int> &a, vector<ll> &ans, vector<int> &state, vector<ll> &partial, int set){
	if (k == 0){
		if (!state[set]){
			ans[0] = a[set + 0];
		}
		else {
			ans[0] = partial[set + 0];	
		}
		if (state[set + 1]){
			ans[1] = partial[set + 1] - ans[0];
		}
		else {
			ans[1] = a[set+1] + ans[0];
		}
		return;
	}
	int p = 1 << k;
	vector<ll> incl(p);
	vector<ll> trun(m);
	vector<ll> nincl(p);
	solve2(k-1, a, nincl, state, partial, set);
	for (int i=0; i<p; ++i){
		ans[i] = nincl[i];
		if (state[set + p + i]){
			trun[set + p + i] = partial[set + p + i] - (state[set + i] ? partial[set +		 i] : ans[i]);
		}
	}

	solve2(k-1, a, incl, state, trun, set + p);
	for (int i = 0; i<p; ++i){
		if (state[set+p+i]){
			ans[p+i] = incl[i];
		}
		else if (!state[set+p+i]){
			ans[p + i] = (state[set + i] ? partial[set + i] : ans[i]) + incl[i];
		}

	}
}

signed main(){
	cin >> n;
	m = 1 << n;
	vector<int> a(m);
	vector<int> state(m);

	for (int i=0; i<m; ++i){
		cin >> a[i];
	}

	vector<ll> ans(m); 
	for (int i=0; i<n; ++i){
		solve(i, a, ans, 0);
	}
	for (int i=0; i<m; ++i){
		cout << ans[i] << " ";
	}
	cout << endl;
	
	return 0;

}	