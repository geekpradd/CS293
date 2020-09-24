#include <bits/stdc++.h>
using namespace std;


int main(){
	cin.tie(NULL); ios_base::sync_with_stdio(false);
	int c, s, limit, ops;
	cin >> c >> s >> limit >> ops;
	vector<string> courses(c);
	vector<int> slots(c);
	vector<int> regl(c);
	vector< set<string> > bacche(c);

	map<string, int> index;
	for (int i=0; i<c; ++i){
		cin >> courses[i];
		cin >> slots[i] >> regl[i];
		index[courses[i]] = i;
	}
	vector<string> rolls(s);
	map<string, int> roller;
	for (int i=0; i<s; ++i){
		cin >> rolls[i];
	}
	cout << "huh" << endl;
	sort(rolls.begin(), rolls.end());
	for (int i=0; i<s; ++i){
		roller[rolls[i]] = i;
	}
	vector< set<string> > enrollment(s); 
	while (ops--){
		cout << "ok" << endl;
		cin.clear();
		string inp;
		cin >> inp;
		cout << "got " << inp << endl;
		stringstream ss(inp);
		string temp;
		vector<string> terms;
		while (getline(ss, temp, ' ')){
			if (temp != " ")
				terms.push_back(temp);
		}
		cout << terms.size() << endl;
		string code = terms[0];

		if (code == "R"){
			string roll, course;
			roll = terms[1]; course = terms[2];

			if (!roller.count(roll) || !index.count(course)){
				cout << "fail" << endl;
				continue;
			}
			int id = roller[roll];
			int cid = index[course];

			if (bacche[cid].count(roll)){
				cout << "fail" << endl;
			}	
			else if(enrollment[id].size() == limit){
				cout << "fail" << endl;
			}
			else {
				if (bacche[cid].size() == regl[cid]){
					cout << "fail" << endl;
				}
				else {
					int slot = slots[cid];
					bool pos = 1;
					for (string s: enrollment[id]){
						if (slots[index[s]] == slot){
							pos = 0;
							break;
						}
					}
					if (!pos){
						cout << "fail" << endl;
					}
					else {
						cout << "success" << endl;
						enrollment[id].insert(course);
						bacche[cid].insert(roll);
					}
				}
			}
		}
		else if (code == "D"){
			string roll, course;
			roll = terms[1]; course = terms[2];
			if (!roller.count(roll) || !index.count(course)){
				cout << "fail" << endl;
				continue;
			}
			int id = roller[roll];
			int cid = index[course];
			bool there = false;
			set<string>::iterator hmm;
			for (auto itr = enrollment[id].begin(); itr !=enrollment[id].end(); ++itr){
				if(*itr == course){
					there = 1; hmm = itr;
				}
			}
			if(!there){
				cout << "fail" << endl;
			}
			else{
				cout << "success"<< endl;
				enrollment[id].erase(hmm);
				bacche[cid].erase(roll);
			}
		}
		else if (code == "P"){
			if (terms.size() > 2){
				string f, s; f = terms[1], s = terms[2];
				if (f.size() == 8){
					if (roller.count(f) && roller.count(s)){
						int id1 = roller[f], id2 = roller[s];
						for (string x: enrollment[id1]){
							if (enrollment[id2].count(x)){
								cout << x << " ";
							}
						}
					}
				}
				else {
					if (index.count(f) && index.count(s)){
						int id1 = index[f], id2 = index[s];
						for (string x: bacche[id1]){
							if (bacche[id2].count(x)){
								cout << x << " ";
							}
						}
					}
				}
			}
			else {
				string oth = terms[1];
				if (oth.size() == 6){
					if (index.count(oth)){
						int cid = index[oth];
						for (auto itr = bacche[cid].begin(); itr != bacche[cid].end(); ++itr){
							cout << *itr << " ";
						}
					}
				}
				else {
					if (roller.count(oth)){
						int id = roller[oth];
						for (string s: enrollment[id]){
							cout << s << " ";
						}
					}
					
				}
			}
			cout << endl;

		}
	}
}