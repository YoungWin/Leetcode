
/*
author:young
二叉树：路径相关计算
*/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


/*
112. 路径总和【后序遍历 - 路径的定义】
给定一个二叉树和一个目标和，判断该树中是否存在[根节点到叶子节点的路径]，这条路径上所有节点值相加等于目标和。
说明: 叶子节点是指没有子节点的节点。
示例: 
给定如下二叉树，以及目标和 sum = 22，
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \      \
        7    2      1
返回 true, 因为存在目标和为 22 的根节点到叶子节点的路径 5->4->11->2。
*/
class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if(!root && sum!=0) return false;
        stack<TreeNode*> st;
        TreeNode* cur=root;
        TreeNode* pre=nullptr;
        int res=sum;
        while(!st.empty() || cur){
            while(cur){
                st.push(cur);
                res-=cur->val;
                cur=cur->left;
            }
            cur=st.top();
            if(!cur->left && !cur->right && res==0) return true;
            if(!cur->right || pre==cur->right){
                st.pop();
                res+=cur->val;
                pre=cur;
                cur=nullptr;   //遍历过右节点 再回根节点 cur无法变空
            }else{
                cur=cur->right;
            }
        }
        return false;
    }
};
//------------------------------------------------------------
class Solution {  
public:
    bool hasPathSum(TreeNode* root, int sum) {
        return helper(root, sum);
    }

    bool helper(TreeNode* root, int res){
        if(!root) return false;
        
        res-=root->val;
        if(res==0 && !root->left && !root->right) return true;

        bool rs=helper(root->left, res);
        bool ls=helper(root->right, res);
        if(rs || ls) return true;
        return false;
    }
};

/*
113. 路径总和 II【后序遍历】
给定一个二叉树和一个目标和，找到所有从根节点到叶子节点路径总和等于给定目标和的路径。
说明: 叶子节点是指没有子节点的节点。
示例:
给定如下二叉树，以及目标和 sum = 22，
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1
返回:
[
   [5,4,11,2],
   [5,8,4,5]
]
*/
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> res;
        if(!root) return res;
        stack<TreeNode*> st;
        TreeNode* cur=root;
        TreeNode* pre=nullptr;
        int ressum=sum;
        vector<int> one;
        while(!st.empty() || cur){
            while(cur){
                st.push(cur);
                one.push_back(cur->val);
                ressum-=cur->val;
                cur=cur->left;
            }
            cur=st.top();
            if(!cur->left && !cur->right && ressum==0) res.push_back(one);
            if(!cur->right || cur->right==pre){
                st.pop();
                ressum+=cur->val;
                one.pop_back();
                pre=cur;
                cur=nullptr;
            }else{
                cur=cur->right;
            }
        }
        return res;
    }
};
//------------------------------------------------------------
class Solution {
    vector<vector<int>> res;
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<int> one;
        helper(root, sum, one);
        return res;
    }
    
    void helper(TreeNode* root, int ressum, vector<int>& one){
        if(!root) return;
        one.push_back(root->val);
        ressum -= root->val;   
        if(!root->left && !root->right && ressum==0) res.push_back(one);   //叶结点
        else{
            helper(root->left, ressum, one);
            helper(root->right, ressum, one);
        }     
        one.pop_back();
        ressum += root->val;
    }
};

/*
437. 路径总和 III【前缀和：到达当前元素的路径上，之前所有元素的和。】
给定一个二叉树，它的每个结点都存放着一个整数值。
找出路径和等于给定数值的路径总数。
路径不需要从根节点开始，也不需要在叶子节点结束，但是 [路径方向必须是向下的（只能从父节点到子节点）]。
二叉树不超过1000个节点，且节点数值范围是 [-1000000,1000000] 的整数。
示例：
root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8
      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1
返回 3。和等于 8 的路径有:
1.  5 -> 3
2.  5 -> 2 -> 1
3.  -3 -> 11
*/
class Solution {
    unordered_map<int, int> um;
    int res=0;
public:
    int pathSum(TreeNode* root, int sum) {
        um[0] = 1;
        helper(root, 0, sum);
        return res;
    }

    void helper(TreeNode* root, int ps, int sum) {
        if(!root) return;
        root->val += ps;   //到达当前元素的路径上，之前所有元素的和。
        res += um[root->val - sum];   //如果两个数的前缀总和是相同的，那么这些节点之间的元素总和为零。进一步扩展相同的想法，如果前缀总和currSum，在节点A和节点B处相差target，则位于节点A和节点B之间的元素之和是target。
        
        um[root->val]++;
        helper(root->left, root->val, sum);
        helper(root->right, root->val, sum);
        um[root->val]--;
    }
};

/*
124. 二叉树中的最大路径和
给定一个非空二叉树，返回其最大路径和。
本题中，路径被定义为一条 [从树中任意节点出发，达到任意节点的序列] 。该路径至少包含一个节点，且不一定经过根节点。
示例 1:
输入: [1,2,3]
       1
      / \
     2   3
输出: 6
示例 2:
输入: [-10,9,20,null,null,15,7]
   -10
   / \
  9  20
    /  \
   15   7
输出: 42
*/
class Solution {
    int res=INT_MIN;
public:
    int maxPathSum(TreeNode* root) {
        helper(root);
        return res;
    }

    int helper(TreeNode* root){
        if(!root) return 0;
        int ls=helper(root->left);
        int rs=helper(root->right);

        ls=(ls>0)?ls:0;
        rs=(rs>0)?rs:0;
        int root_start=max(ls, rs)+root->val;   //必须以root为起始点的最大路径和
        res=max(res, root->val + ls + rs);   //必须包含root的最大路径和
        return root_start;
    }
};

/*
257. 二叉树的所有路径
给定一个二叉树，返回所有从根节点到叶子节点的路径。
说明: 叶子节点是指没有子节点的节点。
示例:
输入:
   1
 /   \
2     3
 \
  5
输出: ["1->2->5", "1->3"]
解释: 所有根节点到叶子节点的路径为: 1->2->5, 1->3
*/
class Solution {
    vector<string> res;
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        if(!root) return res;
        helper(root, "");
        return res;
    }

    void helper(TreeNode* root, string tmp){
        if(!root) return;
        if(!root->left && !root->right){   //叶子节点
            tmp += to_string(root->val);
            res.push_back(tmp);
            return;
        }
        tmp += to_string(root->val) + "->";
        helper(root->left, tmp);
        helper(root->right, tmp);
    }
};

/*
543. 二叉树的直径
给定一棵二叉树，你需要计算它的直径长度。一棵二叉树的直径长度是[任意两个结点路径长度中的最大值]。这条路径可能穿过也可能不穿过根结点。
示例 :
给定二叉树
          1
         / \
        2   3
       / \     
      4   5    
返回 3, 它的长度是路径 [4,2,1,3] 或者 [5,2,1,3]。
注意：两结点之间的路径长度是以它们之间边的数目表示。
*/
class Solution {
    int res = 1;
public:
    int diameterOfBinaryTree(TreeNode* root) {
        helper(root);
        return res-1;
    }

    int helper(TreeNode* root){   //求树的最大深度,就是从树根出发的最长路径上结点数
        if(!root) return 0;
        int left = helper(root->left);  
        int right = helper(root->right);
        res = max(res, left+right+1);   //以root为根的最长路径上，结点总数
        return max(left, right) + 1;
    }
};

/*
687. 最长同值路径
给定一个二叉树，找到最长的路径，这个路径中的每个节点具有相同值。 这条路径可以经过也可以不经过根节点。
注意：两个节点之间的路径长度由它们之间的边数表示。
示例 1:
输入:
              5
             / \
            4   5
           / \   \
          1   1   5
输出:
2
示例 2:
输入:
              1
             / \
            4   5
           / \   \
          4   4   5
输出:
2
注意: 给定的二叉树不超过10000个结点。 树的高度不超过1000。
*/

class Solution {
    int res = 0;
public:
    int longestUnivaluePath(TreeNode* root) {
        helper(root);
        return res;
    }

    int helper(TreeNode* root){   //路径以root为起点的 最长同值路径包含的边数
        if(!root) return 0;
        int left = helper(root->left);
        int right = helper(root->right);
        
        if(root->left && root->val == root->left->val) left = left + 1;
        else left = 0;
        
        if(root->right && root->val == root->right->val) right = right + 1;
        else right = 0;
        
        res = max(res, left+right);

        return max(left, right);
    }
};











