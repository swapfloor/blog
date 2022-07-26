//tag: dp greedy math *1100
/*
一道有意思的dp，标签可以看到是1100，题读了8遍才理解了题意（比赛吃大亏）
我的ac代码可以说是非常简洁，这个dp不像其他dp有一堆状态转移方程，通过题目，我们得到了一个规律，当两个相同颜色的块中间间隔了偶数个块，他们能够堆在一起形成一个塔，相差步数为1，3，5，这样的奇数数字
因此对每一个颜色，保留一个奇数桶和一个偶数桶，分别对应奇数下标该颜色的最大和偶数下标该颜色对应的最大。
偶数由奇数转移：mp[b[i]][0] = mp[b[i]][1] + 1;
奇数由偶数转移：mp[b[i]][1] = mp[b[i]][0] + 1;
对应我的代码中：mp[b[i]][i % 2] = mp[b[i]][(i % 2) ^ 1] + 1;
^可以在两个数字当且仅当他们二者最小比特位不同时形成一个异或环，比如2和3，4和5 4^1=5 5^1=4 4(100)5(101)
*/
#include <bits/stdc++.h>
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
		int n;
		cin >> n;
		
		vector<vi> mp(n + 1, vi(2, 0)); 
		vi dp(n + 1, 0), b(n + 1, 0);
		
		for (int i = 1; i <= n; i ++ ) {
			cin >> b[i];
		}
		
		for (int i = 1; i <= n; i ++ ) {
			mp[b[i]][i % 2] = mp[b[i]][(i % 2) ^ 1] + 1;//非常巧妙
		}
		
		for (int i = 1; i <= n; i ++ )
			cout << max(mp[i][0], mp[i][1]) << " ";
		cout << "\n";
	}
	return 0;
}
