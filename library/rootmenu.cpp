#include"rootmenu.hpp"
#include"book.hpp"
#include"root.hpp"
#include "reader.hpp"
#include <algorithm>   
#include <iostream>    
#include <string>      
#include <vector>  
#include <map>
void rootmenu(string id,reader* Reader,root* Root)
{
    int choice;
    book b;
    while(true)
    {
        cout<<"Welcome user "<<id<<" use the administrator system!"<<endl;
        cout<<"1.Change password"<<endl;
        cout<<"2.Add books"<<endl;
        cout<<"3.Delete books"<<endl;
        cout<<"4.Search books by book id"<<endl;
        cout<<"5.Search books by the book title fuzzily"<<endl;
        cout<<"6.Add a reader account"<<endl;
        cout<<"7.Search the borrowing records of a specified reader"<<endl;
        cout<<"8.Search the borrowing records of a specified book"<<endl;
        cout<<"9.Reset the password of a reader account"<<endl;
        cout<<"10.Show all readers"<<endl;
        cout<<"11.Check the borrow count for a specified book"<<endl;
        cout<<"12.Return"<<endl;
        cout<<"13.Exit"<<endl;
        cin>>choice;
        switch(choice)
        {
            case 1://修改密码
            {
                string new_password;
                cout<<"Please enter a new password:"<<endl;
                cin>>new_password;
                Root->setnewpwd(id,new_password);
                cout<<"New password has been set successfully!"<<endl;
                break;
            }
            case 2://增加图书
            {
                string b_id,isbn,b_name,w_name,publisher,publishtime,inrtoduction;
                double price;
                int page;  
                cout<<"Please enter the book information:"<<endl;
                cout<<"Please enter the ID:"<<endl;
                cin>>b_id;
                cout<<"Please enter the ISBN:"<<endl;
                cin>>isbn;
                cout<<"Please enter the book title:"<<endl;
                cin>>b_name;
                cout<<"Please enter the author's name:"<<endl;
                cin>>w_name;
                cout<<"Please enter the publisher:"<<endl;
                cin>>publisher;
                cout<<"Please enter the publication date:"<<endl;
                cin>>publishtime;
                cout<<"Please enter the book description:"<<endl;
                cin>>inrtoduction;
                cout<<"Please enter the price:"<<endl;
                cin>>price;
                cout<<"Please enter the number of pages:"<<endl;
                cin>>page;
                b.b_id=b_id;b.isbn=isbn;b.b_name=b_name;b.w_name=w_name;b.price=price;b.page=page;
                b.publisher=publisher;b.publishtime=publishtime;b.inrtoduction=inrtoduction;
                Root->setbook(b,Reader);
                cout<<"Book information has been entered successfully!"<<endl;
                break;
            }
            case 3://删除图书
            {
                string id;
                cout<<"Please enter the ID of the book to be deleted:"<<endl;
                cin>>id;
                Root->erasebook(id,Reader);
                break;
            }
            case 4://通过id查找图书
            {
                string id;
                cout<<"Please enter the ID of the book to search for:"<<endl;
                cin>>id;
                book* p=Root->searchbook(id);
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
            case 5://模糊搜索图书
            {
                string title;
                cout<<"Enter the content you want to search for:"<<endl;
                cin>>title;
                cout<<"The following are the search results:"<<endl;
                Reader->searchfuzzily(title);
                break;
            }
            case 6://添加读者用户
            {
                string id;
                cout<<"Please enter the username you want to create:"<<endl;
                cin>>id;
                Root->addreader(id,Reader);
                cout<<"the user account has been created!"<<endl;
                break;
            }
            case 7://查看读者的借阅记录
            {
                string id;
                cout<<"Please enter the reader id you want to search for:"<<endl;
                cin>>id;
                cout<<"The following are the borrowing records of this reader:"<<endl;
                Root->searchRecordOfReader(id,Reader);
                break;
            }
            case 8://查看书本的借阅记录
            {
                string b_id;
                cout<<"Please enter the book id you want to search for:"<<endl;
                cin>>b_id;
                cout<<"The following are the borrowing records of this book:"<<endl;
                Root->searchRecordOfBook(b_id,Reader);
                break;
            }
            case 9://重置读者密码
            {
                string id;
                cout<<"Please enter the ID of the reader whose password you want to reset:"<<endl;
                cin>>id;
                Root->resetid(id,Reader);
                cout<<"The reader's password has been reset successfully!"<<endl;
                break;
            }
            case 10://显示所有读者id
            {
                cout<<"The following are all the reader IDs:"<<endl;
                Root->getallreader(Reader);
                break;
            }
            case 11://查指定图书的借阅数量
            {
                string id;
                cout<<"Please enter the book whose borrowing record you want to search for:"<<endl;
                cin>>id;
                int sum=Root->searchRecord(id);
                cout<<"The total number of times this book has been borrowed is"<<sum<<endl;
                break;
            }
            case 12://返回上一界面
            {
                return;
            }
            case 13://退出程序
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