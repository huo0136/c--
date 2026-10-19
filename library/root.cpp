#include"root.hpp"
#include"book.hpp"
#include "reader.hpp"
#include <algorithm>   
#include <iostream>    
#include <string>      
#include <vector>  
#include <map> 
void root::submit(const string& id,const string& password)
{
    m.insert(pair<string,string>(id,password));
}
bool root::login(const string& id,const string& password)
{
    if(m[id]==password) return true;
    else return false;
}
void root::setbook(const book& b,reader* Reader)
{
    books.push_back(b);
    Reader->books.push_back(b);
}
void root::erasebook(const string& id,reader* Reader)
{
    for(vector<book>::iterator it=books.begin();it!=books.end();it++)
    {
        if(it->b_id==id)
        {
            books.erase(it);
            Reader->erase(id);
            cout<<"This book has been deleted!"<<endl;
            return;
        } 
    }
    cout<<"This book does not exist!"<<endl;
    return;
}
book* root::searchbook(const string& id)
{
    for(vector<book>::iterator it=books.begin();it!=books.end();it++)
    {
        if(it->b_id==id) return &(*it);
    }
    return nullptr;
}
int root::searchRecord(const string& id)//查找借阅人数
{
    book* p=searchbook(id);
    return p->borrow_users.size();
}
void root::addreader(const string& id,reader* Reader)
{
    Reader->submit(id,"1234");   
    return; 
}
void root::getallreader(reader* Reader)
{
    Reader->getid();
    return;
}
void root::resetid(const string& id,reader* Reader)
{
    Reader->R_resetid(id);
    return;
}
void root::setnewpwd(const string& id,const string& new_password)
{
    m[id]=new_password;
}
void root::searchRecordOfBook(const string& b_id,reader* Reader)
{
    book* p;
    for(auto& i:Reader->books)
    {
        if(i.b_id==b_id)
        {
            p=&i;
        }
    }
    for(auto& i:p->borrow_users)
    {
        cout<<i.first<<endl;
    }
}
void root::searchRecordOfReader(const string& id,reader* Reader)
{
    for(auto& i:Reader->books)
    {
        for(auto& j:i.borrow_users)
        {
            if(j.first==id) cout<<i.b_id<<endl;
        }
    }
}