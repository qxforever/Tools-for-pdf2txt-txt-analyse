#include <bits/stdc++.h>
using namespace std;

using pss = pair<string, string> ;

const string Cont = "(continued)";

map<string, string> mp = map<string, string> {
	{"Argentina", "ARG"},
	{"Australia", "AUS"},
	{"Brazil", "BRA"},
	{"Canada", "CAN"},
	{"Chile", "CHL"},
	{"China", "CHN"},
	{"France", "FRA"},
	{"Germany", "DEU"},
	{"Ghana", "GHA"},
	{"Greece", "GRC"},
	{"India", "IND"},
	{"Indonesia", "IDN"},
	{"Iran—NDE", "IRN"},
	{"Iran - NDE", "IRN"},
	{"Israel", "ISR"},
	{"Japan", "JPN"},
	{"Kenya", "KEN"},
	{"Mexico", "MEX"},
	{"Nigeria", "NGA"},
	{"Korea, North—NDE", "PRK"},
	{"Korea, North - NDE", "PRK"},
	{"Pakistan", "PAK"},
	{"P Pakistan", "PAK"},
	{"Peru", "PER"},
	{"Russia", "RUS"},
	{"South Africa", "ZAF"},
	{"Korea, South", "KOR"},
	{"Spain", "ESP"},
	{"Turkey", "TUR"},
	{"United Kingdom", "GBR"},
	{"USA", "USA"}
};

string month[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

int check(const string &str) {
	if (str.find(Cont) != string::npos) return 2;
	bool f = 0, g = 0, h = 0;
	for(const auto &c : str) {
		if (isdigit(c)) f = 1;
		else if (c == '.') return 1;
		else h = 1;
	}
	if (f && !g && !h) return 2;
	return 0;
}

void work(const string &str, string &u, string &v) {
	int n = str.size();
	int ed = 0;
	for (int i = 0; i < n; i++) {
		if (str[i] == '.' && str[i + 1] == '.' && str[i + 2] == '.') break;
		u += str[i];
	}
	for (int i = n - 1; i >= 0; i--) {
		if (str[i] == '.' && str[i - 1] == '.' && str[i - 2] == '.') {
			ed = i;
			break;
		} 
	}
	for (int i = ed + 1; i < n; i++) v += str[i];
}

bool havecom(string s) {
	int sz = s.size();
	for (int i = 0; i + 3 < sz; i++) {
		if (s[i] == '.' && s[i + 1] == '.' && s[i + 2] == '.') return 1;
	}
	return 0;
}

void split(const string &s, vector<string> &v, const string &c) {
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2) {
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}

map<string, set<string>> table;
map<string, string> last;
bool vis[200010];

void Pre() {
	string s, t;
	freopen("table.txt", "r", stdin);
	while (!cin.eof()) {	
		cin >> s;
		getchar();
		getline(cin, t);
		while (t.size() && t.back() == ' ') t.erase(t.size() - 1);
		t += ' ';
		table[s].insert(t);
		last[s] = t;
	}
	cin.clear();
	fclose(stdin);
}

int main() {
	string str;
	string name;
	Pre();
	freopen("total1.txt", "w", stdout);
#ifdef debug
	for (const auto &i : table) {
		cout << i.first << '\n';
		for (const auto &j : i.second) {
			cout << j << '\n';
		}
	}
#endif
	for (int y = 2014; y <= 2015; y++) {
		fprintf(stderr, "%d\n", y);
		int mon = 0;
		for (auto m : month) {
			mon++;
			stringstream ss;
			ss << y;
			string tostr; ss >> tostr;
			string addr = m + tostr + "ChiefsDirectory.txt";
			freopen(addr.c_str(), "r", stdin);
			bool _read = 1;
			while (!cin.eof()) {
				if (_read) getline(cin, str);
				else _read = 1;
				// fprintf(stderr, "%s\n", name.c_str());
				if (str.back() == ' ') str.erase(--str.end());
				if (str == "The spellings of names of South Korean officials have been changed to reflect widely recognized spellings." ||
					str == "Cabinet" ||
					str == "Supreme People’s Assembly (SPA) Presidium" ||
					str == "Supreme People’s Assembly (SPA)" ||
					str == "North Korea is also known as the Democratic People’s Republic of Korea (DPRK)." ||
					str == "Min. of State for Foreign Affairs Lawan GANA-GUBA"
					)
					continue;
				if (mp.count(str)) {
					name = mp[str];
					continue;
				}
				if (name == "") continue;
				
				vector<string> words;
				string _split = " ";
				split(str, words, _split);
#ifdef debug
				printf("name = %s str = %s\n", name.c_str(), str.c_str());
#endif
				string _cur = "";
				int flag = 0;
				for (int i = 0; i < (int)words.size(); i++) {
					_cur += words[i];
					_cur += ' ';
#ifdef debug
					printf("cur = %s\n", _cur.c_str());
#endif
					if (table[name].count(_cur)) {
						string __cur = " ";
						for (int j = i + 1; j < (int) words.size(); j++) {
							__cur += words[j];
						}
						cout << _cur << '\t' << __cur << '\t' << name << '\t' << mon << '\t' << y << '\n';
						if (_cur == last[name]) name = "";
						flag = 1;
						break;
					}
				}
				if (!flag) {
					getline(cin, str);
					words.clear();
					split(str, words, _split);
					for (int i = 0; i < (int)words.size(); i++) {
						_cur += words[i];
						_cur += ' ';
#ifdef debug
						printf("cur = %s\n", _cur.c_str());
#endif
						if (table[name].count(_cur)) {
							string __cur = " ";
							for (int j = i + 1; j < (int) words.size(); j++) {
								__cur += words[j];
							}
							cout << _cur << '\t' << __cur << '\t' << name << '\t' << mon << '\t' << y << '\n';
							if (_cur == last[name]) name = "";
							flag = 1;
							break;
						}
					}
				}
				if (!flag) _read = 0;
			}
			cin.clear();
			fclose(stdin);
		}
	}
}