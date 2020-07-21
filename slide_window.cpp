  
/*
author:young
滑动窗口
*/

/*
3. 无重复字符的最长子串
给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。
示例 1:
输入: "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
示例 2:
输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3:
输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
*/

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> window;
        int left=0,right=0,res=0;
        while(right<s.size()){
            char c=s[right];
            right++;
            window[c]++;
            while(window[c]>1){
                char d=s[left];
                left++;
                window[d]--;
            }
            res=max(res,right-left);
        }
        return res;
    }
};

/*
76. 最小覆盖子串
给你一个字符串 S、一个字符串 T，请在字符串 S 里面找出：包含 T 所有字符的最小子串。
示例：
输入: S = "ADOBECODEBANC", T = "ABC"
输出: "BANC"
说明：
如果 S 中不存这样的子串，则返回空字符串 ""。
如果 S 中存在这样的子串，我们保证它是唯一的答案。
*/

class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char,int> need,window;
        for(char c:t) need[c]++;
        int left=0,right=0,valid=0,start=0,len=INT_MAX;
        while(right<s.size()){
            char c=s[right];
            right++;
            if(need.count(c)){
                window[c]++;
                if(window[c]==need[c]) valid++;
            }
            while(need.size()==valid){
                if(right-left<len){
                    start=left;
                    len=right-left;
                }
                char d= s[left];
                left++;
                if(need.count(d)){
                    if(window[d]==need[d]) valid--;
                    window[d]--;
                }
            }
        }
        return (len==INT_MAX)?"":s.substr(start,len);
    }
};


/*
239. 滑动窗口最大值
给定一个数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。
返回滑动窗口中的最大值。
进阶：
你能在线性时间复杂度内解决此题吗？
示例:
输入: nums = [1,3,-1,-3,5,3,6,7], 和 k = 3
输出: [3,3,5,5,6,7] 
解释: 
  滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
提示：
1 <= nums.length <= 10^5
-10^4 <= nums[i] <= 10^4
1 <= k <= nums.length
*/

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        if(k==0) return res;
        deque<int> window;
        int right=0;
        while(right<nums.size()){
            if(!window.empty() && right-window.front()>=k){
                window.pop_front();
            }
            while(!window.empty() && nums[window.back()] < nums[right]){
                window.pop_back();
            }
            window.push_back(right);
            right++;
            if(right>=k) res.push_back(nums[window.front()]);
        }
        return res;
    }
};

/*
209. 长度最小的子数组
给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的 连续 子数组，并返回其长度。如果不存在符合条件的子数组，返回 0。
示例：
输入：s = 7, nums = [2,3,1,2,4,3]
输出：2
解释：子数组 [4,3] 是该条件下的长度最小的子数组。
进阶：
如果你已经完成了 O(n) 时间复杂度的解法, 请尝试 O(n log n) 时间复杂度的解法。
*/
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int N = nums.size();
        if(N == 0) return 0;
        int left = 0, right = 0, res = N+1;
        int partSum = 0;   //当前片段数组和
        while(right < N){
            partSum += nums[right];
            right++;
            while(partSum >= s){
                res = min(res, right-left);
                partSum -= nums[left];
                left++;
            }    
        }
        return res == N+1 ? 0 : res;
    }
};

/*
438. 找到字符串中所有字母异位词
给定一个字符串 s 和一个非空字符串 p，找到 s 中所有是 p 的字母异位词的子串，返回这些子串的起始索引。
字符串只包含小写英文字母，并且字符串 s 和 p 的长度都不超过 20100。
说明：
字母异位词指字母相同，但排列不同的字符串。
不考虑答案输出的顺序。
示例 1:
输入:
s: "cbaebabacd" p: "abc"
输出:
[0, 6]
解释:
起始索引等于 0 的子串是 "cba", 它是 "abc" 的字母异位词。
起始索引等于 6 的子串是 "bac", 它是 "abc" 的字母异位词。
 示例 2:
输入:
s: "abab" p: "ab"
输出:
[0, 1, 2]
解释:
起始索引等于 0 的子串是 "ab", 它是 "ab" 的字母异位词。
起始索引等于 1 的子串是 "ba", 它是 "ab" 的字母异位词。
起始索引等于 2 的子串是 "ab", 它是 "ab" 的字母异位词。
*/

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {   //s是匹配串，p是模式串
        unordered_map<char, int> need,window;
        for(char c:p) need[c]++;
        int left=0,right=0,valid=0;
        vector<int> res;
        while(right<s.size()){
            char c = s[right];
            right++;
            if(need.count(c)){
                window[c]++;
                if(need[c]==window[c]) valid++;
            }
            while(right-left==p.size()){
                if(valid==need.size()) res.push_back(left);
                char d=s[left];
                left++;
                if(need.count(d)){
                    if(need[d]==window[d]) valid--;
                    window[d]--;
                }
            }
        }
        return res;
    }
};

/*
567. 字符串的排列
给定两个字符串 s1 和 s2，写一个函数来判断 s2 是否包含 s1 的排列。
换句话说，第一个字符串的排列之一是第二个字符串的子串。
示例1:
输入: s1 = "ab" s2 = "eidbaooo"
输出: True
解释: s2 包含 s1 的排列之一 ("ba").
示例2:
输入: s1= "ab" s2 = "eidboaoo"
输出: False
注意：
输入的字符串只包含小写字母
两个字符串的长度都在 [1, 10,000] 之间
*/

class Solution {
public:
    bool checkInclusion(string s1, string s2) {   //s1是模式串，s2是匹配串
        unordered_map<char, int> need, window;
        for(auto c:s1) need[c]++;
        int left = 0, right = 0, valid = 0;
        while(right < s2.size()){
            char c = s2[right];
            right++;
            if(need.count(c)){
                window[c]++;
                if(need[c]==window[c]) valid++;
            }
            while(right-left==s1.size()){
                if(need.size()==valid)
                    return true;
                char d = s2[left];
                left++;
                if(need.count(d)){
                    if(need[d]==window[d]) valid--;
                    window[d]--;
                }
            }
        }
        return false;
    }
};

/*
424. 替换后的最长重复字符
给你一个仅由大写英文字母组成的字符串，你可以将任意位置上的字符替换成另外的字符，总共可最多替换 k 次。在执行上述操作后，找到包含重复字母的最长子串的长度。
注意:
字符串长度 和 k 不会超过 104。
示例 1:
输入:
s = "ABAB", k = 2
输出:
4
解释:
用两个'A'替换为两个'B',反之亦然。
示例 2:
输入:
s = "AABABBA", k = 1
输出:
4
解释:
将中间的一个'A'替换为'B',字符串变为 "AABBBBA"。
子串 "BBBB" 有最长重复字母, 答案为 4。
*/

class Solution {
public:
    int characterReplacement(string s, int k){
        unordered_map<char,int> window;
        int left=0,right=0,res=0,maxc=0;
        while(right < s.size()){
            window[s[right]]++;
            maxc=max(maxc,window[s[right]]);   //窗口内出现次数最多元素出现次数

            while(right-left+1 > maxc+k){   //窗口长度>最多重复元素次数+可修改的k个元素
                window[s[left]]--;
                left++;
            }

            res=max(res,right-left+1);
            right++;
        }
        return res;
    }
};


/*
159. 至多包含两个不同字符的最长子串
给定一个字符串 s ，找出 至多 包含两个不同字符的最长子串 t ，并返回该子串的长度。
示例 1:
输入: "eceba"
输出: 3
解释: t 是 "ece"，长度为3。
示例 2:
输入: "ccaabbb"
输出: 5
解释: t 是 "aabbb"，长度为5。
*/

class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s)
    {
        unordered_map<char, int> window;
        int left = 0, right = 0, res = 0;
        while(right<s.size()){
            char c=s[right];
            right++;
            window[c]++;
            while(window.size() > 2){   //窗口内包含的字母种类
                char d=s[left];
                left++;
                window[d]--;
                if(window[d] == 0){   //窗口内d字符的个数为0，把d字母从窗口内擦去
                    window.erase(d);
                }
            }
            res = max(res, right-left);
        }
        return res;
    }
};

