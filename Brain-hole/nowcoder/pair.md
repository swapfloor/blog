[练习题](https://ac.nowcoder.com/acm/problem/238581)

> 牛客脑洞题很多适合练习

设计到这种二进制计算可以找规律，当两个数位数不同时，高位的与一定小于异或，所以只能同数位，当同数位时必然满足条件，0和任意一个数字都不满足条件。

两两结合组合数$\binom{n}{2}$

```c++
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,t,ans=0;
    long long d[33];
    memset(d,0,sizeof(d));
    scanf("%d",&n);
    while(n--){
        scanf("%d",&t);
        if(t){
            ans=0;
            while(t)t>>=1,ans++;
            d[ans]++;
        }
    }
    long long res=0;
    for(int i=1;i<=32;i++)res+=d[i]*(d[i]-1)/2;
    printf("%lld",res);
    return 0;
}
```
