class Solution {
public:
    typedef long long ll;
    long long waysToBuyPensPencils(int n, int a, int b) {
        if (a > b) swap(a, b);
        ll ans = 0;
        bool ok = true;
        for (ll i = 0; ok; i++) {
            int t = n - a * i;
            if (t < 0) {
                ok = false;
                break;
            }
            
            int m = t / b;
            
            ans += m + 1;
        }
        
        return ans;
    }
};
