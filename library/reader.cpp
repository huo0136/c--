#include <algorithm>   
#include <iostream>    
#include <string>      
#include <vector>  
#include <map> 
#include "reader.hpp"
#include "book.hpp"
#include "root.hpp"
void reader::submit(const string& id,const string& password)
{
    m.insert(pair<string,string>(id,password));
}
bool reader::login(const string& id,const string& password)
{
    if(m[id]==password) return true;
    else return false;
}
book* reader::searchbook(const string& id)
{
    for(vector<book>::iterator it=books.begin();it!=books.end();it++)
    {
        if(it->b_id==id) return &(*it);
    }
    return nullptr;
}
void reader::borrow(const string&r_id,const string& id)
{
    book* p=searchbook(id);
    if(p==nullptr) cout<<"No such book found!"<<endl;
    else
    {
        if(p->borrow==1) cout<<"This book has already been borrowed!"<<endl;
        else 
        {
            p->borrow=1;
            p->borrow_users.push_back(pair<string,bool>(r_id,0));
            cout<<"Book is borrowed successfully!"<<endl;
        } 
    } 
}
void reader::Return(const string&r_id,const string& id)
{
    book* p=searchbook(id);
    if(p==nullptr) cout<<"No such book found!"<<endl;
    else 
    {
        if(p->borrow==0) cout<<"This book has already been returned!"<<endl;
        else 
        {
            p->borrow=0;
            pair<string,bool> temp=pair<string,bool>(r_id,1);
            p->borrow_users.pop_back();
            p->borrow_users.push_back(temp);
            cout<<"Book is returned successfully!"<<endl;
        } 
    }                 
}
void reader::getid()
{
    for(auto& i:m)
    {
        cout<<i.first<<endl;
    }
}
void reader::R_resetid(const string& id)
{
    m[id]="1234";
}
void reader::erase(const string& id)
{
    for(vector<book>::iterator it=books.begin();it!=books.end();it++)
    {
        if(it->b_id==id)
        {
            books.erase(it);
            return;
        } 
    }
    return;
}
void reader::searchborrowbook(const string& r_id)
{
    bool find=0;
    for(auto& i:books)
    {
        for(auto& j:i.borrow_users)
        {
            if(j.first==r_id)
            {
                find=1;
                cout<<i.b_name<<endl;
                break;
            } 
        }
    }
    if(find==0) cout<<"No borrow books!"<<endl;
}
void reader::searchToReturnbook(const string& r_id)
{
    bool find=0;
    for(auto& i:books)
    {
        for(auto& j:i.borrow_users)
        {
            if(j.first==r_id && j.second==0)
            {
                find=1;
                cout<<i.b_name<<endl;
                break;
            } 
        }
    }
    if(find==0) cout<<"No borrow books!"<<endl;
}
void reader::searchfuzzily(const string& title)
{
    if(title=="") 
    {
        cout<<"无法查找空内容";
        return;
    }
    int judge=0;
    for(auto &i:books)
    {
        int pos=0,len=1,j=0;
        for(pos=0;pos<i.b_name.length();pos++)
        {
            for(len=1;pos+len<=i.b_name.length();len++)
                if(title==i.b_name.substr(pos,len))
                {
                    cout<<i.b_name<<endl;
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
}
void reader::borrownumber()
{
    vector<int> borrownumbers;
    for(auto& i:books)
    {
        int num=i.borrow_users.size();
        borrownumbers.push_back(num);
    }
    for(int i=0;i<borrownumbers.size();i++)
    {
        for(int j=i+1;j<borrownumbers.size();j++)
        {
            if(borrownumbers[j]>borrownumbers[i])
            {
                swap(borrownumbers[j],borrownumbers[i]);
                swap(books[i].b_id,books[j].b_id);
            }
        }
    }
    for(int i=0;i<borrownumbers.size();i++)
    {
        if(i==10) break;
        cout<<i+1<<"."<<books[i].b_id<<" "<<borrownumbers[i]<<endl;
    }
}
