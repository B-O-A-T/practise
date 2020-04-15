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

思路：BFS，超级源点，从为零的点开始

在过程中学到了emplace()的用法，这是C++11中加入的新特性，
emplace_back能通过参数构造对象，不需要拷贝或者移动内存，
相比push_back能更好地避免内存的拷贝与移动，使容器插入元素的性能得到进一步提升
```
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int rows =matrix.size();
        int columns = matrix[0].size();

        queue<pair<int, int>> q;

        for(int i=0;i<rows;++i){
            for(int j=0;j<columns;++j){
                if(matrix[i][j]==0){
                    q.emplace(i,j);
                } else {
                    matrix[i][j]=-1;
                }
            }
        }

        int dx[]={0,1,0,-1};
        int dy[]={1,0,-1,0};
        while (!q.empty()) {
            auto [i,j] = q.front();
            q.pop();
            for(int k = 0;k<4;++k){
                int x = i+ dx[k];
                int y = j + dy[k];
                if(x>=0&&x<rows&&y>=0&&y<columns&&matrix[x][y]==-1){
                    matrix[x][y] = matrix[i][j]+1;
                    q.emplace(x,y);
                }
            }
        }
        return matrix;
    }
};
```
