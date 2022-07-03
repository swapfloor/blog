# dp的一道例题

> 这是一道非常适合学习动态规划的一道例题。

## 题目描述

请实现一个函数用来匹配包括`'.'`和`'*'`的正则表达式。

模式中的字符`'.'`表示任意一个字符，而`'*'`表示它前面的字符可以出现任意次（含0次）。

在本题中，匹配是指字符串的所有字符匹配整个模式。

例如，字符串`"aaa"`与模式`"a.a"`和`"ab*ac*a"`匹配，但是与`"aa.a"`和`"ab*a"`均不匹配。

## 限制

- `1 <= s长度 <= 20`
- `1 <= p长度 <= 30`
- s仅包含小写英文字母
- p包含小写英文字母`'.'`和`'*'`.
- 保证每次出现字符`*`时，前面都匹配到有效的字符

## 题目全析

首先我们考虑自然的想法，给出两个只包含字母的字符串比较，可以用`return s == p;`。
如果想要递归实现：

```c++
bool isMatch(std::string s, std::string p) {
	if (p == "") return s == "";
	
	bool fsm = false; // fsm 表示两串的第一个字符是否匹配  全称first match
	fsm = s.size() >= 1 && s[0] == p[0];
	
	return fsm && isMatch(s.substr(1, s.size()),
		p.substr(1, p.size()));
}
```

- 如果模式串中包含`'.'`和`'*'`怎么处理

对于模式串p的第$i$位，加入正在和主串s的第$j$位进行比较，
- 仅包含小写字母`fsm = p[i] == s[j];`
- 如果模式串p的第$i$位为`'.'`时，那么主串第j位就不需要去询问了`fsm = p[i] == '.'`
- 如果模式串p的第$i+1$位为`'*'`时，有两种做法
  - 如果假设`'*'`左边的字母数为0，则模式串直接下移两位，变为模式串p的第$i+2$位，加入正在和主串s的第$j$位进行比较
  - 如果假设`'*'`左边的字母数为$n(n>0)$，则模式串首先需要满足两串的第一个字符匹配即`fsm == true;`，变为模式串p的第$i$位，加入正在和主串s的第$j+1$位进行比较

```c++
bool isMatch(std::string s, std::string p) {
	if (p == "") return s == "";
	
	bool fsm = false;
	fsm = s.size() >= 1 && (s[0] == p[0] || p[0] == '.');
	
	if (p.size() >= 2 && p[1] == '*') {
		return fsm && isMatch(s.substr(1, s.size()), p) 
			|| isMatch(s, p.substr(2, s.size()));
	} else {
		return fsm && isMatch(s.substr(1, s.size()),
			p.substr(1, p.size()));
	}
}
```

想一下这个算法的复杂度，看下图

![](https://github.com/swapfloor/blog/blob/main/images/dp_regex_lc_01.png)
原因：
- 程序会不断向下递归，假如每次递归进入函数本身需要操作一次的话，那么中间会有一些像①②相同的情况就会多进行一次操作，递归是栈操作也需要花费一定的时间。
- 如果`s1 == s2, p1 == p2;`则`isMatch(s1, p1) == isMatch(s2, p2);`一定成立。
结果：
- 我们可以用数组去记录这一状态，但是不要放入一整个字符串，这样很浪费时间，我们记录后续状态的起始坐标，可以在`substr`看出结尾坐标都是`str.size()`即结尾。

我们新创造一个函数名为dp即动态规划，dp(i, j)表示s的第i个位置到最后与p的第j个位置到最后的匹配即`isMatch(s.substr(i, s.size()), p.substr(j, p.size()));`。
然后关键是记录相同的状态，用一个数组f[i][j]去存储，有相同的状态我们可以直接返回状态，先将数组初始化为-1。

```c++
std::vector<std::vector<int>> f;
std::string s, p;
int n, m;

bool isMatch(std::string _s, std::string _p) {
	s = _s; p = _p;
	n = s.size();
	m = p.size();
	f = std::vector(n + 1, std::vector<int> (m + 1, -1));
	
	dp(0, 0);
}

bool dp(int x, int y) {
	if (f[x][y] != -1) return f[x][y];
	
	if (y == m) return f[x][y] = n == x;
	
	bool fsm = x < n && (s[x] == p[y] || p[y] == '.'); // x < n是问x在s的范围内，对于字符串递归来说就是s.size() >= 1
	
	if (y + 1 < m && p[y + 1] == '*') { // y + 1 < m 即p.size() >= 2
		f[x][y] = dp(x, y + 2) || fsm && bp(x + 1, y);
	} else {
		f[x][y] = fsm && dp(x + 1, y + 1);
	}
	return f[x][y];
}
```

只是将相同状态保存持续性的数据结构中存储称为“记忆化搜索”。

## 复杂度

将n, m作为s和p的长度。

### 普通递归版

最坏情况下，调用`isMatch(s[i:], p[2j:])`$\binom{i+j}{i}$次，调用s的时间次数为$n-i$，调用p时间为$m-2j$。因此时间复杂度为 $\sum_{i=0}^{n}\sum_{j=0}^{m/2}\binom{i+j}{i}O(n+m−i−2j)$。

算出来为$O((n+m)2^{n+m/2})$，空间复杂度$O(n^2+m^2)$

### 记忆化搜索

时间复杂度$O(nm)$，空间来点复杂度为$O(nm)$
