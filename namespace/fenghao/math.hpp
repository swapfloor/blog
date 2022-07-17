#ifndef FENGHAO_MATH_HPP
#define FENGHAO_MATH_HPP 1

#include <vector>
#include <cstring>
#include <cmath>
using std::vector;

namespace fenghao {
    int p[100010], cnt = 0;//cnt线性筛素数的个数
    bool vis[100010];

    void pre() {//线性筛
        int n = 50000;
        memset(vis, 0, sizeof vis);
        for (int i = 2; i <= n; i++) {
            if (!vis[i]) p[cnt++] = i;
            for (int j = 0; p[j] <= n / i; j++) {
                vis[p[j] * i] = true;
                if (i % p[j] == 0) break;
            }
        }
    }

    int phi(int n) {//用公式phi(n)=n*((p1-1)/p1)*((p2-1)/p2)*...*((pk-1)/pk)
        if (!vis[n]) return n - 1;//如果n是质数，那么phi(n) = n - 1
        int res = n;
        int sqrtn = sqrt(n + 0.5);
        for (int i = 0; i < cnt && p[i] <= sqrtn; i++) {//对已经筛出的质数进行枚举
            if (n % p[i] == 0) {
                while (n % p[i] == 0) {
                    n /= p[i];
                }
                // printf("%d\n", p[i]);
                res /= p[i];//公式求解
                // printf("res:%d\n", res);
                res *= (p[i] - 1);
                // printf("res:%d\n", res);
                sqrtn = sqrt(n + 0.5);
            }
        }	
        if (n > 1) {//因为只筛了sqrt(n)如果sqrt(n)右边的数为质数则无法筛去，故其一定为质数。
            // printf("%d\n", n);
            res /= n;
            res *= (n - 1);
        }
        return res;
    }

    long long safe_mod(long long x, long long m) {
        x %= m;
        if (x < 0) x += m;
        return x;
    }

    constexpr long long pow_mod(long long x, long long n, int m = 1000000007) {
        if (m == 1) return 0;
        unsigned int _m = (unsigned int)(m);
        unsigned long long r = 1;
        unsigned long long y = safe_mod(x, m);
        while (n) {
            if (n & 1) r = (r * y) % _m;
            y = (y * y) % _m;
            n >>= 1;
        }
        return r;
    }

    int gcd_fact(int n) {
        long long res = 1;
        int sqrtn = sqrt(n + 0.5);
        int an = 0;//质数指数
        for (int i = 0; i < cnt && p[i] <= sqrtn; i++) {//对已经筛出的质数进行枚举
            an = 0;
            if (n % p[i] == 0) {
                while (n % p[i] == 0) {
                    n /= p[i];
                    an++;
                }
                res *= (an + 1) * pow_mod(p[i], an) - (an) * pow_mod(p[i], an - 1);//公式(a + 1)p^a + a * p^(a-1)
                sqrtn = sqrt(n + 0.5);
            }
        }	
        if (n > 1) {//因为只筛了sqrt(n)如果sqrt(n)右边的数为质数则无法筛去，故其一定为质数。
            // printf("%d\n", n);
            an = 1;
            res *= 2 * n - 1;//仍然根据公式进行了一个小小的简化。
        }
        return res;
    }

    int eulersum(int n) {
        return phi(n) / 2 * n;//可证明
    }

    int noncoinsum(int n) {
        return n - phi(n);
    }

    // int noncoinsum(int n) {//nlogn算法
    //     int res = 0;
    //     for (int i = 1; i <= n; i++) {
    //         if (__gcd(n, i) != 1) {
    //             res++;
    //         }
    //     }
    //     return res;
    // }

    int exeuler(int factor, int n) {//扩展欧拉定理：求解1<=a<=n, gcd(a, n) = factor中a的个数
        return phi(n / factor);//由欧几里得算法知：gcd(a / factor, n / factor) = 1, 1<=a/factor<=n/factor
                                //由欧拉定理可知改数对数即欧拉函数作用于n/factor
    }

    int gcd_sum(int n) {//利用公式：(a + 1)p^a + a * p^(a-1)
        gcd_fact(n);//复杂度同欧拉函数
    }
}

#endif