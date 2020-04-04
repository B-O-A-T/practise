/*
链接：https://ac.nowcoder.com/acm/problem/13221
来源：牛客网

题目描述 
给定两个整数 l 和 r ，对于所有满足1 ≤ l ≤ x ≤ r ≤ 10^9 的 x ，把 x 的所有约数全部写下来。对于每个写下来的数，只保留最高位的那个数码。求1～9每个数码出现的次数。
输入描述:
一行，两个整数 l 和 r (1 ≤ l ≤ r ≤ 10^9)。
输出描述:
输出9行。

第 i 行，输出数码 i 出现的次数。
示例1
输入
1 4
输出
4
2
1
1
0
0
0
0
0

解题思路：有大佬说是整数分块板子题，弱鸡还没有看的很明白，今天时间不够，后续来补充

*/

#include<bits/stdc++.h>
typedef long long LL;
using namespace std;

LL solve(LL x,LL k){
    LL ans = 0;
    for(LL v =1;v*k<=x;v*=10){
        LL up = min(x,v*k+v-1);
        for(LL i = v*k;i<=up;){
            LL j = min(up,x/(x/i));
            ans+=(j-i+1)*(x/i);
            i = j+1;
        }
    }
    return ans;
}

int main(){
    long long  l,r;
    cin>>l>>r;
    for(int i=1;i<=9;i++){
        cout<<solve(r,i)-solve(l-1,i)<<endl;
    }
    return 0;
}
