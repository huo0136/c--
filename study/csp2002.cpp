#include<bits/stdc++.h>
using namespace std;
int n,k,t,xl,xr,yd,yu,x[21][1001],y[21][1001];
int pass=0,stay=0;
int main()
{
    cin>>n>>k>>t>>xl>>yd>>xr>>yu;
    for(int i=1;i<=n;i++) 
    {
        int num[1001],p=1;
        for(int j=1;j<=1000;j++) num[j]=0;
        int ans=0;
        for(int j=1;j<=t;j++)
        {
            cin>>x[i][j]>>y[i][j];
            if(x[i][j]>=xl && x[i][j]<=xr && y[i][j]<=yu && y[i][j]>=yd)
            {
                num[p]++;
            }
            else if(x[i][j]<xl || x[i][j]>xr || y[i][j]>yu || y[i][j]<yd)
            {
                p++;
            }
        } 
        for(int j=1;j<=1000;j++)
        {
            ans=max(ans,num[j]);
        }
        if(ans!=0) pass++;
        if(ans>=k) stay++;
    }
    cout<<pass<<endl<<stay;
    return 0;
}