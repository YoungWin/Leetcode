
/*
author:young
链表：环形链表、排序
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
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(!head) return false;
        ListNode* vir=new ListNode(-1);
        vir->next=head;
        ListNode* pre=vir;
        ListNode* cur=vir;
        while(cur && cur->next){
            pre=pre->next;
            cur=cur->next->next;
            if(pre==cur) return true;
        }
        return false;
    }
};

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
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* vir=new ListNode(-1);
        vir->next=head;
        ListNode* cur=vir;   //
        ListNode* pre=vir;
        while(cur && cur->next){
            cur=cur->next->next;
            pre=pre->next;
            if(pre==cur){
                cur=vir;   //
                while(pre!=cur){
                    pre=pre->next;
                    cur=cur->next;
                }
                return pre;
            }
        }
        return nullptr;
    }
};

/*
剑指 Offer 22. 链表中倒数第k个节点
输入一个链表，输出该链表中倒数第k个节点。为了符合大多数人的习惯，本题从1开始计数，即链表的尾节点是倒数第1个节点。例如，一个链表有6个节点，从头节点开始，它们的值依次是1、2、3、4、5、6。这个链表的倒数第3个节点是值为4的节点。
示例：
给定一个链表: 1->2->3->4->5, 和 k = 2.
返回链表 4->5.
*/
class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        if(!head || k==0) return nullptr;
        ListNode* vir=new ListNode(-1);
        vir->next=head;
        ListNode* cur=head;
        ListNode* pre=vir;
        for(int i=0; i<k; i++) cur=cur->next;
        while(cur){
            cur=cur->next;
            pre=pre->next;
        }
        return pre->next;
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

//////////////////////////////////////////////////////////////////

/*
23. 合并K个排序链表
合并 k 个排序链表，返回合并后的排序链表。请分析和描述算法的复杂度。
示例:
输入:
[
  1->4->5,
  1->3->4,
  2->6
]
输出: 1->1->2->3->4->4->5->6
*/
class Solution {
public:
    //分治，两两合并
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int N = lists.size();
        if(N == 0) return nullptr;
        return merge(lists, 0, N - 1);
    }
    
    ListNode* merge(vector<ListNode*>& lists, int start, int end) {   //递归 链表两两分组
        if(start == end) return lists[start];
        int mid = (start + end) / 2;
        ListNode* l1 = merge(lists, start, mid);
        ListNode* l2 = merge(lists, mid + 1, end);

        ListNode* vir=new ListNode(-1);
        ListNode* cur=vir;
        while(l1 && l2){
            if(l1->val < l2->val){
                cur->next=l1;
                l1=l1?(l1->next):nullptr;
            } else {
                cur->next=l2;
                l2=l2?(l2->next):nullptr;
            }
            cur=cur->next;
        }  
        if(l1) cur->next=l1;
        if(l2) cur->next=l2;
        return vir->next; 
    }
};

/*
86. 分隔链表
给定一个链表和一个特定值 x，对链表进行分隔，使得所有小于 x 的节点都在大于或等于 x 的节点之前。
你应当保留两个分区中每个节点的初始相对位置。
示例:
输入: head = 1->4->3->2->5->2, x = 3
输出: 1->2->2->4->3->5
*/
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode* vp1=new ListNode(INT_MIN);   //小于x的虚拟头节点
        ListNode* vp2=new ListNode(INT_MIN);
        ListNode* cp1=vp1;
        ListNode* cp2=vp2;
        ListNode* cur=head;
        while(cur){
            if(cur->val < x){
                cp1->next=cur;
                cur=cur->next;
                cp1=cp1->next;
                cp1->next=nullptr;
            }else{
                cp2->next=cur;
                cur=cur->next;
                cp2=cp2->next;
                cp2->next=nullptr;
            }
        }
        cp1->next=vp2->next;
        return vp1->next;
    }
};

/*
148. 排序链表【归并排序】
在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序。
示例 1:
输入: 4->2->1->3
输出: 1->2->3->4
示例 2:
输入: -1->5->3->4->0
输出: -1->0->3->4->5
*/
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        ListNode* vir = new ListNode(INT_MIN);
        vir->next = head;
        ListNode* tmp = head;
        int N = 1;   //记录链表长
        while(tmp){
            tmp = tmp->next;
            N++;
        }
        
        for(int i = 1; i < N; i<<=1){   //1+1 2+2 4+4 8+8
            ListNode* pre= vir;   //pre记录合并完部分的链表尾
            ListNode* cur = vir->next;   //经过1+1排序后 原来位置的head结点 可能不再是vir->next指向的元素
            while(cur){
                ListNode* left = cur;
                ListNode* right = cut(left, i);
                cur = cut(right, i);
                
                pre->next = merge(left, right);
                while(pre->next) pre = pre->next;
            }
        }
        return vir->next;
    }
    
    ListNode* cut(ListNode* head, int n) {   //切掉链表前n个节点，并返回后半部分的链表头。
        ListNode* tmp = head;
        for(int i=1; i<n; i++){   //循环结束，tmp指向前n个节点的尾巴
            if(!tmp) return nullptr;
            else tmp = tmp->next;
        }
        if(!tmp) return nullptr;
        ListNode* res = tmp->next;
        tmp->next = nullptr;
        return res;
    }

    ListNode* merge(ListNode* first, ListNode* second) {   //双路归并
        ListNode* vir = new ListNode(INT_MIN);
        ListNode* cur = vir;   //tmp是排序合并完部分的链表尾
        while(first && second){
            if(first->val < second->val){
                cur->next = first;
                cur = first;
                first = first->next;
            } else {
                cur->next = second;
                cur = second;
                second = second->next;
            }
        }
        if(first) cur->next = first;
        else if(second) cur->next = second;
    
        return vir->next;
    }
};

/*
147. 对链表进行插入排序【less -> later】
对链表进行插入排序。
插入排序的动画演示如上。从第一个元素开始，该链表可以被认为已经部分排序（用黑色表示）。
每次迭代时，从输入数据中移除一个元素（用红色表示），并原地将其插入到已排好序的链表中。
插入排序算法：
插入排序是迭代的，每次只移动一个元素，直到所有元素可以形成一个有序的输出列表。
每次迭代中，插入排序只从输入数据中移除一个待排序的元素，找到它在序列中适当的位置，并将其插入。
重复直到所有输入数据插入完为止。
示例 1：
输入: 4->2->1->3
输出: 1->2->3->4
示例 2：
输入: -1->5->3->4->0
输出: -1->0->3->4->5
*/
class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        if(!head || !head->next) return head;   //如果链表 不包含结点 或者 只有一个结点
        ListNode* virthead = new ListNode(-1);   //构造虚拟头结点，virthead一直指向虚拟头结点
        virthead->next = head;
        
        ListNode* tail = head;   //tail指向 当前排好序的链表结尾
        ListNode* node = head->next;   //node指向 要插入的链表结点
        
        while(node){
            if(node->val < tail->val){   //如果node值 比 已排好序的链表尾巴值 大
                ListNode* cur = virthead;
                while(cur->next && node->val > cur->next->val){   //如果 cur的下一个节点值 仍比 node值 小，cur继续后移
                    cur = cur->next;
                }
                tail->next = node->next;
                node->next = cur->next;
                cur->next = node;
            } else {
                tail = node;   
            }
            node = tail->next;
        }
        
        ListNode* tmp = virthead->next;
        delete virthead;
        return tmp;
    }
};


































