#include "IF.h"

#include <iostream>
#include <iomanip>

using namespace std;

// IF建構值
// 初始value vector，一開始放null，表示沒有指令
IF::IF(){
    value.push_back("null");
}

// 進入IF
void IF::intoIF(string s){
    
    // 先清空value vector
    value.clear();

    // 把指令存入value vector
    stringstream ss;
    ss << s;
    while (getline(ss,s,' ')) {
        value.push_back(s); 
    }
}

// 輸出IF的結果
// 也就是完整的指令
void IF::printResult(){
    cout<<setw(5)<<"if"<<'|'<<setw(5);
    for (auto& ret : value){
        cout<<ret;
    }
    cout<<endl;
}