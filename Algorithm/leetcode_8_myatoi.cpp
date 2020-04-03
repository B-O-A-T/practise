/*
请你来实现一个 atoi 函数，使其能将字符串转换成整数。

首先，该函数会根据需要丢弃无用的开头空格字符，直到寻找到第一个非空格的字符为止。接下来的转化规则如下：

如果第一个非空字符为正或者负号时，则将该符号与之后面尽可能多的连续数字字符组合起来，形成一个有符号整数。
假如第一个非空字符是数字，则直接将其与之后连续的数字字符组合起来，形成一个整数。
该字符串在有效的整数部分之后也可能会存在多余的字符，那么这些字符可以被忽略，它们对函数不应该造成影响。
注意：假如该字符串中的第一个非空格字符不是一个有效整数字符、字符串为空或字符串仅包含空白字符时，则你的函数不需要进行转换，即无法进行有效转换。

在任何情况下，若函数不能进行有效的转换时，请返回 0 。

 提示：

本题中的空白字符只包括空格字符 ' ' 。
假设我们的环境只能存储 32 位大小的有符号整数，那么其数值范围为 [−231,  231 − 1]。如果数值超过这个范围，请返回  INT_MAX (231 − 1) 或 INT_MIN (−231) 。

 解题思路：
 一、找到所有边界条件，依次判断，见下面方法一
 二、状态机， 这里放上官方解答（https://leetcode-cn.com/problems/string-to-integer-atoi/solution/zi-fu-chuan-zhuan-huan-zheng-shu-atoi-by-leetcode-/）
 */

class Solution1 {
public:
    int myAtoi(string str) {
        int ans = 0;
        int length = str.length();

        bool flag = false;
        int idx = 0;
        // 去掉前面的空格
        while(idx<length && str[idx] == ' '){
            idx++;
        }
        // 全是空格返回0
        if (idx==length){
            return 0;
        }
        // 正负号的判断
        if(str[idx]=='-'){
            flag = true;
            idx++;
        } else if (str[idx]=='+') {
            idx++;
        } else if (str[idx]<'0'||str[idx]>'9'){
            return 0;
        }

        // 获取连续的数字
        while(idx<length && str[idx]>='0' && str[idx]<='9'){
            int digit = str[idx]-'0';
            // 边界判断，担心越界，所以采取交换原则，由原本的ans *10 +digit>INT_MAX
            // 改为 ans > (INT_MAX - digit)/10
            if (ans > (INT_MAX - digit)/10){
                return flag ? INT_MIN : INT_MAX;
            }
            ans = ans *10 +digit;
            idx++;
        }
        return flag? -ans:ans;
    }
};

class Automaton {
    string state = "start";
    unordered_map<string, vector<string>> table = {
            {"start", {"start", "signed", "in_number", "end"}},
            {"signed", {"end", "end", "in_number", "end"}},
            {"in_number", {"end", "end", "in_number", "end"}},
            {"end", {"end", "end", "end", "end"}}
    };

    int get_col(char c) {
        if (isspace(c)) return 0;
        if (c == '+' or c == '-') return 1;
        if (isdigit(c)) return 2;
        return 3;
    }
public:
    int sign = 1;
    long long ans = 0;

    void get(char c) {
        state = table[state][get_col(c)];
        if (state == "in_number") {
            ans = ans * 10 + c - '0';
            ans = sign == 1 ? min(ans, (long long)INT_MAX) : min(ans, -(long long)INT_MIN);
        }
        else if (state == "signed")
            sign = c == '+' ? 1 : -1;
    }
};

class Solution {
public:
    int myAtoi(string str) {
        Automaton automaton;
        for (char c : str)
            automaton.get(c);
        return automaton.sign * automaton.ans;
    }
};