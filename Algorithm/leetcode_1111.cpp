/*
 * 有效括号的嵌套深度
 *  给你一个「有效括号字符串」 seq，
 *  请你将其分成两个不相交的有效括号字符串，A 和 B，
 *  并使这两个字符串的深度最小。
 *
 * 示例 1：

输入：seq = "(()())"
输出：[0,1,1,1,1,0]
示例 2：

输入：seq = "()(())()"
输出：[0,0,0,1,1,0,1,1]
解释：本示例答案不唯一。
按此输出 A = "()()", B = "()()", max(depth(A), depth(B)) = 1，它们的深度最小。
像 [1,1,1,0,0,1,1,1]，也是正确结果，其中 A = "()()()", B = "()", max(depth(A), depth(B)) = 1 。

 *
 *  解题思路：
 *  要使分得的两个字符串深度最小，最好的结果就是平分，
 *  那么怎么样能够做到尽量平分呢，那就是按奇偶的不同分别分给A，B
 *  就是准备一个栈，’（‘就压栈，记录count++，count为奇数，置为1，
 *  偶数，置为0；当读到’）‘，将栈顶’（‘弹出，记录count--，同理置位。
 */

// 这里直接采用vector模拟结果
class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        int cnt = 0;
        vector<int> res;
        for (auto c : seq) {
            if (c == '(') {
                res.push_back((++cnt)&1);
            } else {
                res.push_back((cnt--)&1);
            }
        }
        return res;
    }
};
