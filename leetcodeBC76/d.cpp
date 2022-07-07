class Solution {
public:
    int maximumScore(vector<int>& a, vector<vector<int>>& eg) {
        vector<vector<int>> g(a.size() + 1);
        
        auto cmp = [&a](const int &x, const int &y) {
            return a[x] > a[y];
        };
        
        for (auto &e : eg) {
            int u = e[0], v = e[1];
            g[u].push_back(v); g[v].push_back(u);
            
            sort(g[u].begin(), g[u].end(), cmp);
            sort(g[v].begin(), g[v].end(), cmp);
            
            if (g[u].size() > 3) g[u].pop_back();
            if (g[v].size() > 3) g[v].pop_back();
        }
        
        int ans = -1;
        
        for (auto &e : eg) {
            int u = e[0], v = e[1];
            
            for (auto &x : g[u]) { // 3 * 3 time used
                for (auto &y : g[v]) {
                    if (x != v && y != u && x != y) {
                        ans = max(ans, a[x] + a[y] + a[u] + a[v]);
                    }
                }
            }
        }
        
        return ans;
    }
};

// vector
