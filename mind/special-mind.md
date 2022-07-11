> 这是一篇关于竞争性编码比赛中的题目的特定解法。

## 最长回文子串

[练习](https://leetcode.com/problems/longest-palindromic-substring/)

### 方法：扩展中心算法

如果用dp解，我们枚举的是回文串的左端点和右端点，时间复杂度为O(n^2)

如果用**扩展中心**来求，枚举一个点，以该点为**中心**进行左右扩展。

**分类**：我们知道可以枚举的回文串都只有两种，一种奇数个元素串，一种偶数个元素串。

所以可以分为枚举一个点，或者枚举两个点(两个点元素相同)。

看了一个超短时间commit的，它不管是一个点扩展还是两个点扩展，（一个点扩展和两个点扩展的复杂度为O(2n^2)）即`expandAroundCenter(String s, int left, int right)`,`expandAroundCenter(s, i, i);`,`expandAroundCenter(s, i, i + 1);`但是实际不卡数据复杂度也比较低。

- 他使用相同点进行扩展，假设扩展端点下边为l和r。使用while循环i为枚举点，i不能超过n。

- `while (r < n - 1 && a[r] == a[r + 1]) r++;`将右端点进行相同元素扩展。这样就是只可能是相同元素个数多少，枚举单个点的原因是没有相同元素。

```c++
class Solution {
public:
    string longestPalindrome(string& s) {
        int n = s.size();
        if (n == 1) {
            return s;
        }
        
        int i = 0, len = 0, srt = 0;
        while (i < n) {
            int l = i, r = i;
            
            while (r < n - 1 && s[r] == s[r + 1]) r++;
            
            i = r + 1;
            
            while (l > 0 && r < n - 1 && s[l - 1] == s[r + 1]) l--, r++;
            
            if (len < r - l + 1) {
                len = r - l + 1;
                srt = l;
            }
        }
        
        return s.substr(srt, len);
    }
};
```
