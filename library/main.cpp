#include"root.hpp"
#include"reader.hpp"
#include"rootmenu.hpp"
#include"readermenu.hpp"
#include <algorithm>   
#include <iostream>    
#include <string>      
#include <vector>  
#include <map> 
using namespace std;
int main()
{
    int choice;
    reader Reader;
    root r(&Reader);
    while(true)
    {
        cout<<"welcome!"<<endl;
        cout<<"1.Register an administrator account"<<endl;
        cout<<"2.Log in to the administrator account"<<endl;
        cout<<"3.Register a reader account"<<endl;
        cout<<"4.Log in to a reader account"<<endl;
        cin>>choice;
        switch (choice)
        {
            case 1://注册管理员账号
            {
                string id,password;
                cout<<"Please enter the username you want to create:"<<endl;
                cin>>id;
                cout<<"Please enter a password:"<<endl;
                cin>>password;
                r.submit(id,password);
                cout<<"Administrator account has been set up successfully!"<<endl;
                break;
            }    
            case 2://登录管理员账号
            {
                string id,password;
                cout<<"Please enter the username:"<<endl;
                cin>>id;
                cout<<"Please enter a password:"<<endl;
                cin>>password;
                if(r.login(id,password)==true) 
                {
                    cout<<"Login successful!"<<endl;
                    rootmenu(id,&Reader,&r);
                    break;
                }
                else
                {
                    cout<<"The username does not exist or the password is incorrect!"<<endl;
                }
                break;
            }  
            case 3://创建读者账号
            {
                string id,password;
                cout<<"Please enter the username to be created:"<<endl;
                cin>>id;
                cout<<"Please set a password:"<<endl;
                cin>>password;
                Reader.submit(id,password);
                cout<<"Reader account has been set up successfully!"<<endl;
                break;
            }  
            case 4://登录读者账号
            {
                string id,password;
                cout<<"Please enter the username:"<<endl;
                cin>>id;
                cout<<"Please enter a password:"<<endl;
                cin>>password;
                if(Reader.login(id,password)) 
                {
                    cout<<"Login successful!"<<endl;
                    readermenu(id,&Reader);
                }
                else
                {
                    cout<<"The username does not exist or the password is incorrect!"<<endl;
                }
                break;
            }  
            case 0://退出
            {
                cout<<"You have been logged out. We look forward to serving you again!"<<endl;
                system("pause");
                return 0;
            }
            default:
            {
                cout<<"No such option exists!"<<endl;
                break;
            }    
        }
    }
    system("pause");
    return 0;
}