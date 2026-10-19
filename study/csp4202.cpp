#include<bits/stdc++.h>
using namespace std;
int main()
{
    long long n;
    int m,min=INT_MAX;
    double k;
    cin>>n>>k>>m;
    int ans;
    int left=1,right=n/m,p;
    while(left<right)
    {
        p=(left+right)/2;
        double rest=n;
        for(int i=1;i<=m;i++)
        {
            rest=rest*(1-k/100)-p;
        }
        if(rest==0)
        {
            cout<<p;
            return 0;
        }
        if(rest>0)
        {
            ans=p;
            left=p+1;
        }
        if(rest<0)
        {
            right=p-1;
        }
    }
    cout<<ans;
    return 0;
}