
/*
author:young
双指针
*/

//「双指针」，当枚举数组中的两个元素时，如果发现随着第一个元素的递增，第二个元素是递减的，则可以使用双指针的方法，将枚举的时间复杂度从 O(N^2) 减少至 O(N)。
//为什么是 O(N)呢？因为在枚举的过程每一步中，「左指针」会向右移动一个位置，而「右指针」会向左移动若干个位置，这个与数组的元素有关，但它一共会移动的位置数为 O(N)，均摊下来，每次也向左移动一个位置，因此时间复杂度为 O(N)。
//(1.)一个有序数组两端的双指针，控制求和变化趋势 167、15、16、18
//(2.)一个有序数组双指针【复制记录+for (快慢双指针)】，原地记录 26、27、80、283、75
//(3.)一个未排序数组数组快慢指针，找重复元素(数组转链表) 287
//(4.)两个有序数组双指针，合并 88
//(5.)容器盛水，双指针 缩减搜索范围 11、42
//(6.)字符串双指针


/*
15. 三数之和
给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？请你找出所有满足条件且不重复的三元组。
注意：答案中不可以包含重复的三元组。
示例：
给定数组 nums = [-1, 0, 1, 2, -1, -4]，
满足要求的三元组集合为：
[
  [-1, 0, 1],
  [-1, -1, 2]
]
*/
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        int N=nums.size();
        sort(nums.begin(), nums.end());
        if(N<3 || nums[0]>0 || nums[N-1]<0) return res;   //
        for(int i=0; i<N; i++){
            if(nums[i]>0) break;   //
            if(i>0 && nums[i-1]==nums[i]) continue;   //
            int left=i+1, right=N-1;
            while(left<right){
                int tmp=nums[i]+nums[left]+nums[right];
                if(tmp<0 || (left>i+1 && nums[left-1]==nums[left])) left++;   //
                else if(tmp>0 || (right<N-1 && nums[right+1]==nums[right])) right--;   //
                else{
                    res.push_back({nums[i], nums[left], nums[right]});  
                    left++;
                }
            }
        }
        return res;
    }
};

/*
16. 最接近的三数之和
给定一个包括 n 个整数的数组 nums 和 一个目标值 target。找出 nums 中的三个整数，使得它们的和与 target 最接近。返回这三个数的和。假定每组输入只存在唯一答案。
示例：
输入：nums = [-1,2,1,-4], target = 1
输出：2
解释：与 target 最接近的和是 2 (-1 + 2 + 1 = 2) 。
提示：
3 <= nums.length <= 10^3
-10^3 <= nums[i] <= 10^3
-10^4 <= target <= 10^4
*/
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int N=nums.size();
        if(N<3) return INT_MAX;
        sort(nums.begin(), nums.end());
        int res=nums[N-1]+nums[N-2]+nums[N-3];   //这里得是nums里真实存在的3个数
        
        for(int i=0; i<N; i++){
            if(i>0 && nums[i-1]==nums[i]) continue;
            int left=i+1, right=N-1;
            while(left<right){
                int tmp=nums[i]+nums[left]+nums[right];
                if(abs(tmp-target)<abs(res-target)) res=tmp;   //这里是绝对值度量，不一定满足res比tmp大
                if(tmp==target) return target;
                else if(tmp<target) left++;
                else right--;
            }
        }
        return res;
    }
};

/*
18. 四数之和
给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素 a，b，c 和 d ，使得 a + b + c + d 的值与 target 相等？找出所有满足条件且不重复的四元组。
注意：
答案中不可以包含重复的四元组。
示例：
给定数组 nums = [1, 0, -1, 0, -2, 2]，和 target = 0。
满足要求的四元组集合为：
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]
*/
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        int N=nums.size();
        if(N<4 || nums[0]>0 || nums[N-1]<0) return res;   //
        for(int a=0; a<N-3; a++){
            if(a>0 && nums[a-1]==nums[a]) continue;   //
            for(int b=a+1; b<N-2; b++){
                if(b>a+1 && nums[b-1]==nums[b]) continue;   //
                int left=b+1, right=N-1;
                while(left<right){
                    int tmp=nums[a]+nums[b]+nums[left]+nums[right];
                    if(tmp<target || (left>b+1 && nums[left-1]==nums[left])) left++;   //
                    else if(tmp>target || (right<N-1 && nums[right+1]==nums[right])) right--;   //
                    else{
                        res.push_back({nums[a],nums[b],nums[left],nums[right]});
                        left++;
                    }
                }
            }
        }
        return res;
    }
};

/*
167. 两数之和 II - 输入有序数组【注意数组有序，可以用双指针】
给定一个已按照升序排列 的有序数组，找到两个数使得它们相加之和等于目标数。
函数应该返回这两个下标值 index1 和 index2，其中 index1 必须小于 index2。
说明:
返回的下标值（index1 和 index2）不是从零开始的。
你可以假设每个输入只对应唯一的答案，而且你不可以重复使用相同的元素。
示例:
输入: numbers = [2, 7, 11, 15], target = 9
输出: [1,2]
解释: 2 与 7 之和等于目标数 9 。因此 index1 = 1, index2 = 2 
*/
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> res={-1,-1};
        int left=0, right=numbers.size()-1;
        while(left<right){
            int tmp=numbers[left]+numbers[right];
            if(tmp<target) left++;
            else if(tmp>target) right--;
            else{
                return {left+1, right+1};
            }
        }
        return res;
    }
};

////////////////////////////////////////////////////////////////////////////////////////

/*
26. 删除排序数组中的重复项【注意双指针的形式】
给定一个排序数组，你需要在 原地 删除重复出现的元素，使得每个元素只出现一次，返回移除后数组的新长度。
不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。
示例 1:
给定数组 nums = [1,1,2], 
函数应该返回新的长度 2, 并且原数组 nums 的前两个元素被修改为 1, 2。 
你不需要考虑数组中超出新长度后面的元素。
示例 2:
给定 nums = [0,0,1,1,1,2,2,3,3,4],
函数应该返回新的长度 5, 并且原数组 nums 的前五个元素被修改为 0, 1, 2, 3, 4。
你不需要考虑数组中超出新长度后面的元素。
说明:
为什么返回数值是整数，但输出的答案是数组呢?
请注意，输入数组是以「引用」方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。
你可以想象内部操作如下:
// nums 是以“引用”方式传递的。也就是说，不对实参做任何拷贝
int len = removeDuplicates(nums);
// 在函数里修改输入数组对于调用者是可见的。
// 根据你的函数返回的长度, 它会打印出数组中该长度范围内的所有元素。
for (int i = 0; i < len; i++) {
    print(nums[i]);
}
*/
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int lastnodup=1, N=nums.size();   //
        if(N==0) return 0;
        for(int i=1; i<N; i++){   //
            if(nums[i-1]!=nums[i]){
                nums[lastnodup]=nums[i];
                lastnodup++;
            }
        }
        return lastnodup;
    }
};
////////////////////////[注意对比双指针形式]
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int N=nums.size();
        if(N<2) return N;
        int i=0, j=1;
        while(j<N){
            if(nums[i]==nums[j]) j++;
            else{
                i++;
                nums[i]=nums[j];
                j++;
            }
        }
        return i+1;
    }
};

/*
27. 移除元素
给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。
不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。
元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。
示例 1:
给定 nums = [3,2,2,3], val = 3,
函数应该返回新的长度 2, 并且 nums 中的前两个元素均为 2。
你不需要考虑数组中超出新长度后面的元素。
示例 2:
给定 nums = [0,1,2,2,3,0,4,2], val = 2,
函数应该返回新的长度 5, 并且 nums 中的前五个元素为 0, 1, 3, 0, 4。
注意这五个元素可为任意顺序。
你不需要考虑数组中超出新长度后面的元素。
说明:
为什么返回数值是整数，但输出的答案是数组呢?
请注意，输入数组是以「引用」方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。
你可以想象内部操作如下:
// nums 是以“引用”方式传递的。也就是说，不对实参作任何拷贝
int len = removeElement(nums, val);
// 在函数里修改输入数组对于调用者是可见的。
// 根据你的函数返回的长度, 它会打印出数组中 该长度范围内 的所有元素。
for (int i = 0; i < len; i++) {
    print(nums[i]);
}
*/
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int lastnoval=0, N=nums.size();   //
        for(int i=0; i<N; i++){   //
            if(nums[i]!=val){
                nums[lastnoval]=nums[i];
                lastnoval++;
            } 
        }
        return lastnoval;
    }
};

/*
80. 删除排序数组中的重复项 II
给定一个排序数组，你需要在原地删除重复出现的元素，使得每个元素最多出现两次，返回移除后数组的新长度。
不要使用额外的数组空间，你必须在原地修改输入数组并在使用 O(1) 额外空间的条件下完成。
示例 1:
给定 nums = [1,1,1,2,2,3],
函数应返回新长度 length = 5, 并且原数组的前五个元素被修改为 1, 1, 2, 2, 3 。
你不需要考虑数组中超出新长度后面的元素。
示例 2:
给定 nums = [0,0,1,1,1,1,2,3,3],
函数应返回新长度 length = 7, 并且原数组的前五个元素被修改为 0, 0, 1, 1, 2, 3, 3 。
你不需要考虑数组中超出新长度后面的元素。
说明:
为什么返回数值是整数，但输出的答案是数组呢?
请注意，输入数组是以“引用”方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。
你可以想象内部操作如下:
// nums 是以“引用”方式传递的。也就是说，不对实参做任何拷贝
int len = removeDuplicates(nums);
// 在函数里修改输入数组对于调用者是可见的。
// 根据你的函数返回的长度, 它会打印出数组中该长度范围内的所有元素。
for (int i = 0; i < len; i++) {
    print(nums[i]);
}
*/
class Solution{
public:
    int removeDuplicates(vector<int>& nums){
        int lasttwodup=1, count=1, N=nums.size();
        if(N==0) return 0;
        for(int i=1; i<N; i++){
            if(nums[i]==nums[i-1]) count+=1;
            else count=1;

            if(count<=2){
                nums[lasttwodup]=nums[i];
                lasttwodup++;
            }
        }
        return lasttwodup;
    }
};

/*
283. 移动零
给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
示例:
输入: [0,1,0,3,12]
输出: [1,3,12,0,0]
说明:
必须在原数组上操作，不能拷贝额外的数组。
尽量减少操作次数。
*/
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int lastnozero=0, N=nums.size();  //
        for(int i=0; i<N; i++){   //
            if(nums[i]!=0){
                nums[lastnozero]=nums[i];
                lastnozero++;
            }
        }
        for(int i=lastnozero; i<N; i++){
            nums[i]=0;
        }
    }
};

/*
75. 颜色分类
给定一个包含红色、白色和蓝色，一共 n 个元素的数组，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。
注意:
不能使用代码库中的排序函数来解决这道题。
示例:
输入: [2,0,2,1,1,0]
输出: [0,0,1,1,2,2]
进阶：
一个直观的解决方案是使用计数排序的两趟扫描算法。
首先，迭代计算出0、1 和 2 元素的个数，然后按照0、1、2的排序，重写当前数组。
你能想出一个仅使用常数空间的一趟扫描算法吗？
*/
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int p0=0, cur=0, p2=nums.size()-1;
        while(cur<=p2){
            if(nums[cur]==0) swap(nums[p0++],nums[cur++]);
            else if(nums[cur]==2) swap(nums[p2--],nums[cur]);
            else cur++;
        }
    }
};

////////////////////////////////////////////////////////////////////////////////////////

/*
287. 寻找重复数【思路比较trick 数组转化成链表理解】
给定一个包含 n + 1 个整数的数组 nums，其数字都在 1 到 n 之间（包括 1 和 n），可知至少存在一个重复的整数。假设只有一个重复的整数，找出这个重复的数。
示例 1:
输入: [1,3,4,2,2]
输出: 2
示例 2:
输入: [3,1,3,4,2]
输出: 3
说明：
不能更改原数组（假设数组是只读的）。
只能使用额外的 O(1) 的空间。
时间复杂度小于 O(n2) 。
数组中只有一个重复的数字，但它可能不止重复出现一次。
*/
class Solution {
public:
    //并不知道这个数 重复几遍
    //判断环：值表示当前节点(index节点)的next指针，值重复就表示 存在不止一个节点的next指针 指向这个重复值对应的index节点
    int findDuplicate(vector<int>& nums) {
        int slow=0, fast=0, N=nums.size();
        while(fast<N && nums[fast]<N){
            slow=nums[slow];
            fast=nums[nums[fast]];
            if(slow==fast){
                fast=0;
                while(slow!=fast){
                    slow=nums[slow];
                    fast=nums[fast];
                }
                return slow;
            }
        }
        return -1;
    }
};

////////////////////////////////////////////////////////////////////////////////////////

/*
88. 合并两个有序数组
给你两个有序整数数组 nums1 和 nums2，请你将 nums2 合并到 nums1 中，使 nums1 成为一个有序数组。
说明:
初始化 nums1 和 nums2 的元素数量分别为 m 和 n 。
你可以假设 nums1 有足够的空间（空间大小大于或等于 m + n）来保存 nums2 中的元素。
示例:
输入:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3
输出: [1,2,2,3,5,6]
*/
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i=m-1, j=n-1;
        int N=nums1.size(), cur=N-1;
        while(i>=0 && j>=0){
            if(nums1[i]<nums2[j]){
                nums1[cur--]=nums2[j--];
            }else{
                nums1[cur--]=nums1[i--];
            }
        }
        while(i>=0){
            nums1[cur--]=nums1[i--];
        }
        while(j>=0){
            nums1[cur--]=nums2[j--];
        }
    }
};

////////////////////////////////////////////////////////////////////////////////////////

/*
11. 盛最多水的容器
给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0)。找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
说明：你不能倾斜容器，且 n 的值至少为 2。
示例：
输入：[1,8,6,2,5,4,8,3,7]
输出：49
*/
class Solution {
public:
    int maxArea(vector<int>& height) {
        int N=height.size();
        if(N<2) return 0;
        int i=0, j=N-1, res=0;
        while(i<j){
            if(height[i]<height[j]){
                res=max(res, height[i]*(j-i));
                i++;   //再收缩，较低一侧无法获得更大面积
            }else{
                res=max(res, height[j]*(j-i));
                j--;
            }
        }
        return res;
    }
};

/*
42. 接雨水
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
示例:
输入: [0,1,0,2,1,0,1,3,2,1,2,1]
输出: 6
*/
class Solution {
public:
    int trap(vector<int>& height){
        int N=height.size();
        if(N==0) return 0;
        int i=0, j=N-1, res=0;
        int left=height[0], right=height[N-1];
        while(i<j){
            left=max(left, height[i]);   //边界挡板高度
            right=max(right, height[j]);
            if(left<right){   //右侧有较高的挡板，当前位置i低洼可积水
                res+=left-height[i];
                i++;
            }else{
                res+=right-height[j];
                j--;
            }
        }
        return res;
    }
};







