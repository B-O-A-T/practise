给定一个字符串，逐个翻转字符串中的每个单词。

 

示例 1：

输入: "the sky is blue"
输出: "blue is sky the"
示例 2：

输入: "  hello world!  "
输出: "world! hello"
解释: 输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。
示例 3：

输入: "a good   example"
输出: "example good a"
解释: 如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。


```
class Solution {
public:
    string reverseWords(string s) {
        reverse(s.begin(), s.end());

        int idx = 0;
        for(int start = 0; start<s.size();++start){
            if(s[start]!=' ') {
                if(idx !=0) s[idx++] = ' ';
                
                int end = start;
                while (end<s.size() && s[end] != ' ')
                    s[idx++] = s[end++];

                reverse(s.begin()+idx-(end-start), s.begin()+idx);

                start = end;
            }
        }
        s.erase(s.begin() + idx, s.end());
        return s;
    }
};
```