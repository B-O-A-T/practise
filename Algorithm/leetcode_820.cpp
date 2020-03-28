//
// 题目描述：给定一个单词列表，我们将这个列表编码成一个索引字符串 S 与一个索引列表 A。
// 例如，如果这个列表是 ["time", "me", "bell"]，我们就可以将其表示
// 为 S = "time#bell#" 和 indexes = [0, 2, 5]。
// 对于每一个索引，我们可以通过从字符串 S 中索引的位置开始读取字符串，
// 直到 "#" 结束，来恢复我们之前的单词列表。
// 那么成功对给定单词列表进行编码的最小字符串长度是多少呢？
//
// 输入: words = ["time", "me", "bell"]
// 输出: 10
// 说明: S = "time#bell#" ， indexes = [0, 2, 5] 。
//
// 解题思路：字典树+DFS
// 由于是后缀重复，修改字典树的插入方法，从后遍历添加，
// 然后用DFS遍历字典树，求得有叶子节点的路径和
//



class Trie{
private:
    int isEnd;

public:
    Trie* next[26];
    Trie(){
        isEnd=false;
        memset(next,0,sizeof(next));
    }
    void insert(string words){
        Trie* node = this;
        for(int i=words.length()-1;i>=0;--i){
            if(node->next[words[i]-'a']==nullptr){
                node->next[words[i]-'a'] = new Trie();
            }
            node = node->next[words[i]-'a'];
        }
        node->isEnd=true;
    }
};
class Solution {
public:
    int minimumLengthEncoding(vector<string>& words) {
        Trie * root = new Trie();
        for(int i=0;i<words.size();++i){
            root->insert(words[i]);
        }
        int res = 0;
        d(root,res,1);
        return res;
    }

    void d(Trie *root, int &res, int deep){
        bool f = true;
        for(int i=0;i<26;++i){
            if(root->next[i]!=nullptr){
                d(root->next[i],res,deep+1);
                f = false;
            }
        }
        if (f) res+=deep;
    }
};
