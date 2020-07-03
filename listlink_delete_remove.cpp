
/*
author:young
链表：删除节点
*/

struct ListNode{
	int val;
	ListNode* next;
	ListNode(int x):val(x),next(nullptr){}
};


/*
19. 删除链表的倒数第N个节点
给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。
示例：
给定一个链表: 1->2->3->4->5, 和 n = 2.
当删除了倒数第二个节点后，链表变为 1->2->3->5.
说明：
给定的 n 保证是有效的。
进阶：
你能尝试使用一趟扫描实现吗？
*/
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* vir=new ListNode(-1);
        vir->next=head;
        ListNode* fast=vir;
        ListNode* slow=vir;
        for(int i=0; i<n; i++) fast=fast->next;
        while(fast->next){
            fast=fast->next;
            slow=slow->next;
        }
        slow->next=slow->next->next;
        return vir->next;
    }
};


/*
203. 移除链表元素
删除链表中等于给定值 val 的所有节点。
示例:
输入: 1->2->6->3->4->5->6, val = 6
输出: 1->2->3->4->5
*/
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* vir=new ListNode(-1);
        vir->next=head;
        ListNode* cur=head;
        ListNode* pre=vir;
        while(cur){
            if(cur->val==val){
                pre->next=cur->next;
                cur=cur->next;
            }else{
                pre=pre->next;
                cur=cur->next;
            }
        }
        return vir->next;
    }
};

/*
83. 删除排序链表中的重复元素
给定一个排序链表，删除所有重复的元素，使得每个元素只出现一次。
示例 1:
输入: 1->1->2
输出: 1->2
示例 2:
输入: 1->1->2->3->3
输出: 1->2->3
*/
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* vir=new ListNode(INT_MIN);
        vir->next=head;
        ListNode* cur=head;
        ListNode* pre=vir;
        while(cur){
            if(cur->val==pre->val){
                pre->next=cur->next;
                cur=cur->next;
            }else{
                pre=pre->next;
                cur=cur->next;
            }
        }
        return vir->next;
    }
};

/*
82. 删除排序链表中的重复元素 II
给定一个排序链表，删除所有含有重复数字的节点，只保留原始链表中 没有重复出现 的数字。
示例 1:
输入: 1->2->3->3->4->4->5
输出: 1->2->5
示例 2:
输入: 1->1->1->2->3
输出: 2->3
*/
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode* vir=new ListNode(INT_MIN);
        vir->next=head;
        ListNode* pre=vir;
        ListNode* cur=head;
        ListNode* tmp=head->next;
        while(tmp){
            while(tmp && tmp->val==cur->val){
                tmp=tmp->next;
            }
            if(cur->next==tmp){
                pre=pre->next;
                cur=cur->next;
                tmp=tmp->next;
            }else{
                pre->next=tmp;
                cur=tmp;
                if(tmp) tmp=tmp->next;
            }
        }
        return vir->next;
    }
};

/*
237. 删除链表中的节点【后一个节点覆盖】
请编写一个函数，使其可以删除某个链表中给定的（非末尾）节点，你将 只被给定 要求被删除的节点。
示例 1:
输入: head = [4,5,1,9], node = 5
输出: [4,1,9]
解释: 给定你链表中值为 5 的第二个节点，那么在调用了你的函数之后，该链表应变为 4 -> 1 -> 9.
示例 2:
输入: head = [4,5,1,9], node = 1
输出: [4,5,9]
解释: 给定你链表中值为 1 的第三个节点，那么在调用了你的函数之后，该链表应变为 4 -> 5 -> 9.
说明:
链表至少包含两个节点。
链表中所有节点的值都是唯一的。
给定的节点为非末尾节点并且一定是链表中的一个有效节点。
不要从你的函数中返回任何结果。
*/

	void deleteNode(ListNode* node) {
        node->val=node->next->val;
        node->next=node->next->next;
    }

