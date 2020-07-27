
/*
author:young
BFS:(1)树的BFS (2)图的BFS，以二维数组形式表达
*/

//Tree只有一个root，而图可以有多个源点，所以首先需要把多个源点都入队；
//Tree是有向的，因此不需要标识是否访问过，而对于无向图来说，必须得标志是否访问过！并且为了防止某个节点多次入队，需要在其入队之前 就将其设置成已访问！

//*******************
//最简单版——树的BFS：101[每层判断回文]、102、103、107、111、199、513、515
//***分析时空复杂度***
//*******************


/*
200. 岛屿数量
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
岛屿总是被水包围，并且每座岛屿只能由水平方向或竖直方向上相邻的陆地连接形成。
此外，你可以假设该网格的四条边均被水包围。
示例 1:
输入:
11110
11010
11000
00000
输出: 1
示例 2:
输入:
11000
11000
00100
00011
输出: 3
解释: 每座岛屿只能由水平和/或竖直方向上相邻的陆地连接而成。
*/

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty()) return 0;
        int m=grid.size(), n=grid[0].size();
        int cnt=0;
        queue<pair<int,int>> qu;
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                if(grid[i][j]=='1'){
                    qu.push({i,j});
                    grid[i][j]='0';
                    cnt+=1;

                    while(!qu.empty()){
                        auto ft=qu.front();
                        qu.pop();
                        int row=ft.first, col=ft.second;
                        if(row-1>=0 && grid[row-1][col]=='1'){
                            grid[row-1][col]='0';
                            qu.push({row-1,col});
                        }
                        if(row+1<=m-1 && grid[row+1][col]=='1'){
                            grid[row+1][col]='0';
                            qu.push({row+1,col});
                        }
                        if(col-1>=0 && grid[row][col-1]=='1'){
                            grid[row][col-1]='0';
                            qu.push({row,col-1});
                        }
                        if(col+1<=n-1 && grid[row][col+1]=='1'){
                            grid[row][col+1]='0';
                            qu.push({row,col+1});
                        }
                    }
                }

            }
        }
        return cnt;
    }
};

/*
207. 课程表
你这个学期必须选修 numCourse 门课程，记为 0 到 numCourse-1 。
在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们：[0,1]
给定课程总量以及它们的先决条件，请你判断是否可能完成所有课程的学习？
示例 1:
输入: 2, [[1,0]] 
输出: true
解释: 总共有 2 门课程。学习课程 1 之前，你需要完成课程 0。所以这是可能的。
示例 2:
输入: 2, [[1,0],[0,1]]
输出: false
解释: 总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0；并且学习课程 0 之前，你还应先完成课程 1。这是不可能的。
 提示：
输入的先决条件是由 边缘列表 表示的图形，而不是 邻接矩阵 。详情请参见图的表示法。
你可以假定输入的先决条件中没有重复的边。
1 <= numCourses <= 10^5
*/
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> dep(numCourses, 0);
        vector<vector<int>> graph(numCourses, vector<int>());
        for(auto i:prerequisites){
            dep[i[0]]++;
            graph[i[1]].push_back(i[0]);
        }
        queue<int> qu;
        for(int i=0; i<numCourses; i++){
            if(dep[i]==0) qu.push(i);
        }

        int finish=0;
        while(!qu.empty()){
            int ft=qu.front();
            qu.pop();
            finish+=1;

            for(auto i:graph[ft]){   //学完ft 可以学的课
                dep[i]--;
                if(dep[i]==0) qu.push(i);
            }
        }

        if(finish==numCourses) return true;
        return false;
    }
};

/*
210. 课程表 II
现在你总共有 n 门课需要选，记为 0 到 n-1。
在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们: [0,1]
给定课程总量以及它们的先决条件，返回你为了学完所有课程所安排的学习顺序。
可能会有多个正确的顺序，你只要返回一种就可以了。如果不可能完成所有课程，返回一个空数组。
示例 1:
输入: 2, [[1,0]] 
输出: [0,1]
解释: 总共有 2 门课程。要学习课程 1，你需要先完成课程 0。因此，正确的课程顺序为 [0,1] 。
示例 2:
输入: 4, [[1,0],[2,0],[3,1],[3,2]]
输出: [0,1,2,3] or [0,2,1,3]
解释: 总共有 4 门课程。要学习课程 3，你应该先完成课程 1 和课程 2。并且课程 1 和课程 2 都应该排在课程 0 之后。
     因此，一个正确的课程顺序是 [0,1,2,3] 。另一个正确的排序是 [0,2,1,3] 。
说明:
输入的先决条件是由边缘列表表示的图形，而不是邻接矩阵。详情请参见图的表示法。
你可以假定输入的先决条件中没有重复的边。
提示:
这个问题相当于查找一个循环是否存在于有向图中。如果存在循环，则不存在拓扑排序，因此不可能选取所有课程进行学习。
通过 DFS 进行拓扑排序 - 一个关于Coursera的精彩视频教程（21分钟），介绍拓扑排序的基本概念。
拓扑排序也可以通过 BFS 完成。
*/

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> inDegree(numCourses, 0);
        vector<vector<int>> neighbor(numCourses, vector<int>());
        for(auto i : prerequisites){
            inDegree[i[0]]++;
            neighbor[i[1]].push_back(i[0]);   //要想学课程i[0]，先学课程i[1]
        }
        queue<int> qu;
        for(int i = 0; i < inDegree.size(); i++){
            if(inDegree[i] == 0) qu.push(i);
        }

        vector<int> dealed;
        while(!qu.empty()){
            int tmp = qu.front();
            qu.pop();
            dealed.push_back(tmp);
            for(auto i : neighbor[tmp]){
                inDegree[i]--;
                if(inDegree[i] == 0) qu.push(i);
            }
        }

        if(dealed.size() == numCourses) return dealed;
        else return vector<int>();
    }
};

/*
542. 01 矩阵
给定一个由 0 和 1 组成的矩阵，找出每个元素到最近的 0 的距离。
两个相邻元素间的距离为 1 。
示例 1:
输入:
0 0 0
0 1 0
0 0 0
输出:
0 0 0
0 1 0
0 0 0
示例 2:
输入:
0 0 0
0 1 0
1 1 1
输出:
0 0 0
0 1 0
1 2 1
注意:
给定矩阵的元素个数不超过 10000。
给定矩阵中至少有一个元素是 0。
矩阵中的元素只在四个方向上相邻: 上、下、左、右。
*/

//多源BFS，从矩阵里的所有0向外搜索
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> dist(m, vector<int>(n));
        vector<vector<int>> visit(m, vector<int>(n));
        vector<pair<int,int>> around = {{0,1},{0,-1},{-1,0},{1,0}};
        queue<pair<int, int>> qu;
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == 0) {   // 将所有的0 添加进初始队列中
                    qu.push(pair<int,int>(i, j));
                    visit[i][j] = -1;   // 标记位置(i,j)被访问过
                }
            }
        }

        // 广度优先搜索
        while (!qu.empty()) {
            auto tmp = qu.front();
            qu.pop();
            int i = tmp.first;
            int j = tmp.second;
            for (int d = 0; d < 4; ++d) {   // 周围4个方向的点
                int ni = i + around[d].first;
                int nj = j + around[d].second;
                if (ni >= 0 && ni < m && nj >= 0 && nj < n && !visit[ni][nj]) {
                    dist[ni][nj] = dist[i][j] + 1;   //此时 再没被访问visit的点，都是非0
                    qu.push(pair<int,int>(ni, nj));   //入队 为了后续考查更内层的1
                    visit[ni][nj] = -1;
                }
            }
        }

    return dist;
    }
};

/*
407. 接雨水 II
给你一个 m x n 的矩阵，其中的值均为非负整数，代表二维高度图每个单元的高度，请计算图中形状最多能接多少体积的雨水。
示例：
给出如下 3x6 的高度图:
[
  [1,4,3,1,3,2],
  [3,2,1,3,2,4],
  [2,3,3,2,3,1]
]
返回 4 。
*/

//一个比较好的讲解视频 https://www.youtube.com/watch?v=7GH-x3Dn-4o
class Solution {
public:
    vector<pair<int,int>> around = {{0,1},{0,-1},{-1,0},{1,0}};
    struct Cmp {
        bool operator() (const vector<int>& v1, const vector<int>& v2) const {
            return v1[2] > v2[2];
        }
    };
    int trapRainWater(vector<vector<int>>& heightMap) {
        if (heightMap.empty()) return 0;
        int R = heightMap.size();
        int C = heightMap[0].size();
        if (R < 3 || C < 3) return 0;
        priority_queue<vector<int>, vector<vector<int> >, Cmp> pq;
        for (int i = 0; i < R; ++i) {
            pq.push({i, 0, heightMap[i][0]});
            pq.push({i, C - 1, heightMap[i][C - 1]});
            heightMap[i][0] = heightMap[i][C - 1] = -1;
        }
        for (int j = 1; j < C - 1; ++j) {
            pq.push({0, j, heightMap[0][j]});
            pq.push({R - 1, j, heightMap[R - 1][j]});
            heightMap[0][j] = heightMap[R - 1][j] = -1;
        }
        int res = 0;
        int vis_max = INT_MIN;   //出队的所有元素里的max[当前队列里每个元素都比vis_max大-小顶堆]
        while (!pq.empty()) {
            auto t = pq.top();   //pq里值最小的元素
            pq.pop();
            int t0 = t[0], t1 = t[1], t2 = t[2];
            res += (vis_max > t2) ? (vis_max - t2) : 0;
            vis_max = max(vis_max, t2);

            for (int i = 0; i < 4; ++i) {
                int r = t0 + around[i].first;
                int c = t1 + around[i].second;
                if (r >= 0 && r < R && c >= 0 && c < C && heightMap[r][c] != -1) {
                    pq.push({r, c, heightMap[r][c]});
                    heightMap[r][c] = -1;
                }
            }
        }
        return res;
    }
};

/*
42. 接雨水【此题和主题相关度不大】
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。 感谢 Marcos 贡献此图。
示例:
输入: [0,1,0,2,1,0,1,3,2,1,2,1]
输出: 6
*/

class Solution {
public:
    int trap(vector<int>& height){
        int Size=height.size();
        if(Size==0) return 0;
        int i=0,j=Size-1,res=0;
        int lmax=height[0],rmax=height[Size-1];
        while(i<=j){
            lmax=max(lmax,height[i]);
            rmax=max(rmax,height[j]);
            if(lmax<rmax){
                res+=lmax-height[i];   //当前考察位置i可容水量
                i++;
            } else {
                res+=rmax-height[j];
                j--;
            }
        }
        return res;
    }
};


