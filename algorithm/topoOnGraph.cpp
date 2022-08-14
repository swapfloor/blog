vi a[V];//邻接表
bool vis[V];
vi ans;
int cnt;
void topo(int u,vi a[]){
  vis[u]=true;
  for(auto v:a[u]){
    if(!vis[v]){
      topo(v,a);//先dfs到没有出度的点，将该点添加到栈中，这样优先级高的先入栈，最后取出
    }
  }
  ans[--cnt]=u;
}
int main(){
  INT(V);
  ans.resize(V);
  cnt=V;
  rep(i,0,V){
    if(!vis[i]){
      topo(i,a);//有些点可能不在一个群内部，所有不能用dfs搜到，我们添加一个vis数组去记录已经遍历的点。
    }
  }
}
// 以前写这个版本太朴素了。后面出y总的版本
#include <bits/stdc++.h>

using namespace std;

const int N = 100005;

int n, m;
int h[N], e[N], ne[N], idx;
int q[N];
int d[N];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

bool topo() {
    int hh = 0, tt = 0;
    for (int i = 1; i <= n; i++) {
        if (!d[i]) {
            q[tt++] = i;//加入多源
        }
    }
    while (hh < tt) {//队列
        int t = q[hh++];
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (--d[j] == 0) {
                q[tt++] = j;
            }
        }
    }
    return tt == n;
}

int main() {
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    while (m--) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
        d[b]++;
    }
    if (topo()) {
        for (int i = 0; i < n; i++) {
            printf("%d ", q[i]);
        }
        puts("");
    } else {
        puts("-1");
    }
}
