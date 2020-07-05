
/*
author:young
二叉树：构建二叉树
*/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct ListNode{
	int val;
	ListNode* next;
	ListNode(int x):val(x),next(nullptr){}
};

/*
108. 将有序数组转换为二叉搜索树
将一个按照升序排列的有序数组，转换为一棵高度平衡二叉搜索树。
本题中，一个高度平衡二叉树是指一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1。
示例:
给定有序数组: [-10,-3,0,5,9],
一个可能的答案是：[0,-3,9,-10,null,5]，它可以表示下面这个高度平衡二叉搜索树：
      0
     / \
   -3   9
   /   /
 -10  5
*/
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return helper(nums, 0, nums.size() - 1);
    }

    TreeNode* helper(vector<int>& nums, int left, int right) {
        if (left > right) return nullptr;
        int mid = (left + right) / 2;   // 总是选择中间位置左边的数字作为根节点
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = helper(nums, left, mid - 1);
        root->right = helper(nums, mid + 1, right);
        return root;
    }
};
//-----------------------------------------------------------------
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        int N=nums.size();
        if(N==0) return nullptr;
        TreeNode* root=new TreeNode(nums[N/2]);
        vector<int> sl1(nums.begin(), nums.begin()+N/2);
        vector<int> sl2(nums.begin()+N/2+1, nums.end());
        root->left=sortedArrayToBST(sl1);
        root->right=sortedArrayToBST(sl2);
        return root;
    }
};

/*
109. 有序链表转换二叉搜索树【树的先序遍历DFS】
给定一个单链表，其中的元素按升序排序，将其转换为高度平衡的二叉搜索树。
本题中，一个高度平衡二叉树是指一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1。
示例:
给定的有序链表： [-10, -3, 0, 5, 9],
一个可能的答案是：[0, -3, 9, -10, null, 5], 它可以表示下面这个高度平衡二叉搜索树：
      0
     / \
   -3   9
   /   /
 -10  5
*/
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        return helper(head, nullptr);
    }

    TreeNode* helper(ListNode* head, ListNode* tail){
        if(head==tail) return nullptr;
        ListNode* vir=new ListNode(-1);
        vir->next=head;
        ListNode* cur=vir;
        ListNode* pre=vir;
        while(cur!=tail && cur->next!=tail){
            cur=cur->next->next;
            pre=pre->next;
        }
        TreeNode* root=new TreeNode(pre->val);
        root->left=helper(head, pre);
        root->right=helper(pre->next, tail);
        return root;
    }
};
//-----------------------------------------------------------------
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if(!head) return nullptr;

        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* pre = nullptr;
        while (fast && fast->next) {
            fast = fast->next->next;
            pre = slow;   //pre停在了前半段尾部
            slow = slow->next;   //slow停到了后半段头部
        }

        if(pre) pre->next = nullptr;   //

        TreeNode* root = new TreeNode(slow->val);
        root->left = sortedListToBST(head == slow ? pre : head);   //对于单节点 slow没移动的情况，slow作为root了
        root->right = sortedListToBST(slow->next);
        
        return root;
    }
};

/*
114. 二叉树展开为链表
给定一个二叉树，原地将它展开为一个单链表。
例如，给定二叉树
    1
   / \
  2   5
 / \   \
3   4   6
将其展开为：
1
 \
  2
   \
    3
     \
      4
       \
        5
         \
          6
*/
class Solution {
public:
    //左右子树分别展开成链表
    void flatten(TreeNode* root) {
        if(!root) return;
        TreeNode* L=root->left;
        TreeNode* R=root->right;
        
        flatten(L);
        flatten(R);

        root->left = nullptr;
        root->right = L; 

        TreeNode* cur=root;
        while(cur->right)   
        	cur= cur->right;
        cur->right=R;
        return;
    }
};

/*
105. 从前序与中序遍历序列构造二叉树
根据一棵树的前序遍历与中序遍历构造二叉树。
注意:
你可以假设树中没有重复的元素。
例如，给出
前序遍历 preorder = [3,9,20,15,7]
中序遍历 inorder = [9,3,15,20,7]
返回如下的二叉树：

    3
   / \
  9  20
    /  \
   15   7
*/
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {   //根左右 左根右
        if(preorder.size() == 0 || inorder.size() == 0 || preorder.size() != inorder.size()) return nullptr;
        return helper(preorder, 0, preorder.size()-1, inorder, 0, inorder.size() - 1);
    }

    TreeNode* helper(vector<int>& preorder, int preS, int preE, vector<int>& inorder, int inS, int inE){
        if(preS > preE) return nullptr;
        TreeNode* root = new TreeNode(preorder[preS]);
        if(preS == preE) return root;

        int findR = inS;
        while(findR < inE && preorder[preS] != inorder[findR]){
            findR++;
        }

        int offset = findR - inS;   // findR+offset指向root
        root->left = helper(preorder, preS+1, preS+offset, inorder, inS, inS+offset-1);
        root->right = helper(preorder, preS+offset+1, preE, inorder, inS+offset+1, inE);
        return root;
    }
};
//-----------------------------------------------------------------
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {   //根左右 左根右
        if(preorder.size() == 0 || inorder.size() == 0 || preorder.size() != inorder.size()) return nullptr;
        int preS=0, preE=preorder.size()-1, inS=0, inE=inorder.size()-1;

        if(preS > preE) return nullptr;
        TreeNode* root = new TreeNode(preorder[preS]);
        if(preS == preE) return root;

        int findR = inS;
        while(findR < inE && preorder[preS] != inorder[findR]){
            findR++;
        }        
        int offset = findR - inS;   // findR+offset指向root

        vector<int> prel(preorder.begin()+1, preorder.begin()+offset+1);   //左闭右开
        vector<int> inl(inorder.begin(), inorder.begin()+offset);
        vector<int> prer(preorder.begin()+offset+1, preorder.end());
        vector<int> inr(inorder.begin()+offset+1, inorder.end());

        root->left = buildTree(prel, inl);
        root->right = buildTree(prer, inr);
        return root;
    }
};

/*
106. 从中序与后序遍历序列构造二叉树
根据一棵树的中序遍历与后序遍历构造二叉树。
注意:
你可以假设树中没有重复的元素。
例如，给出
中序遍历 inorder = [9,3,15,20,7]
后序遍历 postorder = [9,15,7,20,3]
返回如下的二叉树：
    3
   / \
  9  20
    /  \
   15   7
*/
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {   //左根右 左右根
        if(inorder.size() == 0 || postorder.size() == 0 || inorder.size() != postorder.size()) return nullptr;
        return helper(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1);
    }

    TreeNode* helper(vector<int>& inorder, int inS, int inE, vector<int>& postorder, int postS, int postE) {
        if(inS > inE) return nullptr;
        TreeNode* root = new TreeNode(postorder[postE]);
        if(inS == inE) return root;
        int findR = inS;
        while(findR < inE && postorder[postE] != inorder[findR]){   //findR最终指向root
            findR++;
        }
        int offset = findR - inS;   //inS+offset是root
        root->left = helper(inorder, inS, inS+offset-1, postorder, postS, postS+offset-1);
        root->right = helper(inorder, inS+offset+1, inE, postorder, postS+offset, postE-1);
        return root;
    }
};
//-----------------------------------------------------------------
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {   //左根右 左右根
        if(inorder.size() == 0 || postorder.size() == 0 || inorder.size() != postorder.size()) return nullptr;
        int inS=0, inE=inorder.size() - 1, postS=0, postE=postorder.size() - 1;
        
        if(inS > inE) return nullptr;
        TreeNode* root = new TreeNode(postorder[postE]);
        if(inS == inE) return root;

        int findR = inS;
        while(findR < inE && postorder[postE] != inorder[findR]){   //findR最终指向root
            findR++;
        }
        int offset = findR - inS;   //inS+offset是root

        vector<int> inl(inorder.begin(), inorder.begin()+offset);
        vector<int> postl(postorder.begin(), postorder.begin()+offset);
        vector<int> inr(inorder.begin()+offset+1, inorder.end());
        vector<int> postr(postorder.begin()+offset, postorder.end()-1);

        root->left = buildTree(inl, postl);
        root->right = buildTree(inr, postr);
        return root;
    }
};

/*
889. 根据前序和后序遍历构造二叉树【less】
返回与给定的前序和后序遍历匹配的任何二叉树。
pre 和 post 遍历中的值是不同的正整数。
示例：
输入：pre = [1,2,4,5,3,6,7], post = [4,5,2,6,7,3,1]
输出：[1,2,3,4,5,6,7]
提示：
1 <= pre.length == post.length <= 30
pre[] 和 post[] 都是 1, 2, ..., pre.length 的排列
每个输入保证至少有一个答案。如果有多个答案，可以返回其中一个。
*/
class Solution {
public:
    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {   //根左右 左右根[后序遍历，左子树的根节点是左子树里最后被遍历到的原始 找到该元素就可以切出左子树]
        if(pre.size() == 0 || post.size() == 0 || pre.size() != post.size()) return nullptr;
        return helper(pre, 0, pre.size()-1, post, 0, post.size() - 1);
    }

    TreeNode* helper(vector<int>& pre, int preS, int preE, vector<int>& post, int postS, int postE){
        if(preS > preE) return nullptr;
        TreeNode* root = new TreeNode(pre[preS]);
        if(preS == preE) return root;

        int findR = postS;
        while(findR < postE && pre[preS+1] != post[findR]){
            findR++;
        }
        int offset = findR - postS;   //找到左子树根节点的位置

        root->left=helper(pre, preS+1, preS+offset+1, post, postS, postS+offset);
        root->right=helper(pre, preS+offset+2, preE, post, postS+offset+1, postE-1);
        return root;
    }
};
//-----------------------------------------------------------------
class Solution {
public:
    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {   //根左右 左右根[后序遍历，左子树的根节点是左子树里最后被遍历到的原始 找到该元素就可以切出左子树]
        if(pre.size() == 0 || post.size() == 0 || pre.size() != post.size()) return nullptr;
        int preS=0, preE=pre.size()-1, postS=0, postE=post.size()-1;
        
        if(preS > preE) return nullptr;
        TreeNode* root = new TreeNode(pre[preS]);
        if(preS == preE) return root;

        int findR = postS;
        while(findR < postE && pre[preS+1] != post[findR]){
            findR++;
        }
        int offset = findR - postS;   //找到左子树根节点的位置

        vector<int> prel(pre.begin()+1, pre.begin()+offset+2);   //[begin+1, begin+offset+1]
        vector<int> postl(post.begin(), post.begin()+offset+1);   //[begin, begin+offset]
        vector<int> prer(pre.begin()+offset+2, pre.end());   //[begin+offset+2, end-1]
        vector<int> postr(post.begin()+offset+1, post.end()-1);   //[begin+offset+1, end-2]

        root->left=constructFromPrePost(prel, postl);
        root->right=constructFromPrePost(prer, postr);
        return root;
    }
};

///////////////////////////////////////////////////////////////////////////////////

/*
96. 不同的二叉搜索树【树形dp】
给定一个整数 n，求以 1 ... n 为节点组成的二叉搜索树有多少种？
示例:
输入: 3
输出: 5
解释:
给定 n = 3, 一共有 5 种不同结构的二叉搜索树:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
*/
class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n+1, 0);   //这里必须初始化0,不能是1,因为下面dp[i]+=计算 会累加本身
        dp[0]=1, dp[1]=1;
        cout<<dp[0]<<"  "<<dp[1]<<endl;
        for(int i=2; i<n+1; i++){
            for(int j=1; j<=i; j++){   //可选的哪个节点做树根
                //cout<<"~~~"<<dp[j-1]<<"  "<<dp[i-j]<<endl;
                dp[i]+=dp[j-1]*dp[i-j];       
            }
        }
        return dp[n];
    }
};

/*
95. 不同的二叉搜索树 II
给定一个整数 n，生成所有由 1 ... n 为节点所组成的 二叉搜索树 。
示例：
输入：3
输出：
[
  [1,null,3,2],
  [3,2,null,1],
  [3,1,null,null,2],
  [2,1,3],
  [1,null,2,null,3]
]
解释：
以上的输出对应以下 5 种不同结构的二叉搜索树：

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
*/
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        if(n == 0) return {};
        return helper(1, n);
    } 

    vector<TreeNode*> helper(int start, int end){
        vector<TreeNode*> res;
        if(start > end) return {nullptr};
        
        for(int i = start; i <= end; i++){
            vector<TreeNode*> left = helper(start, i-1);
            vector<TreeNode*> right = helper(i+1, end);
            for(int L = 0; L < left.size(); L++){
                for(int R = 0; R < right.size(); R++){
                    TreeNode* root = new TreeNode(i);
                    root->left = left[L];
                    root->right = right[R];
                    res.push_back(root);
                }
            }
        }
        return res;
    }
};















