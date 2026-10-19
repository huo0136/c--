#include <algorithm>   
#include <iostream>    
#include <string>      
#include <vector>   
#include <map> 
using namespace std;  
struct Book
{
    int id;
    string author,title;
    double price;
};
class library
{
public:
    void add(const int&id,const Book& b);
    void del(const int& id);
    void mod(const int& id,const string& author,const string& title,const double& price);
    void list();
    vector<Book> books;
};
void library::add(const int& id,const Book& b)
{
    bool judge=0;
    for(auto& i:books) 
    {
        if(i.id==id)
        {
            judge=1;
            break;
        }
    }
    if(judge==0) books.push_back(b);
    else cout<<"Add Failed: id already exists!"<<endl;
}
void library::del(const int& id)
{
    bool judge=0;
    for(auto& i:books) 
    {
        if(i.id==id)
        {
            judge=1;
            break;
        }
    }
    if(judge==0) 
    {
        cout<<"Delete Failed:id does not exit!"<<endl;
        return;
    } 
    for(vector<Book>::iterator it=books.begin();it!=books.end();it++)
    {
        if(it->id==id) books.erase(it);
    }
}
void library::mod(const int& id,const string& author,const string& title,const double& price)//按id修改图书的作者、书名和价格。若不存在，输出ModifyFailed:iddoesnotexist；成功则不输出。
{
    bool judge=0;
    for(auto& i:books)
        if(i.id==id)
        {
            judge=1;
            i.author=author;
            i.title=title;
            i.price=price;
            break;
        }
    if(judge==0) cout<<"Modify Failed:id does not exist!"<<endl;
}
void library::list()
{
    for(int i=0;i<books.size();i++)//冒泡
    {
        for(int j=i+1;j<books.size();j++)
        {
            if(books[j].id<books[i].id) swap(books[j],books[i]);
        }
    }
    for(auto& i:books)
    {
        cout<<i.id<<" "<<i.author<<" "<<i.title<<" ";
        printf("%.2lf\n",i.price);
    }
}
int main()
{
    int n;
    string choice[21];
    library h;
    int id[21];
    string author[21],title[21];
    double price[21];
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>choice[i];
        if(choice[i]=="ADD")
        {
            cin>>id[i]>>author[i]>>title[i]>>price[i];
        }
        if(choice[i]=="DEL")
        {
            cin>>id[i];
        }
        if(choice[i]=="MOD")
        {
            cin>>id[i]>>author[i]>>title[i]>>price[i];
        }
    }
    cout<<"----------------------------"<<endl;
    for(int i=1;i<=n;i++)
    {
        if(choice[i]=="ADD")
        {
            Book b;
            b.id=id[i];b.author=author[i];b.price=price[i];b.title=title[i];
            h.add(id[i],b);
        }
        if(choice[i]=="DEL")
        {
            h.del(id[i]);
        }
        if(choice[i]=="MOD")
        {
            h.mod(id[i],author[i],title[i],price[i]);
        }
        if(choice[i]=="LIST")
        {
            h.list();
        }
    }
}
