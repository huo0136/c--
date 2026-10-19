#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s1="abcdab";
    int pos=s1.find("ab");//从左往右找到就返回对应字符串的第一个位置，找不到就返回-1
    cout<<pos<<endl;

    pos=s1.rfind("ab");//从右往左查找，仍返回'a'的位置
    cout<<pos<<endl;

    string s2;
    s2.append("abcdef");
    s2.replace(0,4,"qwerabcd");//替换：从0号位置开始用"qwerabcd"替换前四个字符
    cout<<s2<<endl;
    return 0;
}