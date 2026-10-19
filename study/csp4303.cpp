#include<bits/stdc++.h>
using namespace std;
int n,m,T,T0[101];
struct task
{
    int t0,s[101],ssum;
    int during=0;
};
task tasks[101];
vector<task*> Queues[101];//Queues[i]是指第i个cpu装着的任务
bool Judge()
{
    for(int i=1;i<=m;i++)
    {
        if(!Queues[i].empty()) return false;
    }
    return true;
}
void work(int cpu)//每一个cpu一秒的工作
{
    if(Queues[cpu].empty()) return;
    int judge=0;
    auto it=Queues[cpu][0];
    for(int j=1;j<=it->ssum;j++)
    {
        
        if(it->s[j]==cpu)
        {
            judge=1;
            if(it->t0<=2) it->t0=0;
            else it->t0-=2; 
            it->during++;
            break;
        } 
    }
    if(judge==0)
    {
        it->t0--;
        it->during++;
    } 
    if(it->t0==0)
    {
        Queues[cpu].erase(Queues[cpu].begin());
        for(int i=0;i<Queues[cpu].size();i++)
        {
            if(Queues[cpu][i]->during!=0) Queues[cpu][i]->during++;
        }  
    } 
    else 
    {
        for(int i=1;i<Queues[cpu].size();i++)
        {
            if(Queues[cpu][i]->during!=0) Queues[cpu][i]->during++;
        }  
    }
    //持续计算未完成任务的during
      
}
int main()
{
    cin>>n>>m>>T;
    for(int i=1;i<=m;i++) cin>>T0[i];
    for(int i=1;i<=n;i++)
    {
        cin>>tasks[i].t0>>tasks[i].ssum;
        for(int j=1;j<=tasks[i].ssum;j++) cin>>tasks[i].s[j];
    }

    //一开始排好队
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if((j-1)%m+1==i)
            Queues[i].push_back(&tasks[j]);
        }
    }
    for(int I=1;;I++)
    {
        if(Judge()) break;
        //一个周期
        for(int i=1;i<=T;i++)
        {
            for(int j=1;j<=m;j++)
            {
                work(j);
                if(i%T0[j]==0)//持续工作到T0的倍数就将第一个任务插到尾
                {
                    rotate(Queues[j].begin(),Queues[j].begin()+1,Queues[j].end());
                }
            } 
        }
        for(int i=1;i<=n;i++)
        {
            cout<<tasks[i].during<<" ";
        }
        cout<<endl;
        //交换队列
        vector<task*> temp=Queues[m]; 
        for(int i=1;i<=m;i++)
        {    
            if(i==1) Queues[m]=Queues[1];
            else if(i==m) Queues[m-1]=temp;
            else Queues[i]=Queues[i+1];        
        }
    }
    for(int i=1;i<=n;i++)
    {
        cout<<tasks[i].during<<" ";
    }
    return 0;
}

    

    
     