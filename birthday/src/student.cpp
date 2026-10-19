#include "student.hpp"
#include <algorithm>   
#include <iostream>    
#include <string>      
#include <vector>  
#include <map> 
#include <fstream>
using namespace std;
bool read(const string& filename,vector<student>& students)
{
    ifstream in(filename);
    if(!in)
    {
        cout<<"Error:cannot open students.txt"<<endl;
        return false;
    }
    student s;
    while(in>>s.id>>s.month>>s.day)
    {
        students.push_back(s);
    }
    return true;
}
map<pair<int,int>,vector<student>> group(vector<student> students)
{
    map<pair<int,int>,vector<student>> groups;
    for(auto& i:students)
    {
        groups[{i.month,i.day}].push_back(i);
    }
    return groups;
}