#include "IF.h"

#include <iostream>
#include <iomanip>

using namespace std;

IF::IF(){
    value.push_back("null");
}

void IF::intoIF(string s){
    value.clear();
    
    stringstream ss;
    ss << s;
    while (getline(ss,s,' ')) {
        value.push_back(s); 
    }
}

void IF::printResult(){
    cout<<setw(5)<<"if"<<'|'<<setw(5);
    for (auto& ret : value){
        cout<<ret;
    }
    cout<<endl;
}