# 一些数学知识备忘录的理解全析

> 之前是看到小岛那里有一个男人八题（楼教主出的），打开一看是一份数学备忘清单，里面有超多的acm数学公式，当然我这里还会写一些y总的数学，他的数学功底是很好的。

## yxc数学大全

### 快速选择（应用于序列第k小数或k大数）复杂度为O(n)

## 奇数平方和

> 来自[Perplexboy](https://www.zhihu.com/people/a-tuan-14)

已知

$$
\sum_{k=1}^{n}k^2=\frac{1}{6}n(n+1)(2n+1)
$$

因此

$$
\sum_{k=1}^{n}(2k-1)^2
$$

$$
=\sum_{k=1}^{2n}k^2-\sum_{k=1}^n(2k)^2
$$

$$
=\frac{1}{3}n(2n+1)(4n+1)-4\sum_{k=1}^{n}k^2
$$

$$
=\frac{1}{3}n(2n+1)(4n+1)-\frac{2}{3}n(n+1)(2n+1)
$$

$$
=\frac{1}{3}n(2n+1)(2n-1)
$$

思路：奇数平方和等于总数平方和减去偶数平方和，

偶数平方和为

$$
\sum_{k=1}^n(2k)^2=\frac{2}{3}n(n+1)(2n+1)
$$

```c++
long long sumOfQuareOdd(int n) {
    //1到n中的奇数平方和
    
    long long x = n >> 1;//多少个奇数
    if (n & 1) x ++ ;
    
    return x * (2 * x + 1) * (2 * x - 1) / 3;
}
long long sumOfQuareEven(int n) {
    //1到n中的偶数平方和
    
    long long x = n >> 1;
    
    return x * (x + 1) * (2 * x + 1) / 3 * 2;
}
```

立方和：

$$
\sum_{k=1}^{n}k^3=\frac{1}{4}n^2(n+1)^2
$$

```c++
//计算[min(n,m),max(n,m)]段连续的整数中所有偶数的平方和以及所有奇数的立方和。
#include<bits/stdc++.h>
using namespace std;
long long sumOfQuareOdd(int n) {
    //1到n中的奇数平方和
    
    long long x = n >> 1;//多少个奇数
    if (n & 1) x ++ ;
    
    return x * (2 * x + 1) * (2 * x - 1) / 3;
}
long long sumOfQuareEven(int n) {
    //1到n中的偶数平方和
    
    long long x = n >> 1;//多少个偶数
    
    return x * (x + 1) * (2 * x + 1) / 3 * 2;
}
long long sumOfCubeOdd(int n) {
    //1到n中的奇数立方和
    
    long long x = n >> 1;//多少个奇数
    if (n & 1) x ++ ;
    
    return x * x * (2 * x * x - 1);
}
int main(){
    int n, m;
    while (cin >> n >> m) {
        if (n > m) swap(n, m);
        cout << sumOfQuareEven(m) - sumOfQuareEven(n - 1) << " "
             << sumOfCubeOdd(m) - sumOfCubeOdd(n - 1) << "\n";
    }
	return 0;
}
```
