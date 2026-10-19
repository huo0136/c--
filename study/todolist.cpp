#include<bits/stdc++.h>
#include<windows.h>

using namespace std;
int num0=0,num1=0,num2=0;//统计不同优先级任务的数量
struct task
{
    string title;
    bool done=false;
    int priority;//0是低级，1是中级，2是高级
};
class List
{
public:
    void addtask(string title,int priority);
    void complete(string title);
    void search(string tit);
    void listall();
    void listdone();
    void todolist();
    void Delete(string title);
private:
    task* find(string Title)
    {
        task* p;
        for(auto &i:m_tasks)
        {
            if(i.title==Title)
            {
                p=&i;
                return p;
            }
        }
        return nullptr;
    }       
    deque<task>m_tasks;  
};
void List::addtask(string title,int priority)//按照优先级顺序加任务，省了sort的时间
{
    task t;
    t.title=title;
    t.priority=priority;
    if(t.priority==0)
    {
        m_tasks.push_front(t);
        num0++;
    }
    if(t.priority==1)
    {
        m_tasks.insert(m_tasks.begin()+num0,t);
        num1++;
    }
    if(t.priority==2)
    {
        m_tasks.push_back(t);
        num2++;
    }
    return;
}
void List::complete(string title)//找到并完成，找不到就返回false，按照优先级完成任务
{
    task* p=find(title);
    if(p==nullptr) 
    {
        cout<<"未查找到此项目"<<endl;
        return;
    }    
    int pri=p->priority;
    if(pri==2)
    {
        for(auto &i:m_tasks)
        {
            if(i.title==title) 
            {
                i.done=true;
                return;
            }    
        }
    }
    if(pri==1)
    {
        int judge2=0;
        for(deque<task>::iterator it=m_tasks.end()-1;it!=m_tasks.end()-num2-1;it--)
        {
            if(it->done==0)
            {
                judge2=1;
                break;
            }
        }
        if(judge2==1)
        {
            cout<<"请先完成更高优先级的任务"<<endl;
            return;
        } 
        else 
        {
            for(auto &i:m_tasks)
                if(i.title==title) 
                {
                    i.done=true;
                    cout<<"该任务已完成"<<endl;
                    return;
                }    
        }
    }
    if(pri==0)
    {
        int judge2=0;
        for(deque<task>::iterator it=m_tasks.begin()+num0;it!=m_tasks.end();it++)
        {
            if(it->done==0)
            {
                judge2=1;
                break;
            }
        }
        if(judge2==1) cout<<"请先完成更高优先级的任务"<<endl;
        else 
        {
            for(auto &i:m_tasks)
                if(i.title==title) 
                {
                    i.done=true;
                    return;
                }    
        }
    }
    return;
}        
void List::search(string tit)
{
    if(tit=="") 
    {
        cout<<"无法查找空内容";
        return;
    }
    int judge=0;
    for(auto &i:m_tasks)
    {
        int pos=0,len=1,j=0;
        for(pos=0;pos<i.title.length();pos++)
        {
            for(len=1;pos+len<=i.title.length();len++)
                if(tit==i.title.substr(pos,len))
                {
                    cout<<i.title<<endl;
                    judge=1;
                    j=1;
                    break;
                }
            if(j==1) break;    
        }
    }
    if(judge==0)
    {
        cout<<"未查找到相关任务"<<endl;
        return;
    }
    return;
}
void List::listall()
{
    for(auto &i:m_tasks)
    {
        cout<<i.title<<endl;
    }
}
void List::listdone()
{
    bool judge=false;
    for(auto &i:m_tasks)
    {
        if(i.done==true) 
        {
            cout<<i.title<<" ";
            judge=true;
        }    
    }
    if(judge==true)
    {
        cout<<endl;
        return;
    }
    else
    {
        cout<<"none has done"<<endl;
        return;
    }
}
void List::todolist()
{
    bool judge=false;
    for(auto &i:m_tasks)
    {
        if(i.done==false) 
        {
            cout<<i.title<<endl;
            judge=true;
        }    
    }
    if(judge==true)
    {
        return;
    }
    else
    {
        cout<<"all have done"<<endl;
        return;
    }
}
void List::Delete(string title)
{
    for(deque<task>::iterator it=m_tasks.begin();it!=m_tasks.end();it++)
    {
        if(it->title==title)
        {
            if(it->priority==0) num0--;
            if(it->priority==1) num1--;
            if(it->priority==2) num2--;
            m_tasks.erase(it);
            cout<<"该任务已删除"<<endl;
            return;
        }
    }
    cout<<"未查找到该任务"<<endl;
    return;
}
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    List list;
    while(true)
    {
        int choice;
        cout<<"1.添加任务"<<endl;
        cout<<"2.完成任务"<<endl;
        cout<<"3.列出所有任务"<<endl;
        cout<<"4.列出已完成任务"<<endl;
        cout<<"5.列出未完成任务"<<endl;
        cout<<"6.删除任务"<<endl;
        cout<<"7.搜索相关任务"<<endl;
        cout<<"8.退出"<<endl;
        cin>>choice;
        if(choice==8)
        {
            cout<<"已退出"<<endl;
            return 0;
        }
        else if(choice==1)
        {
            string title1;
            int priority;
            cout<<"请添加任务和优先级:";
            cin>>title1>>priority;
            if(priority>2) priority=2;
            if(priority<1) priority=0;//防止无法运行
            list.addtask(title1,priority);
            cout<<"任务已添加"<<endl;
        }
        else if(choice==2)
        {
            string title1;
            cout<<"请添加完成任务名:";
            cin>>title1;
            list.complete(title1);
            
        }   
        else if(choice==3)
        {
            cout<<"以下是所有任务："<<endl;
            list.listall();
            cout<<"任务已全部显示"<<endl;
        }   
        else if(choice==4)
        {
            cout<<"以下是所有已完成任务:"<<endl;
            list.listdone();
            cout<<"完成任务已全部显示"<<endl;
        }
        else if(choice==5)
        {
            cout<<"以下是所有未完成任务："<<endl;
            list.todolist();
            cout<<"未完成任务已全部显示"<<endl;
        }
        else if(choice==6)
        {
            string title;
            cout<<"请输入要删除的任务:";
            cin>>title;
            list.Delete(title);
        }
        else if(choice==7)
        {
            string tit;
            cout<<"请输入想要查找的内容:";
            cin>>tit;
            cout<<"以下是相关搜索："<<endl;
            list.search(tit);
        }
        else
        {
            cout<<"无当前选项，请重新输入"<<endl;
        }
    }
    system("pause");
    return 0;
}