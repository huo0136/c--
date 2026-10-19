#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,m,k;
    double mu[101],sig[101],x[21],fi[21];
    double mu0=0,sig0=0,z,min=2100000000;
    int ans;
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)
    {
        cin>>mu[i];
        mu0+=mu[i];
    } 
    for(int i=1;i<=n;i++)
    {
        cin>>sig[i];
        sig0+=pow(sig[i],2);
    } 
    sig0=pow(sig0,0.5);
    for(int i=1;i<=k;i++) cin>>x[i];
    for(int i=1;i<=k;i++) cin>>fi[i];
    z=(m-mu0)/sig0;
    cout<<z<<endl;
    for(int i=1;i<=k;i++)
    {
        if(fabs(z-x[i])<min) 
        {
            ans=i;
            min=fabs(z-x[i]);
        }
        
    }
    cout<<fi[ans];
    system("pause");
    return 0;
}