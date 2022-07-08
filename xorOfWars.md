[War of XORs](https://www.codechef.com/problems/XORIER?itm_medium=potd&itm_campaign=potd)

## 题目描述

给定一个长度为N的序列a，找出有多少对(i, j)($1\le i < j <\le n$)满足$a_i\oplus a_j$等于两个质数(两个质数可以相等)的和，两个质数奇偶性
相同。

## 限制

- $1\le N \le 10^5$

## 困难

我开始没看到n的范围直接枚举了，TLE罚坐。

首先我们又定理知道一个大于2的偶数可以表示为两个质数的和。（这里两个质数均为奇数）

- 奇数跟奇数的xor为偶数

- 偶数跟偶数的xor也为偶数

所以设偶数有n个，不同下标的偶数的组合为$\binom{n}{2}=\frac{n\times (n-1)}{2}$

### 去掉某些不符合规则的元素

当两个数相同时，xor为0，不符合。

xor为2的也需要去掉。直接枚举即可。

```c++
// [War of XORs](https://www.codechef.com/problems/XORIER?itm_medium=potd&itm_campaign=potd)
#include <bits/stdc++.h>

using i64 = long long;

constexpr int MAXN = 1e6;

void solve() {
	int n;
	std::cin >> n;
	
	std::vector<int> a(n, 0); // 除了a数组其余数据尽量用64位有符号整数，防止溢出。
	std::vector<i64> z(2, 0);
	std::vector<i64> mp(MAXN + 1, 0);   
	for (auto &k : a) {
		std::cin >> k;
		z[k % 2]++;     // 奇数桶和偶数桶
		mp[k]++;        // 元素入桶
	}
	
	i64 ans = z[0] * (z[0] - 1) / 2 + z[1] * (z[1] - 1) / 2;    对所有的奇数和偶数分别组合。
	
	for (auto m : mp) {
		ans -= m * (m - 1) / 2;     // 减去相同的元素。对奇数或者对偶数组合时会出现下标不同但是数值相同的元素组合，需要减去。
	}
	
	for (auto m : a) {
		if (m ^ 2 <= MAXN && mp[m ^ 2]) {
			ans -= mp[m] * mp[m ^ 2];
			mp[m] = mp[m ^ 2] = 0;      // 对于已经去掉了m和m^2，后续可能会遍历到m^2，这时清零后会出现ans -= mp[m] = 0 * mp[m ^ 2] = 0，这样不会出现减多了的情况。
		}
	}
	
	std::cout << ans << "\n";
}

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}

	return 0;
}
```
