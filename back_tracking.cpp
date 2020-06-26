
/*
author:young
回溯
*/

//回溯算法就是个多叉树的遍历问题， 关键就是在前序遍历和后序遍历的位置。

/*
46. 全排列
给定一个 没有重复 数字的序列，返回其所有可能的全排列。
示例:
输入: [1,2,3]
输出:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]
*/

class Solution {
    vector<vector<int>> res;
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> tmp;
        vector<bool> used(nums.size(),false);
        helper(nums,tmp,used);
        return res;
    }

    void helper(vector<int>& nums, vector<int>& tmp, vector<bool>& used){
        if(tmp.size()==nums.size()){
            res.push_back(tmp);
            return;
        }
        for(int i=0; i<nums.size(); i++){
            if(used[i]) continue;
            tmp.push_back(nums[i]);
            used[i]=true;
            helper(nums,tmp,used);
            tmp.pop_back();
            used[i]=false;
        }
    }
};


/*
47. 全排列 II
给定一个可包含重复数字的序列，返回所有不重复的全排列。
示例:
输入: [1,1,2]
输出:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]
*/

class Solution {
    vector<vector<int>> res;
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<int> tmp;
        vector<bool> used(nums.size(),false);   //记录 当前树分支上的 值使用情况
        sort(nums.begin(),nums.end());
        helper(nums,tmp,used);
        return res;
    }

    void helper(vector<int>& nums, vector<int>& tmp, vector<bool>& used){
        if(tmp.size()==nums.size()){
            res.push_back(tmp);
            return;
        }
        for(int i=0; i<nums.size(); i++){
            if(used[i] || (i>0 && !used[i-1] && nums[i-1]==nums[i])) continue;
            tmp.push_back(nums[i]);
            used[i]=true;
            helper(nums,tmp,used);
            tmp.pop_back();
            used[i]=false;
        }
    }
};


//必须说明的是,不管怎么优化,回溯时间复杂度都不可能低于 O(N!)。因为穷举整棵决策树是⽆法避免的。 
//这也是回溯算法的⼀个特点,不像动态规划存在重叠⼦问题可以优化,回溯算法就是纯暴⼒穷举,复杂度⼀般都很⾼。



/*
51. N皇后
n 皇后问题研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
上图为 8 皇后问题的一种解法。
给定一个整数 n，返回所有不同的 n 皇后问题的解决方案。
每一种解法包含一个明确的 n 皇后问题的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。
示例:
输入: 4
输出: [
 [".Q..",  // 解法 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // 解法 2
  "Q...",
  "...Q",
  ".Q.."]
]
解释: 4 皇后问题存在两个不同的解法。
提示：
皇后，是国际象棋中的棋子，意味着国王的妻子。皇后只做一件事，那就是“吃子”。当她遇见可以吃的棋子时，就迅速冲上去吃掉棋子。当然，她横、竖、斜都可走一到七步，可进可退。（引用自 百度百科 - 皇后 ）
*/
//决策树的每⼀层表⽰棋盘上的每⼀⾏； 每个节点可以做出的选择是， 在该⾏的任意⼀列放置⼀个皇后。

class Solution {
private:
    vector<vector<string>> res;
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<bool> Line(n,false);   //每一列的合法性
        vector<bool> Incline1(2*n-1,false);   //主对角线的合法性
        vector<bool> Incline2(2*n-1,false);   //副对角线的合法性
        vector<vector<bool>> Q(n, Line);
        helper(n, Q, Line, Incline1, Incline2, 0);
        return res;
    }
    void helper(int& n, vector<vector<bool>>& Q, vector<bool>& line, vector<bool>& incline1, vector<bool>& incline2, int k) {
        if(k==n) {
            string a="";
            vector<string> b;   //每个string表示一行
            for(int i=0; i<n; i++) {
                for(int j=0; j<n; j++) {
                    if(Q[i][j]) a.push_back('Q');
                    else a.push_back('.');
                }
                b.push_back(a);
                a.clear();
            }
            res.push_back(b);
            return;
        }
        for(int i=0; i<n; i++) {   //遍历第k行的各列
            if(line[i] || incline1[k+n-1-i] || incline2[k+i]) continue;
            //第i列被占；副对角线(k,i)点对应的坐标索引值 差都为k-i，用n-1做个平移；主对角线(k,i)点对应的坐标索引值 和都为k+i
            incline1[k+n-1-i]=true;
            incline2[k+i]=true;
            Q[k][i]=true;
            line[i]=true;

            helper(n, Q, line, incline1, incline2, k+1);

            incline1[k+n-1-i]=false;
            incline2[k+i]=false;
            Q[k][i]=false;
            line[i]=false;
        }  
    }
};

/*
78. 子集
给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
说明：解集不能包含重复的子集。
示例:
输入: nums = [1,2,3]
输出:
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
*/

class Solution {
    vector<vector<int>> res;
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        if(nums.size() == 0) return res;
        vector<int> tmp;
        helper(nums, tmp, 0);
        return res;
    }
    void helper(vector<int>& nums, vector<int>& tmp, int start) {
        if(tmp.size() <= nums.size()){
            res.push_back(tmp);
        }
        for(int i = start; i < nums.size(); i++){   //带减枝的for循环
            tmp.push_back(nums[i]);
            helper(nums, tmp, i + 1);
            tmp.pop_back();
        }
    }
};

/*
90. 子集 II
给定一个可能包含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
说明：解集不能包含重复的子集。
示例:
输入: [1,2,2]
输出:
[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]
*/

class Solution {
	vector<vector<int>> res;
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        if(nums.size() == 0) return res;
        sort(nums.begin(), nums.end());   //有重复元素，先排序
        vector<int> tmp;
        helper(nums, tmp, 0);
        return res;
    }
    
    void helper(vector<int>& nums, vector<int>& tmp, int start) {
        if(tmp.size() <= nums.size()){
            res.push_back(tmp);
        }
        for(int i = start; i < nums.size(); i++){
            if(i > start && nums[i] == nums[i - 1]) continue;   //同层遍历，如果当前层已经使用过相同值，再使用会重复
            tmp.push_back(nums[i]);
            helper(nums, tmp, i + 1);
            tmp.pop_back();
        }
    }
};

/*
22. 括号生成
数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
示例：
输入：n = 3
输出：[
       "((()))",
       "(()())",
       "(())()",
       "()(())",
       "()()()"
     ]
*/

class Solution {
    vector<string> res;
public:
    vector<string> generateParenthesis(int n) {
        string tmp;
        helper(n, tmp, 0, 0);   //回溯函数
        return res;
    }
    
    void helper(int n, string& tmp, int left, int right) {
        if(tmp.size() == n * 2){
            res.push_back(tmp);
            return;
        }
        if(left < n){
            tmp.push_back('(');
            helper(n, tmp, left + 1, right);
            tmp.pop_back();
        }
        if(right < left){
            tmp.push_back(')');
            helper(n, tmp, left, right + 1);
            tmp.pop_back();
        }
    }
};


/*
77. 组合
给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合。
示例:
输入: n = 4, k = 2
输出:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
*/

class Solution {
    vector<vector<int>> res;
public:
    vector<vector<int>> combine(int n, int k) {
        if(n <= 0 || k <= 0 || n < k) return res;
        vector<int> tmp;
        helper(n, k, tmp, 1);
        return res;
    }

    void helper(int n, int k, vector<int>& tmp, int start) {
        if(tmp.size() == k){
            res.push_back(tmp);
            return;
        }
        for(int i = start; i <= n + 1 - k + tmp.size(); i++){   //滑窗可选值范围是n+1-k，i取值移动左边界，tmp.size()扩大右边界 选择
            tmp.push_back(i);
            helper(n, k, tmp, i + 1);   //tmp存已经选择完的数字，i+1表示选择 从第i+1个数字向后
            tmp.pop_back();
        }
    }
};

/*
39. 组合总和
给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
candidates 中的数字可以无限制重复被选取。
说明：
所有数字（包括 target）都是正整数。
解集不能包含重复的组合。 
示例 1:
输入: candidates = [2,3,6,7], target = 7,
所求解集为:
[
  [7],
  [2,2,3]
]
示例 2:
输入: candidates = [2,3,5], target = 8,
所求解集为:
[
  [2,2,2,2],
  [2,3,3],
  [3,5]
]
*/

class Solution {
    vector<vector<int>> res;
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> tmp;
        helper(candidates, target, tmp, 0);
        return res;
    }
    
    void helper(vector<int>& candidates, int target, vector<int>& tmp, int start) {
        if(target < 0) return;
        if(target == 0) res.push_back(tmp);
        for(int i = start; i < candidates.size(); i++){   //从 candidates里 当前start位置 向后遍历，避免重复
            tmp.push_back(candidates[i]);
            helper(candidates, target - candidates[i], tmp, i);
            tmp.pop_back();
        }
    }
};


/*
40. 组合总和 II
给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
candidates 中的每个数字在每个组合中只能使用一次。
说明：
所有数字（包括目标数）都是正整数。
解集不能包含重复的组合。 
示例 1:
输入: candidates = [10,1,2,7,6,1,5], target = 8,
所求解集为:
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]
示例 2:
输入: candidates = [2,5,2,1,2], target = 5,
所求解集为:
[
  [1,2,2],
  [5]
]
*/

class Solution {
    vector<vector<int>> res;
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int> tmp;
        sort(candidates.begin(), candidates.end());
        helper(candidates, target, tmp, 0);
        return res;
    }
    
    void helper(vector<int>& candidates, int target, vector<int>& tmp, int start){
        if(target < 0) return;
        if(target == 0) res.push_back(tmp);
        for(int i = start; i < candidates.size(); i++){
            if(i > start && candidates[i - 1] == candidates[i]) continue;   //后一分支起始元素 与前一分支相同，这时 前一分支的内部递归一定包含后一分支
            tmp.push_back(candidates[i]);
            helper(candidates, target- candidates[i], tmp, i + 1);
            tmp.pop_back();
        }
    }
};

/*
216. 组合总和 III
找出所有相加之和为 n 的 k 个数的组合。组合中只允许含有 1 - 9 的正整数，并且每种组合中不存在重复的数字。
说明：
所有数字都是正整数。
解集不能包含重复的组合。 
示例 1:
输入: k = 3, n = 7
输出: [[1,2,4]]
示例 2:
输入: k = 3, n = 9
输出: [[1,2,6], [1,3,5], [2,3,4]]
*/

class Solution {
    vector<vector<int>> res;
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> tmp;
        helper(k, n, tmp, 1);   //从数字1开始挑选组合集合的数字
        return res;
    }

    void helper(int num, int target, vector<int>& tmp, int start) {
        if(num == 0 && target == 0){   //num是集合里还差几个数字 达到k，target是集合里还差多少 达到和为n
            res.push_back(tmp);
            return;
        }

        for(int i = start; i <= 9; i++){
            if(i > target) return;   //要减去的数比剩余和大 直接不考虑 减枝
            tmp.push_back(i);
            helper(num - 1, target - i, tmp, i + 1);
            tmp.pop_back();
        }
    }
};


/*
377. 组合总和 Ⅳ
给定一个由正整数组成 且不存在重复数字的 数组，找出 和为给定目标正整数的 组合的个数。
示例:
nums = [1, 2, 3]
target = 4
所有可能的组合为：
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)
请注意，顺序不同的序列被视作不同的组合。
因此输出为 7。
进阶：
如果给定的数组中含有负数会怎么样？
问题会产生什么变化？
我们需要在题目中添加什么限制来允许负数的出现？
*/

class Solution {
	int res = 0;
public:
	// 回溯法超时
	int combinationSum4(vector<int>& nums, int target) {
	    helper(nums, target);
	    return res;
	}
	void helper(vector<int>& nums, int target){
	    if(target < 0) return;
	    if(target == 0) res++;

	    for(int i = 0; i < nums.size(); i++){
	        helper(nums, target - nums[i]);
	    }
	}
};

////////////////////////////////////////////////////////////////////////////

class Solution {
private:
    unordered_map<int, int> mp;   //{和 : 多少组合组数}
public:
    int combinationSum4(vector<int>& nums, int target) {
        return helper(nums, target);
    }
    
    int helper(vector<int>& nums, int target) {
    	if(target < 0)  return 0;
        if(target == 0) {
        	mp[target] = 1;
        	return mp[target];
        }
        if(mp.count(target) > 0) return mp[target];   // target>0
        
        int sum = 0;
        for(int i = 0; i < nums.size(); i++) {   // 可重复选数字
            sum += helper(nums, target - nums[i]);
        }
        return mp[target] = sum;
    }
};

///////////////////////////////////////////////////////////////////////////

class Solution {
public:
    //dp[i]:用给定无重复正数数组元素，组成和为i的组合数
    int combinationSum4(vector<int>& nums, int target) {
        if(nums.size() == 0) return 0;
        vector<int> dp(target + 1, 0);
        dp[0] = 1;   //新加进来的一个数 自己单独构成一个组合
        for(int i = 0; i <= target; i++){
            for(int j = 0; j < nums.size(); j++){
                if(i < nums[j]) continue;

                if(dp[i] >= INT_MAX - dp[i - nums[j]])
                    dp[i] = INT_MAX;
                else
                    dp[i] += dp[i - nums[j]];
            }
        }
        return dp[target];
    }
};

