class Solution {
public:
	int ans = 0;
	int solve(int u, const std::vector<std::vector<int>>& g, const std::string& s) {
		int d1 = 0, d2 = 0;
		
		for (auto v : g[u]) {
			int d = solve(v, g, s);
			
			if (s[u] == s[v]) continue;
			
			if (d > d1) {
				d2 = d1;
				d1 = d;
			} else if (d > d2) {
				d2 = d;
			}
		}
		
		ans = std::max(ans, d1 + d2 + 1);
		
		return std::max(d1, d2) + 1;
	}
    int longestPath(std::vector<int>& a, std::string s) {
    	std::vector<std::vector<int>> g(a.size() + 3);
    	
        for (int i = 1; i < a.size(); i++) {
			g[a[i]].push_back(i);
		}
		
		solve(0, g, s);
		 
		return ans;
    }
};
