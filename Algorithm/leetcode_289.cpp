/*
 * 给定一个包含 m × n 个格子的面板，每一个格子都可以看成是一个细胞。
 * 每个细胞都具有一个初始状态：1 即为活细胞（live），或 0 即为死细胞（dead）。
 * 每个细胞与其八个相邻位置（水平，垂直，对角线）的细胞都遵循以下四条生存定律：
 * 如果活细胞周围八个位置的活细胞数少于两个，则该位置活细胞死亡；
 * 如果活细胞周围八个位置有两个或三个活细胞，则该位置活细胞仍然存活；
 * 如果活细胞周围八个位置有超过三个活细胞，则该位置活细胞死亡；
 * 如果死细胞周围正好有三个活细胞，则该位置死细胞复活；
 * 根据当前状态，写一个函数来计算面板上所有细胞的下一个（一次更新后的）状态。下一个状态是通过将上述规则同时应用于当前状态下的每个细胞所形成的，其中细胞的出生和死亡是同时发生的。
 *
 *
 *
 * 输入：
 *  [
 *     [0,1,0],
 *    [0,0,1],
 *     [1,1,1],
 *     [0,0,0]
 *   ]
 *   输出：
 *   [
 *     [0,0,0],
 *     [1,0,1],
 *     [0,1,1],
 *     [0,1,0]
 *   ]
 *
 *   思路：
 *   1、将整个数组复制，然后遍历判断每个位置周围的情况，记录新值；
 *   2、原地更新，但要主要记录之前的信息，比如从活得变成死的记为2，
 *   死的变成活得记为-1，其中就包含了对应的元信息。
 *   3、由于状态值只有零一，所以一个int中32bit，只用了一位，
 *   可以用第二位来记录新的结果，第一位仍然为原值，输出时右移一位即可。
 */


#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int dx[8] = {0, 0, 1, -1, 1, 1, -1, -1};
        int dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};
        if(board.size()==0){
            return;
        }
        int n = board.size();
        int m = board[0].size();

        for(int i=0;i<n;++i){
            for(int j=0;j<m;++j){
                int cnt = 0;
                for(int k=0;k<8;++k){
                    int x = i+dx[k];
                    int y = j+dy[k];
                    if(x<0||x>=n || y<0 || y>=m){
                        continue;
                    }
                    cnt += board[x][y]&1;
                }
                if((board[i][j] & 1)>0){
                    if(cnt>=2&&cnt<=3){
                        board[i][j] |= 2;
                    }
                } else if(cnt==3){
                    board[i][j] |=2;
                }
            }
        }

        for(int i=0;i<n;++i){
            for(int j=0;j<m;++j){
                board[i][j]>>=1;
            }
        }
    }
};

int main(){
    Solution s;
    vector<vector<int>> nums = {{0,1,0},{0,0,1},{1,1,1},{0,0,0}};
    s.gameOfLife(nums);
    for(int i = 0;i<nums.size();++i){
        for (int j = 0; j < nums[0].size(); ++j) {
            cout<<nums[i][j]<<" ";
        }
        cout<<endl;
    }

    return 0;
}

