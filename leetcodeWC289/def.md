# a

按照题意模拟即可，递归好些一点我就写递归了，不过空间使用较多。🤣

# b

## 题描

给你一个数组，你每次可以挑选出其中相同数值的两个或者三个，请算出最少的挑选次数，如果不可能返回`-1`。

## 全析

返回`-1`的情况，数组中存在一个元素的数量为1。

当数组中一个元素的数量为$n(n\ge 2)$时，如何取次数最少？

### 解决方法

假设取$x$个2次和$y$个3次，$2x+3y=n$，尽量取3个。

设$t=\frac{n}{3}$，$2x$为偶数，所以$n$和$3y$同奇偶性，所以$n$和$y$同奇偶性。
- 如果$t$和$n$都是奇数，那么$y=t,ans=x+y=(n-3t)/2+t$
- 否则，那么$ans=(n-3t+3)/2+t-1$（凑巧）

# c

四方位前缀和。

求转弯路径积。

遍历$n\times m(n: rows, m: cols)$的每个点，求每个点周围的2的数量和5的数量，两垂直路径相加，然后取2和5数量较小值。

```c++
t[1] = w[i - 1][j][2], g[1] = w[i - 1][j][5];//up
t[2] = h[i][j - 1][2], g[2] = h[i][j - 1][5];//left
t[3] = w[m][j][2] - w[i][j][2], g[3] = w[m][j][5] - w[i][j][5];//bottom
t[4] = h[i][n][2] - h[i][j][2], g[4] = h[i][n][5] - h[i][j][5];//right
```

总共的可能有：
- up + left:      t[1] + t[2]
- up + right:     t[1] + t[4]
- left + bottom:  t[2] + t[3]
- bottom + right: t[3] + t[4]

我自己错误：
- 我是先求各方位2和5最小值，但是一想2可以和垂直路径的5进行积累成尾0
- 只判断转弯路径，题读错了。Return the maximum number of trailing zeros in the product of a **cornered** path found in grid.所以是四方位前缀而不是$\binom{4}{2}=6$种方位

**cornered** path: definition
```
A cornered path is defined as a set of adjacent cells with at most one turn.
cornered角落的，拐角的
```

# d

## 题描

给出一个从0开始的数组中各下标的父节点，0的父节点为-1，给出各下标对应的小写英文字符串，字符串构成一棵树。

## 思路

对一个结点，暴搜其子节点的链，取最长链和次长链的结点和加1。

## 做法

- 首先建邻接表，这个我惯性思维无向图建双边，其实只见一条父节点到儿子的边就好，原因：这题特殊在所有点都给出了父节点，比边的连接关系更加特殊。
- 注意是相邻不相同字母，我以为是字母表中相邻字母🤣。

```c++
int ans = 0;
int solve(int u, const std::vector<std::vector<int>>& g, const std::string& s) {
	int d1 = 0, d2 = 0;
	
	for (auto v : g[u]) {
		int d = solve(v, g, s);
		
		if (s[u] == s[v]) continue;
		
		if (d > d1) {
			d2 = d1;
			d1 = d;
		} else if (d > d2) {
			d2 = d;
		}
	}
	
	ans = std::max(ans, d1 + d2 + 1);
		
	return std::max(d1, d2) + 1;
}
```
