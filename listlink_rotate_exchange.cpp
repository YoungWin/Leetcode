
/*
author:young
链表：翻转交换
*/

struct ListNode{
	int val;
	ListNode* next;
	ListNode(int x):val(x),next(nullptr){}
};


/*
206. 反转链表
反转一个单链表。
示例:
输入: 1->2->3->4->5->NULL
输出: 5->4->3->2->1->NULL
进阶:
你可以迭代或递归地反转链表。你能否用两种方法解决这道题？
*/
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* pre=NULL;
        ListNode* cur=head;
        while(cur){
            ListNode* tmp=cur->next;
            cur->next=pre;
            pre=cur;
            cur=tmp;
        }
        return pre;
    }
};

/*
24. 两两交换链表中的节点
给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。
你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
示例:
给定 1->2->3->4, 你应该返回 2->1->4->3.
*/
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* vir=new ListNode(-1);
        vir->next=head;
        ListNode* Op=vir;
        while(Op){
            ListNode* check=Op;
            for(int i=0; i<2; i++){
                if(!check->next) return vir->next;
                check=check->next;
            }

            ListNode* pre=Op->next;
            ListNode* cur=pre->next;
            for(int i=0; i<1; i++){
                ListNode* tmp=cur->next;
                cur->next=pre;
                pre=cur;
                cur=tmp;
            }

            ListNode* Oc=Op->next;
            Op->next=pre;
            Oc->next=cur;
            Op=Oc;
        }
        return vir->next;
    }
};

/*
25. K 个一组翻转链表
给你一个链表，每 k 个节点一组进行翻转，请你返回翻转后的链表。
k 是一个正整数，它的值小于或等于链表的长度。
如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。
示例：
给你这个链表：1->2->3->4->5
当 k = 2 时，应当返回: 2->1->4->3->5
当 k = 3 时，应当返回: 3->2->1->4->5
说明：
你的算法只能使用常数的额外空间。
你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。
*/
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* vir=new ListNode(-1);
        vir->next=head;
        ListNode* Op=vir;
        while(Op){
            ListNode* check=Op;
            for(int i=0; i<k; i++){
                if(!check->next) return vir->next;
                check=check->next;
            }

            ListNode* pre=Op->next;
            ListNode* cur=pre->next;
            for(int i=0; i<k-1; i++){
                ListNode* tmp=cur->next;
                cur->next=pre;
                pre=cur;
                cur=tmp;
            }

            ListNode* Oc=Op->next;
            Op->next=pre;
            Oc->next=cur;
            Op=Oc;
        }
        return vir->next;
    }
};

/*
92. 反转链表 II
反转从位置 m 到 n 的链表。请使用一趟扫描完成反转。
说明:
1 ≤ m ≤ n ≤ 链表长度。
示例:
输入: 1->2->3->4->5->NULL, m = 2, n = 4
输出: 1->4->3->2->5->NULL
*/
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode* vir=new ListNode(-1);
        vir->next=head;
        ListNode* Op=vir;
        for(int i=0; i<m-1; i++) Op=Op->next;

        ListNode* pre=Op->next;
        ListNode* cur=pre->next;
        for(int i=m; i< n; i++){
            ListNode* tmp=cur->next;
            cur->next=pre;
            pre=cur;
            cur=tmp;
        }

        ListNode* Oc=Op->next;
        Op->next=pre;
        Oc->next=cur;
        Op=Oc;
        return vir->next;
    }
};

/*
61. 旋转链表
给定一个链表，旋转链表，将链表每个节点向右移动 k 个位置，其中 k 是非负数。
示例 1:
输入: 1->2->3->4->5->NULL, k = 2
输出: 4->5->1->2->3->NULL
解释:
向右旋转 1 步: 5->1->2->3->4->NULL
向右旋转 2 步: 4->5->1->2->3->NULL
示例 2:
输入: 0->1->2->NULL, k = 4
输出: 2->0->1->NULL
解释:
向右旋转 1 步: 2->0->1->NULL
向右旋转 2 步: 1->2->0->NULL
向右旋转 3 步: 0->1->2->NULL
向右旋转 4 步: 2->0->1->NULL
*/
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head || !head->next) return head;
        ListNode* vir=new ListNode(-1);
        vir->next=head;
        ListNode* cur=vir;
        int cnt=0;
        while(cur->next){   //求链表长
            cnt+=1;
            cur=cur->next;
        }
        cur->next=head;   //原链表尾巴连接到头

        cur=head;
        for(int i=1; i<cnt-k%cnt; i++){   //找到前cnt-k%cnt链表长的尾巴，cur-head-i-1
            cur=cur->next;
        }

        ListNode* newhead=cur->next;
        cur->next=nullptr;
        return newhead;
    }
};


//////////////////////////////////////////////////////////////////////

/*
143. 重排链表
给定一个单链表 L：L0→L1→…→Ln-1→Ln ，
将其重新排列后变为： L0→Ln→L1→Ln-1→L2→Ln-2→…
你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
示例 1:
给定链表 1->2->3->4, 重新排列为 1->4->2->3.
示例 2:
给定链表 1->2->3->4->5, 重新排列为 1->5->2->4->3.
*/
class Solution {
public:
    void reorderList(ListNode* head) {
        ListNode* vir=new ListNode(-1);
        vir->next=head;
        ListNode* fast=vir;
        ListNode* slow=vir;
        while(fast && fast->next){
            slow=slow->next;
            fast=fast->next->next;
        }
        ListNode* left=head;
        ListNode* right=slow->next;
        slow->next=nullptr;
        ListNode* rightnew=reverse(right);
        while(left || rightnew){   //左右节点依次交替合并 先检查左 再检查右
            if(left){
                vir->next=left;
                left=left->next;
                vir=vir->next;
            }
            if(rightnew){
                vir->next=rightnew;
                rightnew=rightnew->next;
                vir=vir->next;
            }
        }
    }

    ListNode* reverse(ListNode* head){
        ListNode* pre=nullptr;
        ListNode* cur=head;
        while(cur){
            ListNode* tmp=cur->next;
            cur->next=pre;
            pre=cur;
            cur=tmp;
        }
        return pre;
    }
};






