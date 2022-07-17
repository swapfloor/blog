int p[100010], cnt = 0;//cnt线性筛素数的个数
bool vis[100010];

void pre() {//线性筛
    int n = 50000;
    memset(vis, 0, sizeof vis);
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) p[cnt++] = i;
        for (int j = 0; p[j] <= n / i; j++) {
            vis[p[j] * i] = true;
            if (i % p[j] == 0) break;
        }
    }
}
