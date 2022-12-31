#include <iomanip>
#include <iostream>
#include <string>
#include "WB.h"
using namespace std;

// WB建構值
// 初始化opcode, signal, rs, rt, rd, RegWriteValue
WB::WB(){
    opcode = "null";
    signal = "null";
    rs = -1;
    rt = -1;
    rd = -1;
    RegWriteValue = -1;
}

// 進入WB
// 傳入MEM的opcode, signal, rs, rt, rd, ALUresult, ReadmemValue, register
void WB::intoWB(string op, string sig, int s, int t, int d, int rwv, int rmv, int *reg){
    
    // 存入WB對應到的變數中
    opcode=op;

    // 若opcode是null，則結束WB程序
    if(opcode == "null") {
        return;
    }

    // 若opcode不是null，則切割signal字串
    signal="     "+sig.substr(5,7);
    rs=s;
    rt=t;
    rd=d;
    // RegWriteValue = ALUresult
    RegWriteValue = rwv;

    // 若opcode是lw，則把暫存器rt的位置存入ReadmemValue
    if(opcode == "lw"){
        reg[rt] = rmv;
    }
    // 若opcode是add或sub，則把暫存器rd的位置存入RegWriteValue
    else if(opcode == "add" || opcode == "sub"){
        reg[rd] = RegWriteValue;
    }
}

// 輸出WB的結果
// 也就是opcode, siginal, rs, rt, rd的值
void WB::printResult(){
    if(opcode == "null") cout<<setw(5)<<"wb"<<'|'<<setw(5)<<opcode<<'|'<<setw(9)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(8)<<'|'<<setw(6)<<'|'<<setw(6)<<'|'<< setw(12)<<'|'<<setw(15)<<'|'<<setw(16)<<'|'<<endl;
    else cout<<setw(5)<<"wb"<<'|'<<setw(5)<<opcode<<'|'<<setw(8)<<signal<<'|'<<setw(3)<<rs<<'|'<<setw(3)<<rt<<'|'<<setw(3)<<rd<<'|'<<setw(8)<<'|'<<setw(6)<<'|'<<setw(6)<<'|'<< setw(12)<<'|'<<setw(15)<<'|'<<setw(16)<<'|'<<endl;
}