> 一篇关于树状数组的入门程序

树状数组可以解决一些**RMQ**问题。

树状数组的代码比较好写，首先是一维求和建树，以1为下标起点，以0为下标起点的程序基本也用不上。

## 点更新，范围查询

### 一维求和

```c++
//以1为下标起点
#include<bits/stdc++.h>
using namespace std;
int n, b[100010];
void add(int id, int val) {
	for (; id <= n; id += id & -id)
		b[id] += val;
}
int sum(int r) {
	int ret = 0;
	for (; r >= 1; r -= r & -r) {
		ret += b[r];
	}
	return ret;
}
int get(int l, int r) {
	return sum(r) - sum(l - 1);
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++ ) {
		int x;
		scanf("%d", &x);
		add(i, x);
	}
	int q;
	scanf("%d", &q);
	while (q--) {
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%d\n", get(l, r));
	}
	return 0;
}
```

```c++
//以0为下标起点
#include<bits/stdc++.h>
using namespace std;
int n, b[100010];
void add(int id, int val) {
	for (; id < n; id = id | (id + 1))
		b[id] += val;
}
int sum(int r) {
	int ret = 0;
	for (; r >= 0; r = ((r + 1) & r) - 1) {
		ret += b[r];
	}
	return ret;
}
int get(int l, int r) {
	return sum(r) - sum(l - 1);
}
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i ++ ) {
		int x;
		scanf("%d", &x);
		add(i, x);
	}
	int q;
	scanf("%d", &q);
	while (q--) {
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%d\n", get(l, r));
	}
	return 0;
}
```

### 二维求和(1-index)

```c++
#include<bits/stdc++.h>
using namespace std;
int n, b[1010][1010];
void add(int x, int y, int val) {
	for (int i = x; i <= n; i += i & (-i))
		for (int j = y; j <= n; j += j & (-j))
			b[i][j] += val;
}
int sum(int x, int y) {
	int ret = 0;
	for (int i = x; i >= 1; i -= i & (-i))
		for (int j = y; j >= 1; j -= j & (-j))
			ret += b[i][j];
	return ret;
}
int get(int x1, int y1, int x2, int y2) {
	return sum(x2, y2) - sum(x2, y1 - 1) - sum(x1 - 1, y2) + sum(x1 - 1, y1 - 1);
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++ ) {
		for (int j = 1; j <= n; j ++ ) {
			int x;
			scanf("%d", &x);
			add(i, j, x);
		}
	}
	int q;
	scanf("%d", &q);
	while (q--) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		printf("%d\n", get(x1, y1, x2, y2));
	}
	return 0;
}
```

## 范围更新，点查询

如何在[l,r]区间每个点加上一个x？需要两个点更新操作`add(l,x)`和`add(r+1,-x)`，此时维护的是一个增量的树状数组。

```c++
#include<bits/stdc++.h>
using namespace std;
int n, m, a[10010], b[10010];//a表示原数组，b表示增量树状数组
void add(int id, int val) {
	for (int i = id; i <= n; i += i & (-i))
		b[i] += val;
}
int sum(int r) {
	int ret = 0;
	for (int i = r; i >= 1; i -= i & (-i))
		ret += b[i];
	return ret;
}
int get(int l, int r) {
	return sum(r) - sum(l - 1);
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i ++ ) {
		scanf("%d", &a[i]);
	}
	while (m--) {
		int l, r, val;
		scanf("%d%d%d", &l, &r, &val);
		add(l, val);
		add(r + 1, -val);
	}
	for (int i = 1; i <= n; i ++ ) {
		printf("%d ", b[i]);
	}
	puts("");
	int q;
	scanf("%d", &q);
	while (q--) {
		int x = 0;
		scanf("%d", &x);
		printf("%d\n", a[x] + sum(x));
	}

	return 0;
}
```

## 范围更新，范围查询

这里维护两个BIT分别为B1，B2，更新方法为`add(B1,l,x)add(B1,r+1,-x)add(B2,l,x*(l-1))add(B2,r+1,-x*r)`，查询公式为`sum(B1,i)*i-sum(B2,i)`

```c++
#include<bits/stdc++.h>
using namespace std;
int n, m, a[10010], b1[10010], b2[10010];//a表示原数组，b1,b2表示增量树状数组
void add(int b[], int id, int val) {
	for (int i = id; i <= n; i += i & (-i))
		b[i] += val;
}
int sum(int b[], int r) {
	int ret = 0;
	for (int i = r; i >= 1; i -= i & (-i))
		ret += b[i];
	return ret;
}
int presum(int r) {
	return sum(b1, r) * r - sum(b2, r);
}
int get(int l, int r) {
	return presum(r) - presum(l - 1);
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i ++ ) {
		scanf("%d", &a[i]);//原数组根据选择去操作输出
	}
	while (m--) {
		int l, r, val;
		scanf("%d%d%d", &l, &r, &val);
		add(b1, l, val);
		add(b1, r + 1, -val);
		add(b2, l, (l - 1) * val);
		add(b2, r + 1, -r * val);
	}
	int q;
	scanf("%d", &q);
	while (q--) {
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%d\n", get(l, r));
	}
	return 0;
}
```
