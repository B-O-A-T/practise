数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

 

示例：

输入：n = 3
输出：[
       "((()))",
       "(()())",
       "(())()",
       "()(())",
       "()()()"
     ]

```
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        int right = n;
        int left = n;
        vector<string> result;
        generate("", left, right, result);
        return result;
    }

private:
    void generate(string item, int left, int right, vector<string> &result){
        if(left==0 && right ==0){
            result.push_back(item);
            return ;
        }
        if(left>0){
            generate(item+"(",left-1,right,result);
        }
        if(left<right){
            generate(item+")",left,right-1,result);
        }
    }
};
```
