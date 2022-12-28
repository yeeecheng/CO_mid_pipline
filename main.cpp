#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "CPU_pipeline.h"
using namespace std;

int main(int argc,char **argv){

    // 預設檔案路徑
    string file_path ="./test_data/q1.txt";
    
    // 判斷是否放超過一個的檔案路徑
    if(argc > 2){
        
        cout<<"only input one file path\n";
        // 使用 -1 代表程式執行失敗
        return -1;
    }
    // 使用額外輸入的檔案路徑
    else if(argc>1){
        file_path = argv[1];
    }

    ifstream ifs(file_path,ios::in);
    if(!ifs.is_open()){

        cout<<"fail to open this file"<<endl;
        // 使用 -1 代表程式執行失敗
        return -1;
    }

    // 讀入檔案的資料
    stringstream ss;
    ss << ifs.rdbuf();
    ifs.close();
    string s;

    // arr vector存指令
    vector<string> arr;

    // 用換行切割資料，存入arr vector
    while(getline(ss, s)){
        arr.push_back(s);
    }
    // 放入四個null指令，來把最後一個指令往前推
    arr.push_back("null");
    arr.push_back("null");
    arr.push_back("null");
    arr.push_back("null");

    // 初始化piplined
    Pipelined pipe;

    //  開始循環指令
    pipe.circle(arr);

    return 0;
}