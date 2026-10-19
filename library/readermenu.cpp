#include"readermenu.hpp"
#include"book.hpp"
#include"reader.hpp"
#include"root.hpp"
#include <algorithm>   
#include <iostream>    
#include <string>      
#include <vector>  
#include <map>
void readermenu(string r_id,reader* Reader)
{
    int choice;
    while(true)
    {
        cout<<"Welcome user "<<r_id<<" use the reader system!"<<endl;
        cout<<"1.Change password"<<endl;
        cout<<"2.Borrow books"<<endl;
        cout<<"3.Return books"<<endl;
        cout<<"4.Search books by the book id"<<endl;
        cout<<"5.Search books by the book title fuzzily"<<endl;
        cout<<"6.Search books you have borrowed"<<endl;
        cout<<"7.Search books you should ruturn"<<endl;
        cout<<"8.View the top 10 most borrowed books"<<endl;
        cout<<"9.Return"<<endl;
        cout<<"10.Exit"<<endl;
        cin>>choice;
        switch(choice)
        {
            case 1://修改密码
            {
                string new_password;
                cout<<"Please enter a new password:"<<endl;
                cin>>new_password;
                Reader->m[r_id]=new_password;
                cout<<"New password has been set successfully!"<<endl;
                break;
            }
            case 2://借阅图书
            {
                string id;
                cout<<"Please enter the ID of the book you want to borrow:"<<endl;
                cin>>id;
                Reader->borrow(r_id,id);
                break;
            }
            case 3://还书
            {
                string id;
                cout<<"Please enter the ID of the book you want to return:"<<endl;
                cin>>id;
                Reader->Return(r_id,id);
                break;
            }
            case 4://搜索书本
            {
                string id;
                cout<<"Please enter the ID of the book you want to search:"<<endl;
                cin>>id;
                book* p=Reader->searchbook(id);
                if(p==nullptr) 
                {
                    cout<<"No such book found!"<<endl;
                }
                else
                {
                    cout<<"The book title is "<<p->b_name<<endl;
                }
                break;
            }
            case 5://模糊搜索书名
            {
                string title;
                cout<<"Enter the content you want to search for:"<<endl;
                cin>>title;
                cout<<"The following are the search results:"<<endl;
                Reader->searchfuzzily(title);
                break;
            }
            case 6://搜索借阅过的书籍
            {
                cout<<"The title of books you have borrowed are listed:"<<endl;
                Reader->searchborrowbook(r_id);
                break;
            }
            case 7://搜索未归还的书本
            {
                cout<<"The title of books you should ruturn are listed:"<<endl;
                Reader->searchToReturnbook(r_id);
                break;
            }
            case 8://查看借阅量排行榜前十的图书
            {
                cout<<"The following are the top 10 most borrowed books and its borrowed times:"<<endl;
                Reader->borrownumber();
                break;
            }
            
            case 9://返回上一界面
            {
                return;
            }
            case 10://退出程序
            {
                exit(0);
            }
            default:
            {
                cout<<"No such option exists!"<<endl;
                break;
            }  
        }
    }
}