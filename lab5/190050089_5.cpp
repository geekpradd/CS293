#include <iostream>
#include <vector>
#define ll long long
using namespace std;
int n, m;
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
			ans[0] = partial[0];	
		}
		if (state[set + 1]){
			ans[1] = partial[1] - ans[0];
		}
		else {
			ans[1] = a[set+1] + ans[0];
		}
		return;
	}
	int p = 1 << k;
	vector<ll> incl(p);
	vector<ll> trun(p);
	vector<ll> nincl(p);
	solve2(k-1, a, nincl, state, partial, set);
	for (int i=0; i<p; ++i){
		ans[i] = nincl[i];
		if (state[set + p + i]){
			trun[i] = partial[p + i] - (state[set + i] ? partial[i] : ans[i]);
		}
	}

	solve2(k-1, a, incl, state, trun, set + p);
	for (int i = 0; i<p; ++i){
		if (state[set+p+i]){
			ans[p+i] = incl[i];
		}
		else if (!state[set+p+i]){
			ans[p + i] = (state[set + i] ? partial[i] : ans[i]) + incl[i];
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
	for (int i=0; i<m; ++i){
		cin >> state[i];
	}
	vector<ll> ans(m); 
	for (int i=0; i<n; ++i){
		solve(i, a, ans, 0);
	}
	for (int i=0; i<m; ++i){
		cout << ans[i] << " ";
	}
	cout << endl;
	vector<ll> other(m);
	vector<ll> partial(m);
	for (int i=0; i<m; ++i){
		if (state[i])
			partial[i] = a[i];
	}
	for (int i=0; i<n; ++i){
		solve2(i, a, other, state, partial, 0);
	}

	for (int i=0; i<m; ++i){
		cout << other[i] << " ";
	}
	cout << endl;
	return 0;

}	