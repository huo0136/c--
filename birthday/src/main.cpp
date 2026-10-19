#include "student.hpp"
#include <algorithm>   
#include <iostream>    
#include <string>      
#include <vector>  
#include <map> 
#include <fstream>
using namespace std;
int main()
{
    vector<student> students;
    if(!read("students.txt",students))
    {
        return 0;
    }
    map<pair<int,int>,vector<student>> groups;
    groups=group(students);
    ofstream out("birthday_result.txt");
    if(!out)
    {
        cout<<"Error:cannot open birthday_result.txt"<<endl;
        return 0;
    }
    for(auto& i:groups)
    {
        int month=i.first.first;
        int day=i.first.second;
        vector<student> s=i.second;
        string line=to_string(month)+" "+to_string(day);
        for(auto& j:s)
        {
            line+=" "+j.id;
        }
        cout<<line<<endl;
        out<<line<<endl;
    }
    out.close();
    system("pause");
    return 0;
}