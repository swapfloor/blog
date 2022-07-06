class Solution {
public:
    int minimumRounds(vector<int>& a) {
        if (a.size() <= 1) return -1;
        
        sort(a.begin(), a.end());
        
        int ans = 0;
        bool ok = true;
        for (int i = 0; i < a.size(); i++) {
            int j = i + 1;
            while (j != a.size() && a[j] == a[i]) {
                j++;
            }
            
            j--;
            
            if (j == i) {
                ok = false;
                break;
            } else {
                int t = j - i + 1;
                int f = t / 3;
                
                if (t & 1 && f & 1) {
                    ans += f + (t - f * 3) / 2;
                } else {
                    ans += (f - 1) + (t - f * 3 + 3) / 2;
                }
                
            }
            
            i = j;
        }
        
        if (!ok) return -1;
        return ans;
    }
};
