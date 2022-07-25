//两次bfs
/*
一次bfs将'B'(坏人)旁边的'.'(空格)变成'#'(墙)
一次bfs将终点(n,m)可到达的所有'.'(空格)和'G'(好人)设为true
最后遍历所有的点看看'G'是不是都为true

埋伏：如果终点有'B'(坏人)或者'#'(墙)就不能逃脱
启发来自教程
*/
#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

const int N = 55;

int n, m, dp[N][N];
char g[N][N];
bool ok, vis[N][N];

bool check(int x, int y) {
	return 1 <= x && x <= n && 1 <= y && y <= m;
}

bool jojo(char a, char b) {
	return (a == 'B' && b == 'G') || (a == 'G' && b == 'B');
}

void BFS() {
	queue<pair<int,int>> q;
	q.push({1, 1});
	while (!q.empty()) {
		auto t = q.front(); q.pop();
		int x = t.f;
		int y = t.s;
		
		if (vis[x][y]) continue;
		
		vis[x][y] = 1;
		
		if (check(x - 1, y)) {
			if (g[x][y] == 'B' && g[x - 1][y] == '.') g[x - 1][y] = '#';
			else if (g[x][y] == '.' && g[x - 1][y] == 'B') g[x][y] = '#';
			if (jojo(g[x][y], g[x - 1][y])) {
				ok = 0;
				return;
			}
			q.push({x - 1, y});
		}
		if (check(x + 1, y)) {
			if (g[x][y] == 'B' && g[x + 1][y] == '.') g[x + 1][y] = '#';
			else if (g[x][y] == '.' && g[x + 1][y] == 'B') g[x][y] = '#';
			if (jojo(g[x][y], g[x + 1][y])) {
				ok = 0;
				return;
			}
			q.push({x + 1, y});
		}
		if (check(x, y - 1)) {
			if (g[x][y] == 'B' && g[x][y - 1] == '.') g[x][y - 1] = '#';
			else if (g[x][y] == '.' && g[x][y - 1] == 'B') g[x][y] = '#';
			if (jojo(g[x][y], g[x][y - 1])) {
				ok = 0;
				return;
			}
			q.push({x, y - 1});
		}
		if (check(x, y + 1)) {
			if (g[x][y] == 'B' && g[x][y + 1] == '.') g[x][y + 1] = '#';
			else if (g[x][y] == '.' && g[x][y + 1] == 'B') g[x][y] = '#';
			if (jojo(g[x][y], g[x][y + 1])) {
				ok = 0;
				return;
			}
			q.push({x, y + 1});
		}
	}
}

void dfs() {
	if (g[n][m] == '#' || g[n][m] == 'B') return;
	queue<pair<int,int>> q;
	q.push({n, m});
	while (!q.empty()) {
		auto t = q.front(); q.pop();
		int x = t.f;
		int y = t.s;
		
		if (vis[x][y]) continue;
		
		vis[x][y] = 1;
		
		if (check(x - 1, y)) {
			if (g[x - 1][y] == 'G' || g[x - 1][y] == '.') {
				q.push({x - 1, y});
			}
		}
		if (check(x + 1, y)) {
			if (g[x + 1][y] == 'G' || g[x + 1][y] == '.') {
				q.push({x + 1, y});
			}
		}
		if (check(x, y - 1)) {
			if (g[x][y - 1] == 'G' || g[x][y - 1] == '.') {
				q.push({x, y - 1});
			}
		}
		if (check(x, y + 1)) {
			if (g[x][y + 1] == 'G' || g[x][y + 1] == '.') {
				q.push({x, y + 1});
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int T;
	cin >> T;
	
	while (T--) {
		memset(vis, 0, sizeof(vis));
		ok = 1;
		cin >> n >> m;
		for (int i = 1; i <= n; i ++ )
			for (int j = 1; j <= m; j ++ )
				cin >> g[i][j];
		BFS();
		if (!ok) {
			cout << "No\n";
			continue;
		}
    		//-debug()
		// for (int i = 1; i <= n; i ++ ) {
			// for (int j = 1; j <= m; j ++ )
				// cout << g[i][j];
			// cout << endl;
		// }
		memset(vis, 0, sizeof(vis));
		dfs();
    		//-debug()
		// for (int i = 1; i <= n; i ++ ) {
			// for (int j = 1; j <= m; j ++ )
				// cout << vis[i][j];
			// cout << endl;
		// }
		for (int i = 1; i <= n && ok; i ++ ) 
			for (int j = 1; j <= m && ok; j ++ ) 
				if (g[i][j] == 'G' && !vis[i][j])
					ok = 0;
		if (ok) cout << "Yes\n";
		else cout << "No\n";
	}
	return 0;
}
