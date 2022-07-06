class Solution {
public:
    int maxTrailingZeros(std::vector<std::vector<int>>& a) {
        int m = a.size(), n = a[0].size();
        
        std::vector<std::vector<std::vector<int>>> h(m + 1, std::vector<std::vector<int>> (n + 1, std::vector<int> (6, 0)));
        std::vector<std::vector<std::vector<int>>> w(m + 1, std::vector<std::vector<int>> (n + 1, std::vector<int> (6, 0)));
        
        #define db(x) std::cout << #x << " = " << x << "\n"
        #define dbs(x) std::cout << x << " "
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                int t = a[i - 1][j - 1];
                int cnt = 0;
                while (t % 2 == 0) {
                    t /= 2;
                    cnt++;
                }
                
                h[i][j][2] = h[i][j - 1][2] + cnt;
                
                cnt = 0;
                while (t % 5 == 0) {
                    t /= 5;
                    cnt++;
                }
                
                h[i][j][5] = h[i][j - 1][5] + cnt;
            }
        }
        
        for (int j = 1; j <= n; j++) {
            for (int i = 1; i <= m; i++) {
                int t = a[i - 1][j - 1];
                int cnt = 0;
                while (t % 2 == 0) {
                    t /= 2;
                    cnt++;
                }
                
                w[i][j][2] = w[i - 1][j][2] + cnt;
                
                cnt = 0;
                while (t % 5 == 0) {
                    t /= 5;
                    cnt++;
                }
                
                w[i][j][5] = w[i - 1][j][5] + cnt;
            }
        } 
        
        int ans = 0;
        for (int i = 1; i <= m; i++) {
        	for (int j = 1; j <= n; j++) {
        		int t[5] = {0}, g[5] = {0};
				t[0] = h[i][j][2] - h[i][j - 1][2], g[0] = h[i][j][5] - h[i][j - 1][5];
        		t[1] = w[i - 1][j][2], g[1] = w[i - 1][j][5];//up
        		t[2] = h[i][j - 1][2], g[2] = h[i][j - 1][5];//left
        		t[3] = w[m][j][2] - w[i][j][2], g[3] = w[m][j][5] - w[i][j][5];//bottom
        		t[4] = h[i][n][2] - h[i][j][2], g[4] = h[i][n][5] - h[i][j][5];//right
        		
        		ans = std::max(ans, std::min(t[0] + t[1] + t[2], g[0] + g[1] + g[2]));
        		ans = std::max(ans, std::min(t[0] + t[1] + t[4], g[0] + g[1] + g[4]));
        		ans = std::max(ans, std::min(t[0] + t[2] + t[3], g[0] + g[2] + g[3]));
        		ans = std::max(ans, std::min(t[0] + t[3] + t[4], g[0] + g[3] + g[4]));
			}
		}
        return ans;
     }
};
