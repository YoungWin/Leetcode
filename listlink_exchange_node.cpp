
/*
author:yuyang
链表：交换节点
*/

struct ListNode{
	int val;
	ListNode* next;
	ListNode(int x):val(x),next(nullptr){}
};


/*
24. 两两交换链表中的节点
给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。
你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
示例:
给定 1->2->3->4, 你应该返回 2->1->4->3.
*/

   ListNode* swapPairs(ListNode* head) {
        ListNode* vir = new ListNode(-1);
        vir->next = head;
        ListNode* Op = vir;
        while(Op){
            ListNode* check=Op;
            for(int i=0;i<2;i++){
                if(!check->next) return vir->next;
                check=check->next;
            }
            ListNode* pre=Op->next;
            ListNode* cur=pre->next;
            for(int i=0;i<1;i++){
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

/*
92. 反转链表 II
反转从位置 m 到 n 的链表。请使用一趟扫描完成反转。
说明:
1 ≤ m ≤ n ≤ 链表长度。
示例:
输入: 1->2->3->4->5->NULL, m = 2, n = 4
输出: 1->4->3->2->5->NULL
*/

    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode* pre = nullptr, *cur = head;
        ListNode* Op, *Oc;
        int cnt=1;
        while(cur && cnt<=n){
            if(cnt==m){
                Op=pre;
                Oc=cur;
            }
            if(cnt<=m){
                pre=cur;
                cur=cur->next;
            } else {
                ListNode* tmp = cur->next;
                cur->next = pre;
                pre=cur;
                cur=tmp;
            }
            cnt++;
        }
        if(!Op) head=pre;
        else Op->next=pre;
        Oc->next=cur;
        return head;
    }

/*
206. 反转链表
反转一个单链表。
示例:
输入: 1->2->3->4->5->NULL
输出: 5->4->3->2->1->NULL
进阶:
你可以迭代或递归地反转链表。你能否用两种方法解决这道题？
*/

    ListNode* reverseList(ListNode* head) {
       ListNode* pre = nullptr, *cur = head;
       while(cur){
           ListNode* tmp = cur->next;
           cur->next = pre;
           pre = cur;
           cur = tmp;
       }
       return pre;
    }

    