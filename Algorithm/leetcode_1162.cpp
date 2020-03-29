/*
  你现在手里有一份大小为 N x N 的『地图』（网格） grid，上面的每个『区域』（单元格）都用 0 和 1 标记好了。
  其中 0 代表海洋，1 代表陆地，你知道距离陆地区域最远的海洋区域是是哪一个吗？请返回该海洋区域到离它最近的陆地区域的距离。
  我们这里说的距离是『曼哈顿距离』（ Manhattan Distance）：(x0, y0) 和 (x1, y1) 这两个区域之间的距离是 |x0 - x1| + |y0 - y1| 。
  如果我们的地图上只有陆地或者海洋，请返回 -1。

示例 1:

  输入：[[1,0,1],[0,0,0],[1,0,1]]
  输出：2 
  解释： 
  海洋区域 (1, 1) 和所有陆地区域之间的距离都达到最大，最大距离为 2。


解题思路：
  BFS
*/


class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        int dx[] = {1,0,-1,0};
        int dy[] = {0,1,0,-1};
        int rows = grid.size();
        int columns = grid[0].size();
        deque<pair<int,int>> deq;

        for(int i=0;i<rows;++i){
            for(int j=0;j<columns;++j){
                if(grid[i][j]==1){
                    deq.push_back( {i,j});
                }
            }
        }

        if(deq.size() ==0 || deq.size() == rows*columns){
            return -1;
        }

        int distance =-1;
        while(deq.size()!=0){
            distance++;
            int size = deq.size();
            while(size--){
                auto cur = deq.front();
                deq.pop_front();
                for(int i=0;i<4;++i){
                    int x = dx[i]+cur.first;
                    int y = dy[i]+cur.second;

                    if(x<0||x>=rows||y<0||y>=columns||grid[x][y]!=0){
                        continue;
                    }
                    grid[x][y]=2;
                    deq.push_back({x,y});
                }
            }
        }

        return distance;
    }
};
