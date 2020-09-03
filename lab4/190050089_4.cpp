#include <bits/stdc++.h>
#define ii pair<int, int>
using namespace std;


signed main(){
	string s; cin >> s;
	int k; cin >> k;
	int n = s.size();
	k = n/k;
	vector< vector<int> > count(26, vector<int>(k, 0));

	for (int i=0; i<s.size(); ++i){
		int val = s[i] - 'a';
		count[val][i%k]++;
	}
	int ops = 0;
	for (int i=0; i<k; ++i){
		int total = 0;
		int best = -1;
		for (int j=0; j<26; ++j){
			total += count[j][i];
			best = max(best, count[j][i]);
		}

		ops += total - best;
	}
	cout << ops << endl;
	
	vector< vector< pair<int, int> > > occur(26, vector< pair<int, int> > (n, make_pair(0, 0)));

	vector<ii> highest(n, make_pair(0, 0));
	vector<ii> total(n, make_pair(0, 0));
	int best = 1000000000;
	int best_i = 0;

	for (int blk = 1; blk < n; ++blk){
		int rem = n % blk;
		int extra = 0;
		if (rem > 0){
			rem = blk - rem;
			extra++;
		}
		int cur = rem;
		
		for (int i=0; i<n; ++i){
			int val = s[i] - 'a';
			int index = i%blk;
			if (total[index].second != blk){
				total[index] = make_pair(1, blk);
			}
			else {
				total[index].first++;
			}
			if (occur[val][index].second != blk){
				occur[val][index] = make_pair(1, blk);
			}
			else{
				occur[val][index].first++;
			}
			if (highest[index].second != blk){
				highest[index] = make_pair(1, blk);
			}
			else{
				highest[index].first = max(highest[index].first, occur[val][index].first);
			}
		}
		for (int i=0; i<blk; ++i){
			cur += total[i].first - highest[i].first;
		}
		if (cur < best){
			best = cur;
			best_i = (n/blk)+extra;
		}
		else if (cur == best){
			int cu = (n/blk)+extra;
			if (cu < best_i){
				best_i = cu;
			}
		}
	}

	cout << best << " " << best_i << endl;


}