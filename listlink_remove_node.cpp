
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
83. 删除排序链表中的重复元素
给定一个排序链表，删除所有重复的元素，使得每个元素只出现一次。
示例 1:
输入: 1->1->2
输出: 1->2
示例 2:
输入: 1->1->2->3->3
输出: 1->2->3
*/

    ListNode* deleteDuplicates(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode* fast=head->next;
        ListNode* slow=head;
        while(fast){
            if(fast->val == slow->val){
                slow->next=fast->next;
            } else {
                slow=slow->next;
            }
            fast=fast->next;
        }
        return head;
    }

/*
203. 移除链表元素
删除链表中等于给定值 val 的所有节点。
示例:
输入: 1->2->6->3->4->5->6, val = 6
输出: 1->2->3->4->5
*/

    ListNode* removeElements(ListNode* head, int val) {
        if(!head) return nullptr;
        ListNode* vir=new ListNode(-1);
        vir->next=head;
        ListNode* fast=head;
        ListNode* slow=vir;
        while(fast){
            if(fast->val == val){
                slow->next=fast->next;
            } else {
                slow=slow->next;
            }
            fast=fast->next;
        }
        return vir->next;
    }

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

	ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(!head || n==0) return nullptr;
        ListNode* vir=new ListNode(-1);
        vir->next=head;
        ListNode* fast=head;
        ListNode* slow=vir;
        for(int i=0; i<n; i++){
            fast=fast->next;
        }
        while(fast){
            slow=slow->next;
            fast=fast->next;
        }
        slow->next=slow->next->next;
        return vir->next;
    }

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

    ListNode* deleteDuplicates(ListNode* head) {
        if(!head|| !head->next) return head;

        ListNode *vir = new ListNode(-1);
        vir->next = head;

        ListNode *a = vir;
        ListNode *b = head;
        ListNode *c = head->next;

        while(c){
            while(c && c->val == b->val) c = c->next;    
            if(b->next == c){   //c和b的值不等
                c = c->next;
                b = b->next;
                a = a->next;
            }else{ 
                b = c;
                a->next = c;
                if(c) c = c->next;
            }
        }

        return vir->next;
    }