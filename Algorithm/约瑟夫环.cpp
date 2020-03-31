/*
 * 0,1,,n-1这n个数字排成一个圆圈，从数字0开始，
 * 每次从这个圆圈里删除第m个数字。求出这个圆圈里剩下的最后一个数字。
 * 例如，0、1、2、3、4这5个数字组成一个圆圈，
 * 从数字0开始每次删除第3个数字，则删除的前4个数字依次是2、0、4、1，
 * 因此最后剩下的数字是3。
 *
 *
 * 解题思路：
 * 链接：https://leetcode-cn.com/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof/solution/huan-ge-jiao-du-ju-li-jie-jue-yue-se-fu-huan-by-as/
 * 来源：力扣（LeetCode）
 */

class Solution {
public:
    int lastRemaining(int n, int m) {
        int ans = m-1;
        for(int i=1;i<=n;++i){
            ans = (ans+m)%i;
        }
        cout<<ans<<endl;
        return ans;
    }
};

