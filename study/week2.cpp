#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
int n;
double a[100000][6],l1,l2,l3,maxl=0,maxs=0;
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    cin>>n;
    for(int i=0;i<n;i++)
    {
        double *p0=a[i];
        for(int j=0;j<6;j++) cin>>*(p0+j);
        l1=sqrt(pow(*p0-*(p0+2),2)+pow(*(p0+1)-*(p0+3),2));
        l2=sqrt(pow(*p0-*(p0+4),2)+pow(*(p0+1)-*(p0+5),2));
        l3=sqrt(pow(*(p0+2)-*(p0+4),2)+pow(*(p0+3)-*(p0+5),2));
        double p=(l1+l2+l3)/2;
        double s=sqrt(p*(p-l1)*(p-l2)*(p-l3));
        if(s==0) continue;//三点共线舍去
        maxl=max(maxl,l1+l2+l3);
        maxs=max(maxs,s);
    }
    cout<<"面积最大为"<<maxs<<endl;
    cout<<"周长最大为"<<maxl<<endl;
    system("pause");
    return 0;
}