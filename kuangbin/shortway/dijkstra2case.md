> 两道dijkstra习题

# t1(frogger)

**青蛙希望，它的跳跃过程中，单次跳跃的最长距离尽可能短。**

假设我们先枚举一个u，然后枚举一个v，用`dist`记录答案，用`g[x][y]`记录x点到y点的距离。

那么怎么松弛，最长距离尽可能小，重点在**小**而不再**长**，分析谓词强弱时，一般重点在话的后面。

根据离散数学可知，我们先取邻边的最大值即单次跳跃的最长距离，然后对这些最长距离取min。即$min(max(dist(u), g[u][v]))$

```c++
void dijkstra() {
	for (int i = 2; i <= n; i++) {
		dist[i] = dis(1, i);
	}
	dist[1] = 0;
	memset(vis, 0, sizeof vis);
	vis[1] = 0;
	
	for (int i = 1; i <= n; i++) {
		int u;
		double minx = INF;
		for (int j = 1; j <= n; j++) {
			if (!vis[j] && dist[j] < minx) {
				u = j;
				minx = dist[j];
			}
		}
		
		vis[u] = true;
		
		for (int v = 1; v <= n; v++) {
			if (dist[v] > max(dist[u], dis(u, v))) {
				dist[v] = max(dist[u], dis(u, v)); // 这里也可以写成dist[v] = min(dist[v], max(dist[u], dis(u, v)))
			}
		}
	}
}
```

# t2(heavy transportation)

这题正好和frogger这道题反过来了，前面是最长距离尽可能小，这题是最短板尽量长，松弛操作就是即$max(min(dist(u), g[u][v]))$

```c++
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iomanip>

using namespace std;

const int N = 1010, INF = 0x3f3f3f3f;

int n, m, g[N][N];
int dist[N];
bool vis[N];

void dijkstra() {
	for (int i = 2; i <= n; i++) {
		dist[i] = g[1][i];
	}
	dist[1] = 0;
	memset(vis, 0, sizeof vis);
	
	for (int i = 1; i <= n; i++) {
		int u, minx = 0;
		for (int j = 1; j <= n; j++) {
			if (!vis[j] && minx < dist[j]) {
				u = j;
				minx = dist[j];
			}
		}

		vis[u] = true;
		
		for (int v = 1; v <= n; v++) {
			if (dist[v] < min(dist[u], g[u][v])) {
				dist[v] = min(dist[u], g[u][v]);
			}
		}
	}
}

int main() {
	int sce = 1;
	cin >> sce;
	for (int i = 1; i <= sce; i++) {
		cout << "Scenario #" << (i) << ":\n";
		memset(g, 0, sizeof g);
		cin >> n >> m;
		for (int i = 1; i <= m; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			g[a][b] = g[b][a] = c;
		}
		dijkstra();
		cout << dist[n] << "\n\n";
	}
	return 0;
}
```

那么大家肯定是知道我不会写堆优化了，我先放个板子吧。

- 堆优化
```c++
void dijkstra_heap() {
	memset(dist, 0x3f, sizeof dist);
	dist[1] = 0;
	priority_queue<PII, vector<PII>, greater<PII>> q;
	q.emplace(dis[s], idx[s]);// first是到起点的距离，second是下标
	
	while (!q.empty()) {
		auto t = q.top();
		q.pop();
		
		int u = t.second;
		
		if (vis[u]) continue;
		vis[u] = true;
		
		for (auto v : g) {
			// 松弛公式
			q.emplace(dist[v], v);
		}
	}
}
```
