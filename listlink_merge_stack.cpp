
/*
author:young
链表：合并链表、借助栈计算
*/

struct ListNode{
	int val;
	ListNode* next;
	ListNode(int x):val(x),next(nullptr){}
};


/*
160. 相交链表【双指针分别从两条链表头走，一条链表遍历完切换到另一条的链表头】
编写一个程序，找到两个单链表相交的起始节点。
*/
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(!headA || !headB) return nullptr;
        ListNode* curA=headA;
        ListNode* curB=headB;
        while(curA != curB){
            if(curA) curA=curA->next;
            else curA=headB;

            if(curB) curB=curB->next;
            else curB=headA;
        } 
        return curA;
    }
};

/*
2. 两数相加
给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。
如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。
您可以假设除了数字 0 之外，这两个数都不会以 0 开头。
示例：
输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 0 -> 8
原因：342 + 465 = 807
*/
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* vir=new ListNode(-1);
        ListNode* cur=vir;
        int car=0;
        while(l1 || l2 || car){
            int tmp=(l1?(l1->val):0) + (l2?(l2->val):0) + car;   //
            ListNode* node=new ListNode(tmp%10);
            car=tmp/10;
            cur->next=node;
            cur=node;
            l1=l1?l1->next:nullptr;   //
            l2=l2?l2->next:nullptr;
        }
        return vir->next;
    }
};

/*
21. 合并两个有序链表
将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 
示例：
输入：1->2->4, 1->3->4
输出：1->1->2->3->4->4
*/
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(!l1) return l2;   //
        if(!l2) return l1;
        ListNode* vir=new ListNode(-1);
        ListNode* cur=vir;
        while(l1&&l2){
            if(l1->val < l2->val){
                cur->next=l1;
                l1=l1?(l1->next):nullptr;   //
            } else {
                cur->next=l2;
                l2=l2?(l2->next):nullptr;
            }
            cur=cur->next;
        }
        if(l1) cur->next=l1;  //if
        if(l2) cur->next=l2;
        return vir->next;
    }
};

/*
445. 两数相加 II
给你两个 非空 链表来代表两个非负整数。数字最高位位于链表开始位置。它们的每个节点只存储一位数字。将这两数相加会返回一个新的链表。
你可以假设除了数字 0 之外，这两个数字都不会以零开头。
进阶：
如果输入链表不能修改该如何处理？换句话说，你不能对列表中的节点进行翻转。
示例：
输入：(7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 8 -> 0 -> 7
*/
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        stack<int> sl1;
        stack<int> sl2;
        ListNode* c1=l1;
        ListNode* c2=l2;
        while(c1){
            sl1.push(c1->val);
            c1=c1->next;
        }
        while(c2){
            sl2.push(c2->val);
            c2=c2->next;
        }

        int ss1=0, ss2=0, carry=0;
        ListNode* pre=nullptr;
        while(!sl1.empty() || !sl2.empty() || carry){
            if(!sl1.empty()){
                ss1=sl1.top();
                sl1.pop();
            }else{
                ss1=0;
            }
            if(!sl2.empty()){
                ss2=sl2.top();
                sl2.pop();
            }else{
                ss2=0;
            }
            int sum=ss1+ss2+carry;
            carry=sum/10;
            ListNode* cur=new ListNode(sum%10);
            cur->next=pre;
            pre=cur;   //pre用于记录 做好的后半部分链
        }
        return pre;
    }
};

/*
234. 回文链表
请判断一个链表是否为回文链表。
示例 1:
输入: 1->2
输出: false
示例 2:
输入: 1->2->2->1
输出: true
进阶：
你能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？
*/
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if(!head) return true;
        stack<int> st;
        ListNode* cur=head;
        while(cur){
            st.push(cur->val);
            cur=cur->next;
        }
        cur=head;
        while(cur){
            if(cur->val!=st.top()) return false;
            st.pop();
            cur=cur->next;
        }
        return true;
    }
};

/*
剑指 Offer 06. 从尾到头打印链表
输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）。
示例 1：
输入：head = [1,3,2]
输出：[2,3,1]
限制：
0 <= 链表长度 <= 10000
*/
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        vector<int> res;
        if(!head) return res;
        stack<int> st;
        ListNode* cur=head;
        while(cur){
            st.push(cur->val);
            cur=cur->next;
        }
        while(!st.empty()){
            res.push_back(st.top());
            st.pop();
        }
        return res;
    }
};




