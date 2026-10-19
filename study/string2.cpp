#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s1="i ";
    s1+="love ";
    string s2="you";
    s1+=s2;
    cout<<s1<<endl;
    string s3="i";
    s3.append(" love ");
    s3.append("you hhh",3);
    cout<<s3;
    s3.append(s1);//拼接s3，s1
    cout<<endl<<s3;
    string s4;
    s4.append(s3,0,6);//拼接，从0位开始，找6个字符拼接到尾巴
    cout<<endl<<s4;
    return 0;
}