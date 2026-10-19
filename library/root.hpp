#pragma once
#include <algorithm>   
#include <iostream>    
#include <string>      
#include <vector>  
#include <map> 
#include "book.hpp"
#include "reader.hpp"
using namespace std; 
class root
{
public:
    root(reader* Reader) : p(Reader){}
    void submit(const string& id,const string& password);
    bool login(const string& id,const string& password);
    void setbook(const book& b,reader* Reader);
    void erasebook(const string& id,reader* Reader);
    book* searchbook(const string& id);
    int searchRecord(const string& id);
    void addreader(const string& id,reader* Reader);
    void getallreader(reader* Reader);
    void resetid(const string& id,reader* Reader);
    void setnewpwd(const string& id,const string& new_password);
    void searchRecordOfBook(const string& b_id,reader* Reader);
    void searchRecordOfReader(const string& id,reader* Reader);
    map<string,string>m;
    vector<book>books;
    reader* p;
};