#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "..\\CO_mid_pipline\\lib\\include\\CPU_pipeline.h"
using namespace std;

int main(){
    ifstream ifs(".\\test_data\\q1.txt",ios::in);
    if(!ifs.is_open()){
        cout<<"fail to open this file"<<endl;
        return 1;
    }

    stringstream ss;
    ss << ifs.rdbuf();
    ifs.close();
    string s;

    vector<string> arr;
    while(getline(ss, s)){
        // cout<<s<<endl;;
        arr.push_back(s);
    }
    arr.push_back("null");
    arr.push_back("null");
    arr.push_back("null");
    arr.push_back("null");

    Pipelined pipe;
    pipe.circle(arr);

    return 0;
}