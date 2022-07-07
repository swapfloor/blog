class Solution {
public:
    int findClosestNumber(vector<int>& nums) {
        int ans = -1e8;
        for (auto n : nums) {
            if (abs(n) < abs(ans) || abs(n) == abs(ans) && n > ans) {
                ans = n;
            }
        }
        
        return ans;
    }
};
