> 一些最短路的模板算法

## dijkstra

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
