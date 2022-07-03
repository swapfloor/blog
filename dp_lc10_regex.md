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
