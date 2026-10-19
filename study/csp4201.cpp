#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    string x[105];
    int a[105],b[105];
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>x[i];
        for(int j=0;j<x[i].size();j++)
        {
            if(x[i][j]=='.')
            {
                string temp1={""},temp2={""};
                for(int p=0;p<=j-1;p++)
                    temp1+=x[i][p];
                a[i]=stoi(temp1);
                for(int p=j+1;p<x[i].size();p++)
                    temp2+=x[i][p];
                b[i]=stoi(temp2);        
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(b[i]>=5) cout<<a[i]+1<<" ";
        else cout<<a[i]<<" ";
    }
    cout<<endl;
    for(int i=1;i<=n;i++)
    {
        if(b[i]>5) cout<<a[i]+1<<" ";
        else if(b[i]<5)cout<<a[i]<<" ";
        else
        {
            if(a[i]%2==0)
            {
                cout<<a[i]<<" ";
            }
            else 
            {
                cout<<a[i]+1<<" ";
            }
        }
    }
    return 0;
}