> 这里包含了我的一些dp练习题及题目解析

## 最长回文子串

[练习](https://leetcode.com/problems/longest-palindromic-substring/)

![](https://github.com/swapfloor/blog/blob/main/images/dp0.png)

dp问题有一个**重复计算的子结构**，本题也可以定义一个P(x, y)表示Sx...Sy是一个回文串。

- 当Sx...Sy是一个回文串时，P(x, y) = true;

- 否则P(x, y) = false;

我们可以弄出P的一个计算方法，P(x, y) = (P(x + 1, y - 1) and Sx == Sy)

dp跟暴搜的区别无非就是一个少时间，一个少空间，我们要尽量少时间，问题具体处理方式相同，dp选择了记住它。

拿到了**集合**和**状态计算**，还要一个base就是dfs的**基础条件**，**最小区间返回**。

得出了基础条件时，p(x, x) = true;

```c++
class Solution {
public:
    string longestPalindrome(string s) {
        int z = s.size();
        bool dp[z + 1][z + 1];
        
        memset(dp, 0, sizeof dp);

        for (int i = 0; i <= z; i++) dp[i][i] = true;

        int ans = 0;
        int x = 0, y = 0;
        for (int len = 1; len < z; len++) {
            for (int i = 0; i + len < z; i++) {
                int j = i + len;
                if (len == 1) {
                    dp[i][j] = s[i] == s[j];
                } else {
                    dp[i][j] = dp[i + 1][j - 1] && (s[i] == s[j]);
                }

                if (dp[i][j] && len > ans) {
                    x = i, y = j;
                    ans = len;
                }
            }
        }
        
        return std::string(s.begin() + x, s.begin() + y + 1);
    }
};
```

## 邻边绝对值之和

[练习](https://ac.nowcoder.com/acm/contest/11230/D)

> 一道新题

n到10的5次方的数量级，所以n^2就不行了，暴搜肯定不行，根据一些数学经验可以先分析一下。

首先当b的每个元素都不是1时下界是0？不可能是0，why？

我们都会想一个取1，一个取`b[i]`，但是后面如果取`b[i]`呢？所以下界是$\sum_{i = 2}^{n} abs(b[i] - b[i - 1])$

所以可以取1或者取最大，取1就是取最小为0，取b就是取最大就是1。

```c++
#include <bits/stdc++.h>

using i64 = long long;

bool vis[200002];

void solve() {
	  int n;
	  std::cin >> n;
	  
	  std::vector<int> a(n + 2, 0);
	  std::vector<std::vector<int>> dp(n + 2, std::vector<int> (2, 0));
	  
	  for (int i = 1; i <= n; i++) {
	  	std::cin >> a[i];
	  }
	  
	  for (int i = 2; i <= n; i++) {
	  	dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + abs(1 - a[i - 1]));
	  	dp[i][1] = std::max(dp[i - 1][0] + abs(1 - a[i]), dp[i - 1][1] + abs(a[i] - a[i - 1]));
	  }  
	  std::cout << std::max(dp[n][0], dp[n][1]) << "\n";
}

int main(){
	  std::ios::sync_with_stdio(false);
	  std::cin.tie(nullptr);
	  
	  solve();

	  return 0;
}
```
