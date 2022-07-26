//div3的d题，一道贪心题目
//搞一个字母桶，贪心策略，优先去掉字典序较大的字母。
#include <bits/stdc++.h>
#define de(x) cout << #x << " = " << x << endl;
#define f first
#define s second

using namespace std;

typedef vector<int> vi;

const int N = 55;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int T;
	cin >> T;
	
	while (T--) {
		string s;
		cin >> s;
		
		int w;
		cin >> w;
		
		vector<int> mp(27, 0);
		
		int cnt = 0;
		for (auto i : s) {
			mp[i - 'a' + 1] ++ ;
			cnt += (i - 'a' + 1);
		}
		
		// for (int i = 1; i <= 26; i ++ )//debug
			// cout << mp[i] << (char)(i + 'a' - 1) <<  "\n";
		
		while (cnt > w) {
			for (int i = 26; i >= 1; i -- ) {
				if (mp[i]) {
					int t = ceil((cnt - w) / (i + 0.0));
					if (t > mp[i]) t = mp[i];
					mp[i] -= t;
					cnt -= t * i;
				}	
			}
		}

		// for (int i = 1; i <= 26; i ++ )//debug
			// cout << mp[i] << (char)(i + 'a' - 1) <<  "\n";
		
		for (auto i : s)
			if (mp[i - 'a' + 1]) {
				cout << i;
				mp[i - 'a' + 1] -- ;
			}

		cout << "\n";
	}
	return 0;
}
