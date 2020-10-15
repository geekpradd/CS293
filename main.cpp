#include <bits/stdc++.h>
#define ii pair<int, int>
#define mp make_pair
using namespace std;
#define	DUMP(a)  do { std::cout << "[" << #a " = " << (a) << "]" <<  std::endl; } while(false)

struct node {
	node* left;
	node* right;
	int i;
	int op;
};

ii get_steps(node* nd, int k){
	if (nd->op==0){
		return mp(0, 0);
	}
	int cur = nd->op;
	ii l = get_steps(nd->left, k);
	ii r = get_steps(nd->right, k);
	bool le = 0, re = 0;
	if (nd->left->op == nd->op || nd->left->op == 0){
		le = 1;
	}
	if (nd->right->op == nd->op || nd->right->op == 0){
		re = 1;
	}
	int base = l.second + r.second;
	if (le && re){
		if (l.first + 1 + r.first < k){
			return mp(l.first + 1 + r.first, base);
		}
		else if (l.first + 1 + r.first == k){
			return mp(0, base+1);
		}
		else {
			if (l.first < r.first){
				return mp(l.first+1, base+1);
			}
			else {
				if (r.first + 1 == k){
					return mp(0, base+2);
				}
				else {
					return mp(r.first+1, base+1);
				}
			}
		}
	}
	else if (le){
		if (r.first != 0) base++;
		if (l.first + 1 == k){
			return mp(0, base+1);
		}
		else {
			return mp(l.first+1, base);
		}
	}
	else if (re){
		if (l.first != 0) base++;
		if (r.first + 1 == k){
			return mp(0, base+1);
		}
		else {
			return mp(r.first+1, base);
		}
	}
	else {
		if (l.first !=0 ) base++;
		if (r.first !=0 ) base++;

		if (k == 1){
			return mp(0, base+1);
		}
		return mp(1, base);
	}

}
ii get_time(node* nd, int k){
	// DUMP(nd->op);
	if (nd->op==0){
		return mp(0, 0);
	}
	int cur = nd->op;
	ii l = get_time(nd->left, k);
	ii r = get_time(nd->right, k);
	// DUMP(l.second); DUMP(l.first);
	// DUMP(r.second); DUMP(r.first);
	// DUMP(nd->op);

	bool le = 0, re = 0;
	if (nd->left->op == nd->op || nd->left->op == 0){
		le = 1;
	}
	if (nd->right->op == nd->op || nd->right->op == 0){
		re = 1;
	}
	int base = max(l.second, r.second);
	if (le && re){
		if (l.second > r.second){
			if (l.first == 0){
				if (k != 1)
					return mp(1, base+1);
				return mp(0, base+1);
			}
			else if (l.first + 1 < k){
				return mp(l.first + 1, base);
			}
			else {
				return mp(0, base);
			}
		}
		else if (l.second < r.second){
			if (r.first == 0){
				if (k!= 1)
					return mp(1, base+1);
				return mp(0, base+1);
			}
			else if (r.first + 1 < k){
				return mp(r.first + 1, base);
			}
			else {
				return mp(0, base);
			}
		}
		else {
			int net = l.first + r.first + 1;
			if (net == 1){
				if (k!=1){
					return mp(net,base+1);
				}
				return mp(0, base+1);
			}
			if (net < k){
				return mp(net, base);
			}
			else if (net == k){
				return mp(0, base);
			}
			else {
				return mp(0, base+1);
			}
		}
	}
	else if (le){
		if (r.second > l.second){
			if (k!= 1)
				return mp(1, base+1);
			return mp(0, base+1);
		}
		if (l.first == 0){
			if (k!= 1)
				return mp(1, base+1);
			return mp(0, base+1);
		}
		if (l.first + 1 < k){
			return mp(l.first + 1, base);
		}
		else {
			return mp(0, base);
		}
	}
	else if (re){
		if (l.second > r.second){
			if (k!= 1)
				return mp(1, base+1);
			return mp(0, base+1);
		}
		if (r.first == 0){
			if (k!= 1)
				return mp(1, base+1);
			return mp(0, base+1);
		}
		if (r.first + 1 < k){
			return mp(r.first + 1, base);
		}
		else {
			return mp(0, base);
		}
	}
	else {
		if (k != 1)
			return mp(1, base+1);
		else
			return mp(0, base+1);
	}

}

void solve(node& tree, int k){
	ii steps = get_steps(&tree, k-1);
	ii time = get_time(&tree, k-1);
	int ans = steps.second;
	if (steps.first) ans++;
	cout << ans << " " << time.second <<  endl;
}
signed main(){
	string s; cin >> s;
	stack<node> builder;
	vector<node> nodes;
	for (int i=0; i<s.size(); ++i){
		if (s[i] == 'e'){
			node cur = {NULL, NULL, -1, 0};
			builder.push(cur);
		}
		else {
			int code;
			if (s[i] == '*') code = 1;
			if (s[i] == '+') code = 2;
			node right = builder.top(); builder.pop();
			node left = builder.top(); builder.pop();
			right.i = nodes.size();

			nodes.push_back(right);
			node* to_right = &(nodes[nodes.size()-1]);

			left.i = nodes.size();
			nodes.push_back(left);
			node* to_left = &(nodes[nodes.size()-1]);

			node cur = {to_left, to_right, -1, code};
			builder.push(cur);
		}
	}
	node tree = builder.top();
	tree.i = nodes.size();
	nodes.push_back(tree);

	int n = (s.size()-1)/2;
	solve(tree, n+1);
	int t; cin >> t;
	

	while (t--){
		int k; cin >> k;
		solve(tree, k);
	}


	return 0;
}