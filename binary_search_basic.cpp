/*
author:young
二分查找basic题
*/

/* 
一个比较方便的模板
int start = 0, end = nums.length - 1;
while (start + 1 < end) {   //针对[2,2]紧邻最后两个条件做的限制
    int mid = start + (end - start) / 2;

    if (...) {
        start = mid;
    } else {
        end = mid;
    }
}
*/


/*
74. 搜索二维矩阵
编写一个高效的算法来判断 m x n 矩阵中，是否存在一个目标值。该矩阵具有如下特性：
每行中的整数从左到右按升序排列。
每行的第一个整数大于前一行的最后一个整数。
示例 1:
输入:
matrix = [
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
target = 3
输出: true
示例 2:
输入:
matrix = [
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
target = 13
输出: false
*/

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty()) return false;
        int row = matrix.size(), col = matrix[0].size();
        if(row==0 || col==0) return false;
        int less = min(row, col);
        for(int i=0; i<less; i++){
            bool rf=find(matrix,i,target,true);
            bool cf=find(matrix,i,target,false);
            if(rf||cf) return true;
        }
        return false;
    }
    bool find(vector<vector<int>>& matrix, int i, int target, bool isrow){
        if(matrix.empty()) return false;
        int row = matrix.size(), col = matrix[0].size();
        int left = i, right = 0;
        if(isrow) right = col-1;   //搜索每一行
        else right = row-1;

        while(left+1 < right){
            int mid = left+(right-left)/2;
            if(isrow){
                if(matrix[i][mid]==target) return true;
                else if(matrix[i][mid]<target) left=mid;
                else right=mid;
            } else {
                if(matrix[mid][i]==target) return true;
                else if(matrix[mid][i]<target) left=mid;
                else right=mid;
            }
        }

        if(isrow){
            if(matrix[i][right]==target || matrix[i][left]==target) return true;
        } else {
            if(matrix[right][i]==target || matrix[left][i]==target) return true;
        }
        return false;
    }  
};


/*
240. 搜索二维矩阵 II
编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target。该矩阵具有以下特性：
每行的元素从左到右升序排列。
每列的元素从上到下升序排列。
示例:
现有矩阵 matrix 如下：
[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
给定 target = 5，返回 true。
给定 target = 20，返回 false。
*/
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty()) return false;
        int row=matrix.size(), col=matrix[0].size();
        int i=0, j=col-1;
        while(i<=row-1 && j>=0){
            if(matrix[i][j]==target) return true;
            else if(matrix[i][j]<target) i++;
            else j--;
        }
        return false;
    }
};


/*
668. 乘法表中第k小的数
几乎每一个人都用 乘法表。但是你能在乘法表中快速找到第k小的数字吗？
给定高度m 、宽度n 的一张 m * n的乘法表，以及正整数k，你需要返回表中第k 小的数字。
例 1：
输入: m = 3, n = 3, k = 5
输出: 3
解释: 
乘法表:
1	2	3
2	4	6
3	6	9
第5小的数字是 3 (1, 2, 2, 3, 3).
例 2：
输入: m = 2, n = 3, k = 6
输出: 6
解释: 
乘法表:
1	2	3
2	4	6
第6小的数字是 6 (1, 2, 2, 3, 4, 6).
注意：
m 和 n 的范围在 [1, 30000] 之间。
k 的范围在 [1, m * n] 之间。
*/

class Solution {
public:
    int findKthNumber(int m, int n, int k) {
        int left=1,right=m*n;
        while(left+1<right){
            int mid = left+(right-left)/2;
            if(find(mid,m,n,k)) right=mid;
            else left=mid;
        }
        if(find(left,m,n,k)) return left;
        return right;
    }

    bool find(int mid, int m, int n, int k){
        int row=1;
        int cnt=0;
        while(row<=m){
            if(mid/row==0) break;
            cnt+=min(n,mid/row);
            row++;
        }
        return cnt>=k;
    }
};

///////////////////////////////////////////////////////////////////////////////

/*
34. 在排序数组中查找元素的第一个和最后一个位置
给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。
你的算法时间复杂度必须是 O(log n) 级别。
如果数组中不存在目标值，返回 [-1, -1]。
示例 1:
输入: nums = [5,7,7,8,8,10], target = 8
输出: [3,4]
示例 2:
输入: nums = [5,7,7,8,8,10], target = 6
输出: [-1,-1]
*/

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res={-1,-1};
        if(nums.size()==0) return res;
        int left=0,right=nums.size()-1;
        while(left+1<right){
            int mid = left+(right-left)/2;
            if(nums[mid]<target) left=mid;
            else right=mid;
        }
        if(nums[left]==target) res[0]=left;
        else if(nums[right]==target) res[0]=right;

        left=0,right=nums.size()-1;
        while(left+1<right){
            int mid = left+(right-left)/2;
            if(nums[mid]>target) right=mid;
            else left=mid;
        }
        if(nums[right]==target) res[1]=right;
        else if(nums[left]==target) res[1]=left;

        return res;
    }
};

/*
35. 搜索插入位置
给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
你可以假设数组中无重复元素。
示例 1:
输入: [1,3,5,6], 5
输出: 2
示例 2:
输入: [1,3,5,6], 2
输出: 1
示例 3:
输入: [1,3,5,6], 7
输出: 4
示例 4:
输入: [1,3,5,6], 0
输出: 0
*/

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        if(nums.size()==0) return 0;
        int left = 0, right = nums.size()-1;
        while(left+1 < right){
            int mid = left+(right-left)/2;
            if(nums[mid]==target) return mid;
            else if(nums[mid]<target) left=mid;
            else right=mid;
        }
        if(target <= nums[left]) return left;
        else if(target > nums[left] && target <= nums[right]) return left+1;
        else return right+1;
    }
};


/*
278. 第一个错误的版本
你是产品经理，目前正在带领一个团队开发新的产品。不幸的是，你的产品的最新版本没有通过质量检测。由于每个版本都是基于之前的版本开发的，所以错误的版本之后的所有版本都是错的。
假设你有 n 个版本 [1, 2, ..., n]，你想找出导致之后所有版本出错的第一个错误的版本。
你可以通过调用 bool isBadVersion(version) 接口来判断版本号 version 是否在单元测试中出错。实现一个函数来查找第一个错误的版本。你应该尽量减少对调用 API 的次数。
示例:
给定 n = 5，并且 version = 4 是第一个错误的版本。
调用 isBadVersion(3) -> false
调用 isBadVersion(5) -> true
调用 isBadVersion(4) -> true
所以，4 是第一个错误的版本。
*/

class Solution {
public:
    int firstBadVersion(int n) {
        int left = 1, right = n;
        while(left+1 < right){
            int mid = left + (right - left) / 2;
            if(isBadVersion(mid)) right = mid;
            else left = mid;
        }
        if(isBadVersion(left)) return left;
        return right;
    }
};

///////////////////////////////////////////////////////////////////////////////

/*
33. 搜索旋转排序数组
假设按照升序排序的数组在预先未知的某个点上进行了旋转。
( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。
搜索一个给定的目标值，如果数组中存在这个目标值，则返回它的索引，否则返回 -1 。
你可以假设数组中不存在重复的元素。
你的算法时间复杂度必须是 O(log n) 级别。
示例 1:
输入: nums = [4,5,6,7,0,1,2], target = 0
输出: 4
示例 2:
输入: nums = [4,5,6,7,0,1,2], target = 3
输出: -1
*/

class Solution {
public:
    int search(vector<int>& nums, int target) {
        if(nums.empty() || nums.size()==0) return -1;
        int left=0,right=nums.size()-1;
        while(left+1<right){
            int mid = left+(right-left)/2;
            if(nums[right]==target) return right;
            if(target<nums[right]){
                if(nums[mid]>nums[right] || nums[mid]<target){
                    left=mid;
                } else {
                    right=mid;
                }
            } else {
                if(nums[mid]<nums[right] || nums[mid]>target){
                    right=mid;
                } else {
                    left=mid;
                }
            }
        }
        if(nums[left]==target) return left;
        else if(nums[right]==target) return right;
        else return -1;
    }
};

/*
153. 寻找旋转排序数组中的最小值
假设按照升序排序的数组在预先未知的某个点上进行了旋转。
( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。
请找出其中最小的元素。
你可以假设数组中不存在重复元素。
示例 1:
输入: [3,4,5,1,2]
输出: 1
示例 2:
输入: [4,5,6,7,0,1,2]
输出: 0
*/

class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size()-1;
        while(left+1<right){
            int mid = left+(right-left)/2;
            if(nums[mid]>=nums[right]) left=mid;
            else right=mid;
        }
        if(nums[left]<nums[right]) return nums[left];
        return nums[right];
    }
};

/*
154. 寻找旋转排序数组中的最小值 II
假设按照升序排序的数组在预先未知的某个点上进行了旋转。
( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。
请找出其中最小的元素。
注意数组中可能存在重复的元素。
示例 1：
输入: [1,3,5]
输出: 1
示例 2：
输入: [2,2,2,0,1]
输出: 0
说明：
这道题是 寻找旋转排序数组中的最小值 的延伸题目。
允许重复会影响算法的时间复杂度吗？会如何影响，为什么？
*/

class Solution {
public:
    int findMin(vector<int>& nums) {
        if(nums.empty() || nums.size()==0) return -1;
        int left=0,right=nums.size()-1;
        while(left+1<right){
            int mid = left+(right-left)/2;
            if(nums[right]<nums[mid]) left=mid;
            else if(nums[right]>nums[mid]) right=mid;
            else{
                int tmp=mid;
                while(tmp<right && nums[tmp]==nums[right]){
                    tmp++;
                }
                if(nums[tmp]==nums[right]) right=mid;
                else if(tmp<right) left=mid;
            }
        }
        if(nums[left]<nums[right]) return nums[left];
        return nums[right];
    }
};

///////////////////////////////////////////////////////////////////////////////

/*
69. x 的平方根
实现 int sqrt(int x) 函数。
计算并返回 x 的平方根，其中 x 是非负整数。
由于返回类型是整数，结果只保留整数的部分，小数部分将被舍去。
示例 1:
输入: 4
输出: 2
示例 2:
输入: 8
输出: 2
说明: 8 的平方根是 2.82842..., 
     由于返回类型是整数，小数部分将被舍去。
*/

class Solution {
public:
    int mySqrt(int x) {
        if(x<=1) return x;
        int left=1,right=x-1;
        while(left+1<right){
            int mid=left+(right-left)/2;
            if(mid==x/mid) return mid;
            else if(mid<x/mid) left=mid;
            else right=mid;
        }
        if(right<x/right) return right;
        return left;
    }
};

/*
牛顿法求一个实数的平方根
X_n+1 =(X_n + 1/X_n) / 2
*/

double findsqrt(double K){
	if(K==0 | K==1) return K;
	double tmp = K / 2;
	while(true){
		double pre = tmp;
		tmp = (tmp + 1/tmp) / 2;
		if(fabs(pre - tmp) < 0.005) return tmp;
	}
}


