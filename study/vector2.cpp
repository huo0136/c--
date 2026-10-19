#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    vector<int>v1;
    for(int i=1;i<=10000;i++)
    {
        v1.push_back(i);
    }
    cout<<"容量为"<<v1.capacity()<<endl;
    cout<<"大小为"<<v1.size()<<endl;
    v1.resize(3);
    cout<<"容量为"<<v1.capacity()<<endl;
    cout<<"大小为"<<v1.size()<<endl;
    vector<int>(v1).swap(v1);//创建匿名对象，再转移指针
    cout<<"容量为"<<v1.capacity()<<endl;
    cout<<"大小为"<<v1.size()<<endl;
    system("pause");
    return 0;
}