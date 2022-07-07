class ATM:
    def __init__(self):
        self.d = [20, 50, 100, 200, 500]
        self.ans = [0] * 5

    def deposit(self, b: List[int]) -> None:
        for i in range(5):
            self.ans[i] += b[i]

    def withdraw(self, a: int) -> List[int]:
        t = [0] * 5;
        
        for i in range(4, -1, -1):
            t[i] = a // self.d[i];
            t[i] = min(t[i], self.ans[i]);
            a -= t[i] * self.d[i];
        
        if a:
            return [-1];
        else:
            for i in range(5):
                self.ans[i] -= t[i];
        
        return t;


# Your ATM object will be instantiated and called as such:
# obj = ATM()
# obj.deposit(banknotesCount)
# param_2 = obj.withdraw(amount)
