#pragma once
#include <algorithm>   
#include <iostream>    
#include <string>      
#include <vector>  
#include <map> 
using namespace std;
struct student
{
    string id;
    int month,day;
};
bool read(const string& filename,vector<student>& students);
map<pair<int,int>,vector<student>> group(vector<student> students);