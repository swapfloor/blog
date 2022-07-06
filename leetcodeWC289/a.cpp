class Solution {
public:
    string digitSum(string s, int k) {
        while (s.size() <= k) return s;
        
        string ans;
        int ss = s.size();
        for (int i = 0, j = 0; i < ss; i += k, j = i) {
            int t = 0;
            while (j < ss && j < i + k) {
                t = t + s[j] - '0';
                j++;
            }
            
            std::cout << "t = " << t << "\n";
            ans += to_string(t);
        }
        
        string res = digitSum(ans, k);
        return res;
    }
};
