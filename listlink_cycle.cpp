
/*
author:young
链表：环形链表
*/

struct ListNode{
	int val;
	ListNode* next;
	ListNode(int x):val(x),next(nullptr){}
};

/*
141. 环形链表
给定一个链表，判断链表中是否有环。
为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 pos 是 -1，则在该链表中没有环。
示例 1：
输入：head = [3,2,0,-4], pos = 1
输出：true
解释：链表中有一个环，其尾部连接到第二个节点2。
示例 2：
输入：head = [1,2], pos = 0
输出：true
解释：链表中有一个环，其尾部连接到第一个节点1。
示例 3：
输入：head = [1], pos = -1
输出：false
解释：链表中没有环。
进阶：
你能用 O(1)（即，常量）内存解决此问题吗？
*/

    bool hasCycle(ListNode *head) {
        if(!head) return false;;
        ListNode* fast=head;
        ListNode* slow=head;
        while(fast && fast->next){
            fast=fast->next->next;
            slow=slow->next;
            if(fast==slow) return true;
        }
        return false;
    }

/*
142. 环形链表 II
给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。
为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 pos 是 -1，则在该链表中没有环。
说明：不允许修改给定的链表。
示例 1：
输入：head = [3,2,0,-4], pos = 1
输出：tail connects to node index 1
解释：链表中有一个环，其尾部连接到第二个节点2。
示例 2：
输入：head = [1,2], pos = 0
输出：tail connects to node index 0
解释：链表中有一个环，其尾部连接到第一个节点1。
示例 3：
输入：head = [1], pos = -1
输出：no cycle
解释：链表中没有环。
进阶：
你是否可以不用额外空间解决此题？
*/

    ListNode *detectCycle(ListNode *head) {  
        if(!head) return nullptr;
        ListNode* fast=head;
        ListNode* slow=head;
        while(fast && fast->next){
            fast=fast->next->next;
            slow=slow->next;
            if(fast==slow){
                fast=head;
                while(fast!=slow){   //
                    fast=fast->next;
                    slow=slow->next;
                }
                return fast;
            }
        }
        return nullptr;

/*
剑指 Offer 22. 链表中倒数第k个节点
输入一个链表，输出该链表中倒数第k个节点。为了符合大多数人的习惯，本题从1开始计数，即链表的尾节点是倒数第1个节点。例如，一个链表有6个节点，从头节点开始，它们的值依次是1、2、3、4、5、6。这个链表的倒数第3个节点是值为4的节点。
示例：
给定一个链表: 1->2->3->4->5, 和 k = 2.
返回链表 4->5.
*/

    ListNode* getKthFromEnd(ListNode* head, int k) {
        if(!head || k==0) return nullptr;
        ListNode* fast=head;
        ListNode* slow=head;
        for(int i=0; i<k; i++){
            fast=fast->next;
        }
        while(fast){
            fast=fast->next;
            slow=slow->next;
        }
        return slow;
    }

/*
计算环长
*/
    int getLoopLength(ListNode* head){
	    ListNode* slow = head;
	    ListNode* fast = head;
	    while ( fast && fast->next ){
	        slow = slow->next;
	        fast = fast->next->next;
	        if ( slow == fast )//第一次相遇
	            break;
	    }
	    //slow与fast继续前进
	    slow = slow->next;
	    fast = fast->next->next;
	    int length = 1;       //环长度
	    while ( fast != slow )//再次相遇
	    {
	        slow = slow->next;
	        fast = fast->next->next;
	        length ++;        //累加
	    }
	    //当slow与fast再次相遇，得到环长度
    	return length;
	}

