#include<bits/stdc++.h>
using namespace std;

int mu[105],a[105],dp[40005];
int main(){
    int n,m;
    double q;
    cin>>n>>m>>q;
    for(int i=0;i<n;i++) cin>>mu[i];
    long long Q=llround(q*1000.0);
    long long num=100000000LL*m*m;
    long long W=num/(Q*Q);
    for(int i=0;i<n;i++)
    {
        double s;
        cin>>s;
        a[i]=(int)llround(s*s*100.0);
    }

    long long totalW=0;
    for(int i=0;i<n;i++) totalW+=a[i];
    if(W>totalW) W=totalW;

    int cap=(int)W;
    for(int i=0;i<n;i++)
    {
        int w=a[i],v=mu[i];
        if(w>cap) continue;
        for(int j=cap;j>=w;j--)
        {
            dp[j]=max(dp[j],dp[j-w]+v);
        }
    }
    int ans=0;
    for(int j=0;j<=cap;j++)ans=max(ans,dp[j]);
    cout<<ans<<endl;
    return 0;
}