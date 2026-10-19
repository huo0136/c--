#pragma once
#include <algorithm>   
#include <iostream>    
#include <string>      
#include <vector>  
#include <map> 
#include "book.hpp"
#include "reader.hpp"
using namespace std;
class reader
{
public:
    void submit(const string& id,const string& password);
    bool login(const string& id,const string& password);
    void getid();
    book* searchbook(const string& id);
    void borrow(const string&r_id,const string& id);
    void Return(const string&r_id,const string& id);
    void R_resetid(const string& id);
    void erase(const string& id);
    void searchborrowbook(const string& r_id);
    void searchToReturnbook(const string& r_id);
    void searchfuzzily(const string& title);
    void borrownumber();
    map<string,string>m;  
    vector<book>books;
};