
/*
author:young
动态规划：数组、字符串
*/
//动态规划三要素: 重叠⼦问题、 最优⼦结构、 状态转移⽅程
//明确「状态」 -> 定义 dp 数组/函数的含义 -> 明确「选择」 -> 明确 base case


/*
198. 打家劫舍
你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。
示例 1：
输入：[1,2,3,1]
输出：4
解释：偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。
     偷窃到的最高金额 = 1 + 3 = 4 。
示例 2：
输入：[2,7,9,3,1]
输出：12
解释：偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。
     偷窃到的最高金额 = 2 + 9 + 1 = 12 。
提示：
0 <= nums.length <= 100
0 <= nums[i] <= 400
*/

class Solution {
public:
    //dp[i] : 只取前i个房子的钱 最多可得最大金额
    int rob(vector<int>& nums) {
        int N=nums.size();
        if(N==0) return 0;
        if(N==1) return nums[0];
        vector<int> dp(N,0);
        dp[0]=nums[0];
        dp[1]=max(dp[0],nums[1]);
        for(int i=2; i<N; i++){
            dp[i]=max(dp[i-1], dp[i-2]+nums[i]);   //取不取第i个房子的钱
        }
        return dp[N-1];
    }
};

/*
120. 三角形最小路径和
给定一个三角形，找出自顶向下的最小路径和。每一步只能移动到下一行中相邻的结点上。
相邻的结点 在这里指的是 下标 与 上一层结点下标 相同或者等于 上一层结点下标 + 1 的两个结点。
例如，给定三角形：
[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
自顶向下的最小路径和为 11（即，2 + 3 + 5 + 1 = 11）。
说明：
如果你可以只使用 O(n) 的额外空间（n 为三角形的总行数）来解决这个问题，那么你的算法会很加分。
*/

class Solution {
public:
    //dp[i][j] : 位置(i,j) 对应的 从底层到当前层的 最小路径和
    int minimumTotal(vector<vector<int>>& triangle) {
        vector<vector<int>> dp(triangle);   //dp数组和triangle维度一致
        for(int i = triangle.size() - 2; i >= 0; i--){   //从倒数第二行开始
            for(int j = 0; j < triangle[i].size(); j++){
                dp[i][j] = min(dp[i + 1][j], dp[i + 1][j + 1]) + dp[i][j];
            }
        }
        return dp[0][0];
    }
};

/*
152. 乘积最大子数组
给你一个整数数组 nums ，请你找出数组中乘积最大的连续子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。
示例 1:
输入: [2,3,-2,4]
输出: 6
解释: 子数组 [2,3] 有最大乘积 6。
示例 2:
输入: [-2,0,-1]
输出: 0
解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。
*/

class Solution {
public:
    //dp[i][j]：以 nums[i] 结尾的连续子数组的最值，计算最大值还是最小值由 j 来表示，j 就两个值；
    //当 j = 0 的时候，表示计算的是最小值；当 j = 1 的时候，表示计算的是最大值。
    int maxProduct(vector<int>& nums) {
        int N=nums.size();
        if(N==0) return 0;

        vector<vector<int>> dp(N, vector<int>(2));
        dp[0][0]=nums[0], dp[0][1]=nums[0];

        int res=dp[0][1];   //
        for(int i=1; i<N; i++){
            if(nums[i]>=0){
                dp[i][0]=min(nums[i], nums[i]*dp[i-1][0]);
                dp[i][1]=max(nums[i], nums[i]*dp[i-1][1]);
            } else{
                dp[i][0]=min(nums[i], nums[i]*dp[i-1][1]);
                dp[i][1]=max(nums[i], nums[i]*dp[i-1][0]);
            }

            res=max(res, dp[i][1]);   //
        }
        return res;
    }
};

/*
300. 最长上升子序列
给定一个无序的整数数组，找到其中最长上升子序列的长度。
示例:
输入: [10,9,2,5,3,7,101,18]
输出: 4 
解释: 最长的上升子序列是 [2,3,7,101]，它的长度是 4。
说明:
可能会有多种最长上升子序列的组合，你只需要输出对应的长度即可。
你算法的时间复杂度应该为 O(n2) 。
进阶: 你能将算法的时间复杂度降低到 O(n log n) 吗?
*/

class Solution {
public:
    //dp[i]:以 nums[i] 结尾的「上升子序列」的长度。
    //注意：这个定义中 nums[i] 必须被选取，且必须是这个子序列的最后一个元素。
    int lengthOfLIS(vector<int>& nums) {
        int N=nums.size();
        if(N==0) return 0;
        vector<int> dp(N, 1);
        int res=1;   //
        for(int i=0; i<N; i++){
            for(int j=0; j<i; j++){
                if(nums[j]<nums[i])
                    dp[i]=max(dp[i],dp[j]+1);
            }
            res=max(res,dp[i]);   //
        }
        return res;
    }
};

/*
53. 最大子序和
给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
示例:
输入: [-2,1,-3,4,-1,2,1,-5,4],
输出: 6
解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。
进阶:
如果你已经实现复杂度为 O(n) 的解法，尝试使用更为精妙的分治法求解。
*/

class Solution{
public:
	//dp[i]：以 nums[i] 结尾的连续子数组的最大和。
    //注意：连续子数组一定要以 nums[i] 作为结尾。
	int maxSubArray(vector<int>& nums){
		int N=nums.size();
		if(N==0) return 0;
		vector<int> dp(N, 0);
		dp[0]=nums[0];
		int res=dp[0];   //
		for(int i=1; i<N; i++){
			if(dp[i-1]>0) dp[i]=dp[i-1]+nums[i];
			else dp[i]=nums[i];
			res=max(res,dp[i]);   //
		}
		return res;
	}
};

/*
718. 最长重复子数组
给两个整数数组 A 和 B ，返回两个数组中公共的、长度最长的子数组的长度。
示例 1:
输入:
A: [1,2,3,2,1]
B: [3,2,1,4,7]
输出: 3
解释: 
长度最长的公共子数组是 [3, 2, 1]。
说明:
1 <= len(A), len(B) <= 1000
0 <= A[i], B[i] < 100
*/

class Solution {
public:
    //dp[i][j] : A 以i结尾，B以j结尾的最长公共子数组
    int findLength(vector<int>& A, vector<int>& B) {
        int N1=A.size(), N2=B.size();
        vector<vector<int>> dp(N1+1, vector<int>(N2+1, 0));
        int res=0;   //
        for(int i=1; i<N1+1; i++){
            for(int j=1; j<N2+1; j++){
                if(A[i-1]==B[j-1]) dp[i][j]=dp[i-1][j-1]+1;
                else dp[i][j]=0;   //一定包含A[i-1]和B[j-1]的数组 没公共部分

                res=max(res,dp[i][j]);
            }
        }
        return res;   //
    }
};

/////////////////////////////////////////////////////////////////////////////////////

/*
5. 最长回文子串【连续的字母串】
给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。
示例 1：
输入: "babad"
输出: "bab"
注意: "aba" 也是一个有效答案。
示例 2：
输入: "cbbd"
输出: "bb"
*/

class Solution {
public:
    //dp[i,j] 表示字符串 s 的第 i 到 j 个字母组成的串（下文表示成 s[i:j]）是否为回文串
    string longestPalindrome(string s) {
        int N = s.size();
        if(N == 0 || N == 1) return s;

        string res = string(1, s[0]);   //
        int curlen = 1;  

        vector<vector<bool>> dp(N, vector<bool>(N, false));
        for(int j = 0; j < N; j++){
            for(int i = j; i >= 0; i--){   //固定右边界，左边界逐渐从j向左滑动
                if((s[i] == s[j] && j - i <= 2) || (s[i] == s[j] && dp[i + 1][j - 1] )){
                    dp[i][j] = true;

                    if(j - i + 1 > curlen){   //
                        res = s.substr(i, j - i + 1);   //取从i开始 向后j-i+1长度子串
                        curlen = j - i + 1;
                    }
                }
            }
        }
        return res;
    }
};

/*
516. 最长回文子序列【不连续的字母序列】
给定一个字符串 s ，找到其中最长的回文子序列，并返回该序列的长度。可以假设 s 的最大长度为 1000 。
示例 1:
输入:
"bbbab"
输出:
4
一个可能的最长回文子序列为 "bbbb"。
示例 2:
输入:
"cbbd"
输出:
2
一个可能的最长回文子序列为 "bb"。
提示：
1 <= s.length <= 1000
s 只包含小写英文字母
*/

class Solution {
public:
    //dp[i][j]：在子串 s[i..j] 中，最长回文子序列的长度为
    int longestPalindromeSubseq(string s) {
        int N=s.size();
        vector<vector<int>> dp(N, vector<int>(N,0));
        for(int i=0; i<N; i++) dp[i][i]=1;
        for(int i=N-1; i>=0; i--){   //从后向前遍历 防止覆盖
            for(int j=i+1; j<N; j++){
                if(s[i]==s[j]) dp[i][j]=dp[i+1][j-1]+2;
                else dp[i][j]=max(dp[i+1][j],dp[i][j-1]);
            }
        }
        return dp[0][N-1];
    }
};

/*
139. 单词拆分
给定一个非空字符串 s 和一个包含非空单词列表的字典 wordDict，判定 s 是否可以被空格拆分为一个或多个在字典中出现的单词。
说明：
拆分时可以重复使用字典中的单词。
你可以假设字典中没有重复的单词。
示例 1：
输入: s = "leetcode", wordDict = ["leet", "code"]
输出: true
解释: 返回 true 因为 "leetcode" 可以被拆分成 "leet code"。
示例 2：
输入: s = "applepenapple", wordDict = ["apple", "pen"]
输出: true
解释: 返回 true 因为 "applepenapple" 可以被拆分成 "apple pen apple"。
     注意你可以重复使用字典中的单词。
示例 3：
输入: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
输出: false
*/

class Solution {
public:
    //dp[i] : 字符串s前i个字符组成的字符串s[0..i−1]是否能被空格拆分成若干个字典中出现的单词
    bool wordBreak(string s, vector<string>& wordDict) {
        int N=s.size();
        unordered_set<string> wordDictSet(wordDict.begin(), wordDict.end());        

        vector<bool> dp(N + 1);
        dp[0] = true;   //空串
        for (int i = 1; i<N+1; ++i) {
            for (int j = 0; j < i; ++j) {   //dp[j]真 & s[j...i-1]字典成词
                if (dp[j] && wordDictSet.find(s.substr(j, i - j)) != wordDictSet.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[N];
    }
};

/*
1143. 最长公共子序列
给定两个字符串 text1 和 text2，返回这两个字符串的最长公共子序列的长度。
一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。两个字符串的「公共子序列」是这两个字符串所共同拥有的子序列。
若这两个字符串没有公共子序列，则返回 0。
示例 1:
输入：text1 = "abcde", text2 = "ace" 
输出：3  
解释：最长公共子序列是 "ace"，它的长度为 3。
示例 2:
输入：text1 = "abc", text2 = "abc"
输出：3
解释：最长公共子序列是 "abc"，它的长度为 3。
示例 3:
输入：text1 = "abc", text2 = "def"
输出：0
解释：两个字符串没有公共子序列，返回 0。
提示:
1 <= text1.length <= 1000
1 <= text2.length <= 1000
输入的字符串只含有小写英文字符。
*/

class Solution {
public:
    //dp[i][j] ：对于 s1[1..i] 和 s2[1..j]，它们的 LCS 长度是 dp[i][j]。
    int longestCommonSubsequence(string text1, string text2) {
        int N1=text1.size(), N2=text2.size();
        if(N1==0 || N2==0) return 0;
        vector<vector<int>> dp(N1+1, vector<int>(N2+1, 0));   //第0行和第0列表示其中一个串包含0个字符
        for(int i=1; i<N1+1; i++){
            for(int j=1; j<N2+1; j++){   //注意这里遍历起始范围和dp数组初始化，共同提供了dp的base case边界
                if(text1[i-1]==text2[j-1]) dp[i][j]=dp[i-1][j-1]+1;
                else dp[i][j]=max(dp[i-1][j], dp[i][j-1]);
            }
        }
        return dp[N1][N2];
    }
};

/*
1371. 每个元音包含偶数次的最长子字符串
给你一个字符串 s ，请你返回满足以下条件的最长子字符串的长度：每个元音字母，即 'a'，'e'，'i'，'o'，'u' ，在子字符串中都恰好出现了偶数次。
示例 1：
输入：s = "eleetminicoworoep"
输出：13
解释：最长子字符串是 "leetminicowor" ，它包含 e，i，o 各 2 个，以及 0 个 a，u 。
示例 2：
输入：s = "leetcodeisgreat"
输出：5
解释：最长子字符串是 "leetc" ，其中包含 2 个 e 。
示例 3：
输入：s = "bcbcbc"
输出：6
解释：这个示例中，字符串 "bcbcbc" 本身就是最长的，因为所有的元音 a，e，i，o，u 都出现了 0 次。
提示：
1 <= s.length <= 5 x 10^5
s 只包含小写英文字母。
*/

class Solution{
public:
    //dp[status]：当前元音奇偶次数组合status 对应的遍历s串位置索引。
    //如status=01000，dp[status]=5表示 遍历到s串索引为5的位置时，e都出现了奇数次，其它元音为偶数次。
    int findTheLongestSubstring(string s){
        int res=0, status=0, N=s.size();
        vector<int> dp(1<<5, -1);
        dp[0]=0;
        for(int i=0; i<N; i++){
            if(s[i]=='a') status ^= 1<<0;
            else if(s[i]=='e') status ^= 1<<1;
            else if(s[i]=='i') status ^= 1<<2;
            else if(s[i]=='o') status ^= 1<<3;
            else if(s[i]=='u') status ^= 1<<4;

            if(dp[status]>=0) res=max(res, i+1-dp[status]);      //再次达到status元音字母组合态，更新两次相同字母组合态之间的s串长
            else dp[status]=i+1;    //初次达到status元音字母组合态，更新位置索引
        }
        return res;
    }
};

/*
72. 编辑距离
给你两个单词 word1 和 word2，请你计算出将 word1 转换成 word2 所使用的最少操作数 。
你可以对一个单词进行如下三种操作：
插入一个字符
删除一个字符
替换一个字符
示例 1：
输入：word1 = "horse", word2 = "ros"
输出：3
解释：
horse -> rorse (将 'h' 替换为 'r')
rorse -> rose (删除 'r')
rose -> ros (删除 'e')
示例 2：
输入：word1 = "intention", word2 = "execution"
输出：5
解释：
intention -> inention (删除 't')
inention -> enention (将 'i' 替换为 'e')
enention -> exention (将 'n' 替换为 'x')
exention -> exection (将 'n' 替换为 'c')
exection -> execution (插入 'u')
*/

class Solution {
public:
    //dp[i][j] : A 的前 i 个字母和 B 的前 j 个字母之间的编辑距离
    int minDistance(string word1, string word2) {
        int N1=word1.size(), N2=word2.size();
        vector<vector<int>> dp(N1+1, vector<int>(N2+1, 0));
        for(int i = 0; i < N1+1; i++) dp[i][0] = i;   //第一列的每一行
        for(int j = 0; j < N2+1; j++) dp[0][j] = j;   //第一行的每一列
        for(int i = 1; i < N1+1; i++){
            for(int j = 1; j < N2+1; j++){
                int tmp = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1);   //把i删除，在i后插入j[这里tmp表示 就是为了便于 三个值求max比较 ]
                if(word1[i - 1] == word2[j - 1])   //在二维dp数组里：dp[i][j]位置 对应的两个比较字母是 word1[i-1]和word2[j-1]
                    dp[i][j] = min(dp[i - 1][j - 1], tmp);
                else
                    dp[i][j] = min(dp[i - 1][j - 1] + 1, tmp);   //把i替换成j
            }
        }
        return dp[N1][N2];
    }
};

/*
10. 正则表达式匹配
给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。
'.' 匹配任意单个字符
'*' 匹配零个或多个前面的那一个元素
所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。
说明:
s 可能为空，且只包含从 a-z 的小写字母。
p 可能为空，且只包含从 a-z 的小写字母，以及字符 . 和 *。
示例 1:
输入:
s = "aa"
p = "a"
输出: false
解释: "a" 无法匹配 "aa" 整个字符串。
示例 2:
输入:
s = "aa"
p = "a*"
输出: true
解释: 因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。
示例 3:
输入:
s = "ab"
p = ".*"
输出: true
解释: ".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。
示例 4:
输入:
s = "aab"
p = "c*a*b"
输出: true
解释: 因为 '*' 表示零个或多个，这里 'c' 为 0 个, 'a' 被重复一次。因此可以匹配字符串 "aab"。
示例 5:
输入:
s = "mississippi"
p = "mis*is*p*."
输出: false
*/

class Solution {
public:
    //dp[i][j] : s的前i个字符和p的前j个字符 是否匹配
	// abc*不能匹配a, .*可以匹配abc, ac*可以匹配a
    bool isMatch(string s, string p) {
        int N1 = s.size();
        int N2 = p.size();
        vector<vector<bool>> dp(N1+1, vector<bool>(N2+1, false));   
        dp[0][0] = true;
        for(int j = 1; j < N2+1; j++){   //j表示p串的前j个字符
            if(j >= 2 && p[j - 1] == '*'){   //p的第j个字符是*, p的后两个字符直接忽略
                dp[0][j] = dp[0][j - 2];
            }
        }
        for(int i = 1; i < N1+1; i++){
            for(int j = 1; j < N2+1; j++){
                if(p[j - 1] == s[i - 1] || p[j - 1] == '.'){
                    dp[i][j] = dp[i - 1][j - 1];
                } else if(p[j - 1] == '*') {   //遇到*，要从后向前，尽量使用它 去匹配掉s里的字符                              
                    //p串倒数第二个字母和s串最后一个字母相同，只需要考察s串最后一个字母前的部分 和p串关系 [s=abccc, p=abc*]
                    //p串倒数第二个位置是. 则s串最后一个字母无论是什么，都可以把s的最后一个字母忽略 [s=abcc, p=ab.*]
                    //p串最后两个字符 a*或.* 没被用上，直接看s串和p去掉后两个字符的匹配
                    dp[i][j] = (s[i - 1] == p[j - 2] && dp[i - 1][j]) \
                            || ('.' == p[j - 2] && dp[i - 1][j]) \
                            || dp[i][j - 2];
                }
            }
        }
        return dp[N1][N2];
    }
};

/*
44. 通配符匹配
给定一个字符串 (s) 和一个字符模式 (p) ，实现一个支持 '?' 和 '*' 的通配符匹配。
'?' 可以匹配任何单个字符。
'*' 可以匹配任意字符串（包括空字符串）。
两个字符串完全匹配才算匹配成功。
说明:
s 可能为空，且只包含从 a-z 的小写字母。
p 可能为空，且只包含从 a-z 的小写字母，以及字符 ? 和 *。
示例 1:
输入:
s = "aa"
p = "a"
输出: false
解释: "a" 无法匹配 "aa" 整个字符串。
示例 2:
输入:
s = "aa"
p = "*"
输出: true
解释: '*' 可以匹配任意字符串。
示例 3:
输入:
s = "cb"
p = "?a"
输出: false
解释: '?' 可以匹配 'c', 但第二个 'a' 无法匹配 'b'。
示例 4:
输入:
s = "adceb"
p = "*a*b"
输出: true
解释: 第一个 '*' 可以匹配空字符串, 第二个 '*' 可以匹配字符串 "dce".
示例 5:
输入:
s = "acdcb"
p = "a*c?b"
输出: false
*/




