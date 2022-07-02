## 前言

**二叉搜索树**是一种特殊的二叉树。

### 二叉搜索树的"特殊"性质

每个结点的值大于或等于左子树每个结点的值，小于或等于右子树每个结点的值。

### 二叉搜索树的例图

![](https://github.com/swapfloor/blog/blob/main/images/BST_example.png)

### 练习

如何通过程序**验证**一棵二叉树**是否**是**二叉搜索树**？

给出一棵二叉树的根节点，然后通过编写程序验证是否是二叉搜索树。

**二叉搜索树性质**：每个结点的值大于左子树每个结点的值，小于右子树每个结点的值。且左右子树也为二叉搜索树。

类已经定义好了
```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
```

![](https://github.com/swapfloor/blog/blob/main/images/tree1.jpg)

我可以写一个程序解决这一个图中的问题。
```c++
bool isValidBST(TreeNode* root) {
    int l, r, mid;
    if (root != nullptr) mid = root->val;
    if (root->left != nullptr) l = root->left->val;
    if (root->right != nullptr) r = root->right->val;
    if (mid >= l && mid <= r) return true;
    else return false;
}
```

如果是下面这个图该怎么办？

![](https://github.com/swapfloor/blog/blob/main/images/tree2.jpg)

#### 递归

对于一个被递归的结点，

1. 如果它是右子树递归下来的点，则需要判断三个结点，自己、父亲、还有父亲作为左儿子的父亲，因为需要满足左子树的所有结点小于根节点。

2. 如果它是左子树递归下来的点，则需要判断三个结点，自己、父亲、还有父亲作为右儿子的父亲，因为需要满足右子树的所有结点大于根节点。

三个结点按二叉搜索树顺序排列返回正确，这里可以找反例判断不正确，原因是有可能有空节点。

根据大小关系将左爹和右爹的左爹抽象为矮点，将右爹和左爹的右爹抽象为高点

1. 如果根节点为空，则直接返回正确。

2. 如果矮点存在，矮点大于根节点，返回错误。

3. 如果高点存在，高点小于根节点，返回错误。

- 然后是**递归**，递归要将高点和矮点按逻辑写入，首先是没有这两个点的，所以设为空节点，
- 其次如果向左子树递归，根节点挪到左子树结点上，高点即根节点，矮点直接继承。
- 如果向右子树递归，根节点挪到右子树结点上，矮点即根节点，高点直接继承。

```c++
#define r right
#define l left
#define N TreeNode
bool is(N* rt, N* low, N* high) {
    if (!rt) return true;
    
    if (low && low->val >= rt->val) return false
    if (high && high->val <= rt->val) return false;
    
    return is(rt->l, low, rt) && is(rt->r, rt, high);
}
bool isValidBST(N* rt) {
    return is(rt, nullptr, nullptr);
}
```

#### 利用堆栈进行中序遍历

优点：不使用递归
利用二叉搜索树性质：中序遍历可以得到升序序列

- 首先将根节点放入栈中，然后不断向左移动结点，
- 将途中结点加入栈中，堆栈顶部可以看出是最小的结点，
- 我们从栈顶取出结点放入一个变量`prev`，
- 将栈顶的右子树结点放入另一个变量`cur`，
- 如果`cur`可以向左移动，那么就让它一直向左直到树叶；如果prev大于cur那么就返回错误。

```c++
#define r right
#define l left
#define N TreeNode
bool isValidBST(N* rt) {
    if (!rt) return true;
    
    std::stack<N*> stk;
    
    N *cur = rt, *prev = nullptr;
    
    while (cur || stk.size()) {
        while (cur) {
            stk.push(cur);
            cur = cur->l;
        }
        cur = stk.top(); 
        stk.pop();
        
        if (prev && prev->val >= cur->val) return false;
        
        prev = cur;
        cur = cur->r;
    }
    
    return true;
}
```
可以看到加入stack中的结点不能是空节点，不然就会出现`node->left=nullptr`然后去访问`node->left->left`访问失败。

所以使用`while(cur)`如果存在才加入，如果左节点不存在，就从栈顶去元素，如果不存在右子树，cur就会变成下一个栈顶元素。

#### 其他

利用中序遍历可以看出二叉搜索树的升序性质

假设一棵二叉搜索树为`[12,5,18,3,7,14,19,null,4,6,8]`

![](https://github.com/swapfloor/blog/blob/main/images/bst1.PNG)

```c++
#define r right
#define l left
#define N TreeNode
void printBST(N* rt) {
    if (!rt) return;
    
    std::stack<N*> stk;
    
    N *cur = rt, *prev = nullptr;
    
    while (cur || stk.size()) {
        while (cur) {
            stk.push(cur);
            cur = cur->l;
        }
        cur = stk.top(); 
        stk.pop();
        
        if (prev && prev->val >= cur->val) return;
        
        prev = cur;
        printf("%d ", prev->val); // 将上一个结点打印出来
        cur = cur->r;
    }
}
```

结果为`3 4 5 6 7 8 12 14 18 19`
