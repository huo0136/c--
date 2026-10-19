#pragma once
#include <algorithm>   
#include <iostream>    
#include <string>      
#include <vector>  
#include <map> 
using namespace std; 
class book
{
public:
    string b_id,isbn,b_name,w_name,publisher,publishtime,inrtoduction;
    double price;
    int page;
    bool borrow=0;//0代表未借出
    vector<pair<string,bool>>borrow_users;//string存储借过的读者，bool存储是否归还
};