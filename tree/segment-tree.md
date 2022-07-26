[来自Al.Cash](https://codeforces.com/blog/entry/18051)

> 线段树入门

## 点更新范围查询

实现

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5;  // limit for array size
int n;              // array size
int t[2 * N];

void build() {  // build the tree
  	for (int i = n - 1; i > 0; --i) t[i] = t[i << 1] + t[i << 1 | 1];
}

void modify(int p, int value) {  // set value at position p
  	for (t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
}

int query(int l, int r) {  // sum on interval [l, r)
  	int res = 0;
  	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    	if (l & 1) res += t[l++];
    	if (r & 1) res += t[--r];
  	}
  	return res;
}

int main() {
  	scanf("%d", &n);
  	for (int i = 0; i < n; ++i) scanf("%d", t + n + i);
  	build();
  	modify(0, 1);
  	printf("%d\n", query(3, 11));
  	return 0;
}
```

这里可能更接近算导，经典左闭右开[l, r)，数组下标从0开始

假设数组有n个元素，那么上面代码构建出的线段树具有2n-1个元素。

假设数组有16个元素，那么数组直接放在叶子上，叶子的长度为1，一个叶子可以写成[l, l]也可以写成[l, l + 1)。数组在树的[n, 2 * n)

整棵树可以写成[1, 2 * 16)

- **build**: 建树之前我们需要给叶子结点直接赋值，有了叶子，当我们获取到2 * i和2 * i + 1的值后，那么i处的值可以直接被推出来。类似的相当于线段树是递归分治，我们可以通过dp先求下面的，继而往上推获得答案，最后达到根节点。

- `for (int i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];`可以看见最终的根为1，因为1有两个儿子2和3，而0只有1个儿子。（如果考虑0的左儿子会将自己锁死，`2 * 0 == 0`）

- **modify**: 将数组中的位置更改它的值，数组的位置pos其中$pos\in [0,n)$对应树的位置pos+n  $pos+n\in[n,2n)$

- 实现上与build有点类似

- 性质：偶数左儿子，奇数右儿子。有了这一个性质便可以推出query的实现，对于[l,r)如果l为奇数，那么它不可能是2的幂次方的区间，只能自己一个人冲，所以就`if (l & 1) res += t[l ++ ];`，对于l来说，因为是开区间，所以如果r为奇数那么r-1为偶数左儿子，也不能是2的幂次方的区间，所以`if (r & 1) res += t[-- r];`，下一步l ++ 后l我们跳过了原来res加过的左区间，因为左闭，-- r后我们仍然在res加过的区间，但是因为是右开我们不取，然后同时取父节点`l >>= 1, r >>= 1`，左边取得永远是l，右边取的永远是r-1

## 范围更新点查询

- 在[l, r]区间中给每个元素加上一个x
- 求某个点的值

> 跟BIT非常像了吧。

