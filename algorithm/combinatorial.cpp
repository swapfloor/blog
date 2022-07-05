/* 组合数求解大礼包 */

/*-------------------------------------------------------------------*/
// 杨辉递推式求解组合数，直接利用公式c(n, m) = c(n - 1, m) + c(n - 1, m - 1)
// data 1 <= m <= n <= 2000 复杂度O(n^2)
constexpr int N = 2010;

constexpr int MOD = 1e9 + 7;

std::vector<std::vector<int>> a(N, std::vector<int> (N, 1));

void pre() {
    for (int i = 2; i <= N - 5; i++) {
        a[i][1] = i;
    }

    for (int i = 3; i <= N - 5; i++) {
        for (int j = 2; j < i; j++) {
            a[i][j] = (a[i - 1][j - 1] + a[i - 1][j]) % MOD;
        }
    }
}

/*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------*/
// data 1 <= m <= n <= 1e5 这时用杨辉递推式已经不合适了
// 现预处理阶乘，然后再利用c(n, m) = n! / (m! * (n - m)!)求组合数

constexpr int N = 1e5 + 10;

constexpr int MOD = 1e9 + 7;

std::vector<i64> ft(N, 1);

void pre_fact() {
	for (int i = 2; i <= 2e5 + 5; i++) {
		ft[i] = ft[i - 1] * i % MOD; // 前缀积求阶乘复杂度就是O(n)
	}
}

i64 ksm(i64 a, i64 b) {
	i64 ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}
	
	return ans;
}

i64 inv(int a) {
	return ksm(a, MOD - 2); // 费马小定理求模逆好写一点，需要满足gcd(a, MOD) == 1。这里MOD为质数是满足条件的。
}

i64 c(int n, int m) {
	if (!n || !m || n == m) return 1; // 非常容易的优化。
	
	return ft[n] * inv(ft[m]) % MOD * inv(ft[n - m]) % MOD; // 套公式：c(n, m) = n! / (m! * (n - m)!)
}
/*-------------------------------------------------------------------*/
