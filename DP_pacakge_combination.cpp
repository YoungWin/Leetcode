
/*
author:young
动态规划：背包、组合数【重点区别排列377 / 70和组合518】
*/
//动态规划三要素: 重叠⼦问题、 最优⼦结构、 状态转移⽅程
//明确「状态」 -> 定义 dp 数组/函数的含义 -> 明确「选择」 -> 明确 base case
/*
完全背包问题：背包里的物品可以 无限次选取
「力扣」第 322 题：零钱兑换；
「力扣」第 518 题：零钱兑换 II。
0-1 背包问题：当前考虑的物品 用或者不用
「力扣」第 416 题：分割等和子集；
「力扣」第 474 题：一和零；
「力扣」第 494 题：目标和。
*/


/*【完全背包问题】
322. 零钱兑换
给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额 所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回 -1。
示例 1:
输入: coins = [1, 2, 5], amount = 11
输出: 3 
解释: 11 = 5 + 5 + 1
示例 2:
输入: coins = [2], amount = 3
输出: -1
说明:
你可以认为每种硬币的数量是无限的。
*/

class Solution{
    vector<int> note;
public:
    int coinChange(vector<int>& coins, int amount){
        note.resize(amount+1);
        return helper(coins, amount);
    }
    int helper(vector<int>& coins, int res){
        if(res==0) return 0;
        if(res<0) return -1;
        if(note[res] != 0) return note[res];
        int raw=INT_MAX;
        for(int i:coins){
            int tmp=helper(coins, res-i);
            if(tmp>=0) raw=min(raw, tmp+1);
        }
        if(raw==INT_MAX) note[res]=-1;
        else note[res]=raw;
        return note[res];
    }
}
class Solution{
public:
    //dp[i] : 凑出金额i所需最少硬币数
    int coinChange(vector<int>& coins, int amount){
        vector<int> dp(amount+1, amount+1);
        dp[0]=0;
        for(int k=1; k<amount+1; k++){
            for(int i:coins){
                if(i<=k) dp[k]=min(dp[k],dp[k-i]+1);
            }
        }
        if(dp[amount]>amount) return -1;
        return dp[amount];
    }
};


/*【完全背包问题】
518. 零钱兑换 II
给定不同面额的硬币和一个总金额。写出函数来计算可以凑成总金额的硬币组合数。假设 每一种面额的硬币 有无限个。 
示例 1:
输入: amount = 5, coins = [1, 2, 5]
输出: 4
解释: 有四种方式可以凑成总金额:
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1
示例 2:
输入: amount = 3, coins = [2]
输出: 0
解释: 只用面额2的硬币不能凑成总金额3。
示例 3:
输入: amount = 10, coins = [10] 
输出: 1
注意:
你可以假设：
0 <= amount (总金额) <= 5000
1 <= coin (硬币面额) <= 5000
硬币种类不超过 500 种
结果符合 32 位符号整数
*/

class Solution {
public:
    //dp[i][j] : 凑出金额i，使用前j枚硬币，对应的组合种数
    int change(int amount, vector<int>& coins) {
        int N=coins.size();
        vector<vector<int>> dp(amount+1, vector<int>(N+1, 0));
        for(int j=0; j<N+1; j++) dp[0][j]=1;

        for(int i=1; i<amount+1; i++){   //要凑的金额
            for(int j=1; j<N+1; j++){   //使用的硬币
                if(i<coins[j-1]) dp[i][j]=dp[i][j-1];
                else dp[i][j]=dp[i][j-1]+dp[i-coins[j-1]][j];   //第j枚硬币使用至少一次
            }
        }

        return dp[amount][N];
    }
};

/*【0-1背包问题】
416. 分割等和子集
给定一个只包含正整数的非空数组。是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
注意:
每个数组中的元素不会超过 100
数组的大小不会超过 200
示例 1:
输入: [1, 5, 11, 5]
输出: true
解释: 数组可以分割成 [1, 5, 5] 和 [11].
示例 2:
输入: [1, 2, 3, 5]
输出: false
解释: 数组不能分割成两个元素和相等的子集.
*/

class Solution {
public:
    //dp[i][j] : 要想凑出总和i 使用前j个数 是否可以凑出来
    bool canPartition(vector<int>& nums) {
        int N=nums.size();
        int sum=0;
        for(int i:nums) sum+=i;
        if(sum%2) return false;
        sum=sum/2;

        vector<vector<bool>> dp(sum+1, vector<bool>(N+1, false));
        for(int j=0; j<N+1; j++) dp[0][j]=true;

        for(int i=1; i<sum+1; i++){   //凑数总和
            for(int j=1; j<N+1; j++){   //使用前面几个数字
                if(nums[j-1] > i) dp[i][j]=dp[i][j-1];
                else dp[i][j]=dp[i][j-1] || dp[i-nums[j-1]][j-1];   //第j个数只能用一次
            }
        }

        return dp[sum][N];
    }
};

/*【0-1背包问题】
474. 一和零
在计算机界中，我们总是追求用有限的资源获取最大的收益。
现在，假设你分别支配着 m 个 0 和 n 个 1。另外，还有一个仅包含 0 和 1 字符串的数组。
你的任务是使用给定的 m 个 0 和 n 个 1 ，找到能拼出存在于数组中的字符串的最大数量。每个 0 和 1 至多被使用一次。
注意:
给定 0 和 1 的数量都不会超过 100。
给定字符串数组的长度不会超过 600。
示例 1:
输入: Array = {"10", "0001", "111001", "1", "0"}, m = 5, n = 3
输出: 4
解释: 总共 4 个字符串可以通过 5 个 0 和 3 个 1 拼出，即 "10","0001","1","0" 。
示例 2:
输入: Array = {"10", "0", "1"}, m = 1, n = 1
输出: 2
解释: 你可以拼出 "10"，但之后就没有剩余数字了。更好的选择是拼出 "0" 和 "1" 。
*/





/*【0-1背包问题】
494. 目标和
给定一个非负整数数组，a1, a2, ..., an, 和一个目标数，S。现在你有两个符号 + 和 -。对于数组中的任意一个整数，你都可以从 + 或 -中选择一个符号添加在前面。
返回可以使最终数组和为目标数 S 的所有添加符号的方法数。
示例：
输入：nums: [1, 1, 1, 1, 1], S: 3
输出：5
解释：
-1+1+1+1+1 = 3
+1-1+1+1+1 = 3
+1+1-1+1+1 = 3
+1+1+1-1+1 = 3
+1+1+1+1-1 = 3
一共有5种方法让最终目标和为3。
提示：
数组非空，且长度不会超过 20 。
初始的数组的和不会超过 1000 。
保证返回的最终结果能被 32 位整数存下。
*/





/*
377. 组合总和 Ⅳ
给定一个由正整数组成且不存在重复数字的数组，找出和为给定目标正整数的组合的个数。
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
public:
    //dp[i]:用给定无重复正数数组元素，组成和为i的组合数
    int combinationSum4(vector<int>& nums, int target) {
        int N=nums.size();
        if(N == 0) return 0;
        vector<int> dp(target + 1, 0);
        dp[0] = 1;   //构成0的组合 只有1种
        for(int i = 1; i < target+1; i++){
            for(int j = 0; j < N; j++){
                if(nums[j] <= i){
                    if(dp[i]>=INT_MAX-dp[i-nums[j]]) dp[i]=INT_MAX;   //意思就是dp[i]和dp[i-nums[j]]求和溢出INT_MAX
                    else dp[i]+=dp[i-nums[j]];
                } 
            }
        }
        return dp[target];
    }
};

/*
279. 完全平方数【同322题】
给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）使得它们的和等于 n。你需要让组成和的完全平方数的个数最少。
示例 1:
输入: n = 12
输出: 3 
解释: 12 = 4 + 4 + 4.
示例 2:
输入: n = 13
输出: 2
解释: 13 = 4 + 9.
*/

class Solution {
public:
    //dp[n]：要想和达到n 最少需要的完全平方数个数
    int numSquares(int n) {
        vector<int> dp(n+1, n+1);
        dp[0]=0;
        for(int i=1; i<n+1; i++){
            for(int j=1; j*j<=i; j++){
                dp[i]=min(dp[i], dp[i-j*j]+1);
            }
        }
        return dp[n];
    }
};

/*
343. 整数拆分
给定一个正整数 n，将其拆分为至少两个正整数的和，并使这些整数的乘积最大化。 返回你可以获得的最大乘积。
示例 1:
输入: 2
输出: 1
解释: 2 = 1 + 1, 1 × 1 = 1。
示例 2:
输入: 10
输出: 36
解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36。
说明: 你可以假设 n 不小于 2 且不大于 58。
*/

class Solution {
public:
    //dp[i]：数字i拆分为至少两个正整数之和的最大乘积。
    int integerBreak(int n) {
        if(n==2) return 1;
        vector<int> dp(n+1, 1);
        dp[2]=1;
        for(int i=3; i<n+1; i++){
            for(int j=1; j<i; j++){
                int tmp=max(j*(i-j), j*dp[i-j]);   //对i-j拆不拆分的对比
                dp[i]=max(dp[i], tmp);
            }
        }
        return dp[n];
    }
};







