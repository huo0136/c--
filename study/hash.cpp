#include<bits/stdc++.h>
using namespace std;
int a[150005],n,m,p,sum[400][400]; //sum[x][y]即模x余y所有数的和;
int main() 
{
    vector<int> ans;
    cin>>n>>m;
    p=sqrt(n);
    for(int i=1;i<=n;i++) 
    {
        cin>>a[i];
        for(int j=1;j<=p;j++) 
        {
            sum[j][i%j]+=a[i];
        }
    }
    while(m--) 
    {
        char cmd;
        int x, y;
        cin>>cmd>>x>>y;
        if(cmd=='A') 
        {
            int temp=0;
            if(x<=p) 
            {
                temp=sum[x][y];
            } 
            else 
            {
                int ans=0;
                for(int i=y;i<=n;i+=x) 
                {
                    temp+=a[i];
                }
            }
            ans.push_back(temp);
        }
        if(cmd=='C')
        {
            for(int j=1;j<=p;j++)
            {
                sum[j][x%j]+=y-a[x];
            }
            a[x]=y;
        }
    }
    for(auto &i:ans) cout<<i<<endl;
    system("pause");
    return 0;
}