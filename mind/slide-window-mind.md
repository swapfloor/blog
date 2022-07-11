> 初学者的一些关于滑动窗口的思想及习题全析

[练习239. Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/)

## 题描

给你一个数组nums，长度为k的滑动窗口从nums的左边移动到右边，返回滑动窗口的最大值。

**think**：这道题定为为hard，但是学了之后很有意义。

## 思考

基础想法：我首先遍历求出第一个窗口的最大值。

```c++
vector<int> ans(n - k + 1);
for (int i = 0; i < k; i++) ans[0] = max(ans[0], nums[i]);
```

然后向右移动，如果上一个滑窗的第一个为最大值，那么能不能恢复win[l + 1, r]表示的最大值？所以这里咱遇到了一个困难。

滑窗就是将左侧元素删除，再将右侧元素加入。通过某软件看了一下这个题的解法，单调队列。

如果一个窗口里，最左边的数小于它右边隔壁的数，那么它就可以被丢弃了。Proof？

假设窗口内一个数为a，当窗口移动进来一个b，此时a，b均在窗口内，且`b >= a`，那么ans肯定不为a，在窗口右移直至b离开时，a也一定不是答案，毕竟有b，所有a可以直接丢了。

## code

```c++
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& a, int k) {
        int n = a.size();
        int i = 0;   
        
        if (n == 1) {
            return {a[0]};
        }
        
        deque<int> q; 
        vector<int> ans(n - k + 1);
        
        while (i < n) {
            while (!q.empty() && a[i] >= a[q.back()]) {// 窗口里面小的数的下标丢掉
                q.pop_back();
            }
            
            q.push_back(i);// 新下标入队列，因为单调下降队列，如果比前面元素小留下，比前面元素大，前面元素直接丢掉。
            
            if (i - k + 1 >= 0) {//加入答案中
                ans[i - k + 1] = a[q.front()];
            }
            
            if (!q.empty() && q.front() == i - k + 1) {// 窗口移动导致元素已经不在窗口内了，直接出队。
                q.pop_front();
            }
            
            i++;
        }
        
        return ans;
    }
};
```

[实战练习](https://leetcode.com/contest/weekly-contest-275/problems/minimum-swaps-to-group-all-1s-together-ii/)

仅会滑窗解决现在的竞赛很难，因为滑窗是一个解题模型，而解决这道练习需要有建模思维，比如交换0和1使得1在一起，可以逆推，如果使1在一起即将1的数目个连续序列中0替换成1。思维跟基础模型都很重要，前者需要主动训练，后者需要主动学习。

我们可以枚举连续的窗口复杂度为O(n).

算出每个窗口的1的总数就可以知道0的个数等于总共1的个数减去每个窗口1的总数，可以通过前缀和算出每个窗口的数量。

```c++
class Solution {
public:
    int minSwaps(vector<int>& nums) {
        int ones = 0;
        ones = accumulate(nums.begin(), nums.end(), ones);

        nums.insert(nums.end(), nums.begin(), nums.end());

        int n = nums.size();

        vector<int> s(n + 2, 0);
        for (int i = 0; i < n; i++) s[i + 1] = s[i] + nums[i];

        int ans = 0;
        for (int i = 1; i + ones - 1 <= n; i++) {
            ans = max(ans, s[i + ones - 1] - s[i - 1]);
        }

        return ones - ans;
    }
};
```
