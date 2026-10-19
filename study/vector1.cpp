#include<bits/stdc++.h>
using namespace std;
void print(vector<int> v1)
{
    for(vector<int>::iterator it=v1.begin();it!=v1.end();it++)
    {
        cout<<*it<<" ";
    }
    cout<<endl;
    return;
}
int main()
{
    vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);
    print(v1);
    v1.pop_back();
    print(v1);
    v1.insert(v1.begin(),100);
    print(v1);
    v1.erase(v1.end()-2);
    print(v1);
    v1.erase(v1.begin(),v1.end());
    print(v1);
    system("pause");
    return 0;
}
