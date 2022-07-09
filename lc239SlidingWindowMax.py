class Solution:
    def maxSlidingWindow(self, a: List[int], k: int) -> List[int]:
        if len(a) == 1:
            return a
        
        n = len(a)

        q = []
        ans = []

        i = 0
        while i < n:
            while q and a[i] >= a[q[-1]]: #如果大于前面元素，则前面元素出队
                q.pop()
            
            q.append(i) #新元素入队

            if i - k + 1 >= 0:
                ans.append(a[q[0]]) #队头为最大元素

            if q and q[0] == i - k + 1: #元素移动后不在窗口内，出队
                q.pop(0)

            i += 1
        
        return ans
