
/*
author:young
字符串双指针
*/

//字符串双指针：滑动窗口

/*
30. 串联所有单词的子串
给定一个字符串 s 和一些长度相同的单词 words。找出 s 中恰好可以由 words 中所有单词串联形成的子串的起始位置。
注意子串要与 words 中的单词完全匹配，中间不能有其他字符，但不需要考虑 words 中单词串联的顺序。
示例 1：
输入：
  s = "barfoothefoobarman",
  words = ["foo","bar"]
输出：[0,9]
解释：
从索引 0 和 9 开始的子串分别是 "barfoo" 和 "foobar" 。
输出的顺序不重要, [9,0] 也是有效答案。
示例 2：
输入：
  s = "wordgoodgoodgoodbestword",
  words = ["word","good","best","word"]
输出：[]
*/
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        int N=words.size();
        if(N==0) return res;

        unordered_map<string, int> um1;
        for(auto i:words) um1[i]+=1;

        int One=words[0].size();
        for(int i=0; i<One; i++){
            int left=i, right=i, cnt=0;
            unordered_map<string, int> um2;
            while(left+N*One<=s.size()){
                string tmp="";
                while(cnt<N){   //窗口内词数
                    tmp=s.substr(right,One);
                    if(um1.find(tmp)==um1.end() || um2[tmp]>um1[tmp]) break;
                    um2[tmp]++;
                    cnt++;
                    right+=One;
                }
                if(um2==um1) res.push_back(left);
                if(um1.find(tmp)!=um1.end()){   //最后一个词是词表里的词，缩减左边界
                    um2[s.substr(left,One)]--;
                    cnt--;
                    left+=One;
                }else{   //完全丢弃遍历过的部分
                    right+=One;
                    left=right;
                    cnt=0;
                    um2.clear();
                }
            }
        }
        return res;
    }
};

/*
125. 验证回文串【注意字符串预处理：大写转小写】
给定一个字符串，验证它是否是回文串，只考虑字母和数字字符，可以忽略字母的大小写。
说明：本题中，我们将空字符串定义为有效的回文串。
示例 1:
输入: "A man, a plan, a canal: Panama"
输出: true
示例 2:
输入: "race a car"
输出: false
*/
class Solution {
public:
    bool isPalindrome(string s) {
        string tmp="";
        for(auto i:s){
            if(islower(i)||isdigit(i)) tmp+=i;
            else if(isupper(i)) tmp+=(i+32);
        }

        int left=0, right=tmp.size()-1;
        while(left<right){
            if(tmp[left]!=tmp[right]) return false;
            left++;
            right--;
        }

        return true;
    }
};

/*
680. 验证回文字符串 Ⅱ
给定一个非空字符串 s，最多删除一个字符。判断是否能成为回文字符串。
示例 1:
输入: "aba"
输出: True
示例 2:
输入: "abca"
输出: True
解释: 你可以删除c字符。
注意:
字符串只包含从 a-z 的小写字母。字符串的最大长度是50000。
*/
class Solution {
public:
    bool validPalindrome(string s) {
        int N=s.size();
        if(N==0) return true;
        int i=0, j=N-1;
        while(i<j){
            if(s[i]==s[j]){
                i++;
                j--;
            }else{
                return check(s,i+1,j) || check(s,i,j-1);
            }
        }
        return true;
    }

    bool check(string& s, int left, int right){
        if(left>=right) return true;
        while(left<right){
            if(s[left]!=s[right]) return false;
            left++;
            right--;
        }
        return true;
    }
};

/*
345. 反转字符串中的元音字母
编写一个函数，以字符串作为输入，反转该字符串中的元音字母。
示例 1:
输入: "hello"
输出: "holle"
示例 2:
输入: "leetcode"
输出: "leotcede"
说明:
元音字母不包含字母"y"。
*/
class Solution {
public:
    string reverseVowels(string s) {
        unordered_set<char> us={'a','e','i','o','u','A','E','I','O','U'};
        int N=s.size();
        if(N==0) return s;
        int left=0, right=N-1;
        while(left<right){
            if(us.find(s[left])!=us.end() && us.find(s[right])!=us.end()){
                swap(s[left], s[right]);
                left++;
                right--;
            } 
            else if(us.find(s[left])==us.end()) left++;
            else if(us.find(s[right])==us.end()) right--;
        }
        return s;
    }
};





