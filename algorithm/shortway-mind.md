> 一些最短路的模板算法

## dijkstra(单源最短路算法)（处理非负权边）

### 裸的dijkstra算法，不用堆优化

复杂度及使用条件：O(n^2+m)，只能处理边权为正数的问题。
存储方式：邻接矩阵存储。

范围限制：1≤n≤500, 1≤m≤10^5

```c++
#include <bits/stdc++.h>

using namespace std;

const int N = 1010, INF = 1000000000;

int n, m;
int g[N][N], dist[N];
bool st[N];

void dijkstra() {
	for (int i = 1; i <= n; i++) {
		dist[i] = INF;
	} 
	
	dist[1] = 0;
	
	for (int i = 0; i < n; i++) {//表示从未知最短路径的顶点集合Q（n个元素）最终加到最短路径的顶点集合p中。
		int u, minx = INF;
		for (int j = 1; j <= n; j++) {//枚举u
			if (!st[j] && dist[j] < minx) {
				minx = dist[j];
				u = j;
			}
		}
		st[u] = true;
		for (int v = 1; v <= n; v++) {//枚举u周围的v，这有点像bfs
			if (dist[v] > dist[u] + g[u][v]) {
				dist[v] = dist[u] + g[u][v];
			}
		}
	}
}


int main() {
	cin >> m >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			g[i][j] = INF;
		}
	}
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		g[a][b] = g[b][a] = min(g[a][b], c);//邻接矩阵去重边。
	}
	dijkstra();
	cout << dist[n];
	return 0;
}
```

### dijkstra+堆优化

复杂度：O(mlogn)

范围限制：1≤n,m≤1.5×10^5，可以看见点数稍微一多，裸的dijkstra直接寄。

使用手写链表模拟的邻接表，

```c++
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#define sd second
#define fs first

using namespace std;

typedef pair<int, int> PII;

const int N = 1010, INF = 0x3f3f3f3f;

int h[N], e[N], ne[N], w[N], idx;
int n, m;
int dist[N];
bool st[N];

void add(int a, int b, int c) {
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

void init() {
	idx = 0;
	memset(h, -1, sizeof h);
}

int dijkstra() {
	memset(dist, 0x3f, sizeof dist);
	dist[1] = 0;
	priority_queue<PII, vector<PII>, greater<PII>> heap;
	heap.push({0, 1});// fs: dis  sd: idx
	
	while (heap.size()) {
		auto t = heap.top();
		heap.pop();
		
		int u = t.sd;
		
		if (st[u]) continue;
		st[u] = true;
		
		for (int i = h[u]; i != -1; i = ne[i]) {
			int v = e[i];
			if (dist[v] > dist[u] + w[i]) {
				dist[v] = dist[u] + w[i];
				heap.push({dist[v], v});
			}
		} 
	}
	
	if (dist[n] == 0x3f3f3f3f) return -1;
	return dist[n];
}

int main() {
	cin >> n >> m;
	init();
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		
		add(a, b, c);
	}
	cout << dijkstra() << "\n";
	return 0;
}
```

[练习1368. Minimum Cost to Make at Least One Valid Path in a Grid](https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/)

```c++
/*
 * @lc app=leetcode.cn id=1368 lang=cpp
 *
 * [1368] 使网格图至少有一条有效路径的最小代价
 */

复杂度为O(n^2)肯定能过，这里用堆优化来求O(mlogn)

// @lc code=start
typedef pair<int, int> PII;
class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        const int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        
        int r = grid.size();
        int c = grid[0].size();
        int dist[r][c];
        bool vis[r][c];
        
        memset(dist, 0x3f, sizeof dist);
        memset(vis, 0, sizeof vis);

        dist[0][0] = 0;

        priority_queue<PII, vector<PII>, greater<PII>> q;
        q.emplace(dist[0][0], 0 * c + 0);// 存dist和二维坐标的一维化(x, y) = x * c + y

        while (q.size()) {
            int t = q.top().second;
            int ux = t / c;// 将一维化坐标变成u点(ux, uy)
            int uy = t % c;
            q.pop();

            if (vis[ux][uy]) continue;
            vis[ux][uy] = true;

            for (int i = 0; i < 4; i++) {
                int vx = ux + dirs[i][0];
                int vy = uy + dirs[i][1];
                bool cost = grid[ux][uy] - 1 != i;// 枚举各个方位，如果与给出grid的不同方向则需要一个cost
                if (vx >= 0 && vx < r && vy >= 0 && vy < c && dist[vx][vy] > dist[ux][uy] + cost) {// 枚举v坐标合法，且花费更小
                    dist[vx][vy] = dist[ux][uy] + cost;
                    q.emplace(dist[vx][vy], vx * c + vy);// 将(vx, vy)一维化
                }
            }
        }

        return dist[r - 1][c - 1];
    }
};
// @lc code=end
```

## spfa(队列优化的Bellman-Ford算法)

时间复杂度平均情况下O(m)，最坏情况下O(nm), n 表示点数，m 表示边数

```c++
#include <bits/stdc++.h>

using namespace std;

const int N = 100010, INF = 0x3f3f3f3f;

int n, m;
int h[N], e[N], ne[N], w[N], idx;
int dist[N];
bool vis[N];

void init() {
	memset(h, -1, sizeof h);
	idx = 0;
	
	memset(dist, 0x3f, sizeof dist);
	dist[1] = 0;
}

void add(int a, int b, int c) {
	e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

void spfa() {
	queue<int> q;
	q.push(1);
	vis[1] = true;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = false;
		for (int i = h[u]; i != -1; i = ne[i]) {
			int v = e[i];
			if (dist[v] > dist[u] + w[i]) {
				dist[v] = dist[u] + w[i];
				if (!vis[v]) {
					vis[v] = true;
					q.push(v);
				}
			}
		}
	}
	
	if (dist[n] == INF) cout << "impossible\n";
	else cout << dist[n] << "\n";
}

int main() {
	cin >> n >> m;
	init();
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		
		add(a, b, c);
	}
	
	spfa();
	return 0;
}
```
