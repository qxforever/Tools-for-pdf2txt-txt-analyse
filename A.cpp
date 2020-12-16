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
	{"Israel", "ISR"},
	{"Japan", "JPN"},
	{"Kenya", "KEN"},
	{"Mexico", "MEX"},
	{"Nigeria", "NGA"},
	{"Korea, North—NDE", "PRK"},
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

int main() {
	string in = "01pdf\\April2006ChiefsDirectory.txt";
	freopen(in.c_str(), "r", stdin);
	// freopen("test2006.4.out", "w", stdout);
	string str;
	string name;
	freopen("total.txt", "w", stdout);
	for (int y = 2006; y <= 2006; y++) {
		int mon = 0;
		for (auto m : month) {
			mon++;
			if (m != "April") continue;
			stringstream ss;
			ss << y;
			string tostr; ss >> tostr;
			string addr = m + tostr + "ChiefsDirectory.txt";
			// freopen(addr.c_str(), "r", stdin);
			while (getline(cin, str)) {
				// fprintf(stderr, "%s\n", str.c_str());
				if (str == "The spellings of names of South Korean officials have been changed to reflect widely recognized spellings." ||
					str == "Cabinet" ||
					str == "Supreme People’s Assembly (SPA) Presidium" ||
					str == "North Korea is also known as the Democratic People’s Republic of Korea (DPRK)."
					)
					continue;
				if (str.back() == ' ') str.erase(--str.end());
				if (mp.count(str)) {
					name = mp[str];
					continue;
				}
				if (name == "") continue;
				fprintf(stderr, "%s\n", name.c_str());
				while (str.length() > 45 && !havecom(str)) {
					string tmp;
					getline(cin, tmp);
					if (str.back() == '\n') str.erase(--str.end());
					str += ' ';
					str += tmp;
				}
				int res = check(str);
				if (res == 0) {
					name = "";
				}
				else if (res == 1) {
					string u, v;
					work(str, u, v);
					cout << u << '\t' << v << '\t' << name << '\t' << mon << '\t' << y << '\n';
				}
				else continue;
			}
		}
	}
}