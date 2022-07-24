> 先来个数字三角形入入门

递推版：

```c++
#include<iostream>
using namespace std;
const int N=503;
int n,a[N][N],anr[N][N];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
			cin>>a[i][j];
	for(int i=2;i<=n;i++)
		for(int j=1;j<=i;j++){
			if(j==1)a[i][j]+=a[i-1][j];
			else if(j==i)a[i][j]+=a[i-1][j-1];
			else a[i][j]+=max(a[i-1][j-1],a[i-1][j]);
		}
	int ans=-5000010;
	for(int i=1;i<=n;i++)ans=max(ans,a[n][i]);
	cout<<ans<<"\n";
	return 0;
}
```

换个思路记搜其实才真的好写。

```c++
#include<bits/stdc++.h>
using namespace std;
const int N = 510;
int n, ans = -1e9;
int a[N][N], dp[N][N];
int dfs(int x, int y) {
	if (x <= 0 || y <= 0) return 0;
	int &ret = dp[x][y];
	if (ret != 0x3f3f3f3f) return ret;
	ret = a[x][y];
	if (y == 1) ret += dfs(x - 1, y);
	else if (x == y) ret += dfs(x - 1, y - 1);
	else ret += max(dfs(x - 1, y), dfs(x - 1, y - 1));
	if (x == n) ans = max(ans, ret);
	return ret;
}
int main() {
	memset(dp, 0x3f, sizeof(dp));
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++ ) {
		for (int j = 1; j <= i; j ++ ) {
			scanf("%d", &a[i][j]);
		}
	}
	dp[1][1] = a[1][1];
	for (int i = 1; i <= n; i ++ )
		dfs(n, i);
//  ##debug##
// 	for (int i = 1; i <= n; i ++ ) {
// 		for (int j = 1; j <= i; j ++ ) {
// 			printf("%d ", dp[i][j]);
// 		}
// 		puts("");
// 	}
// 	puts("");
	printf("%d\n", ans);
	return 0;
}
```
