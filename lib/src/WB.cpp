#include <iomanip>
#include <iostream>
#include <string>
#include "WB.h"
using namespace std;


WB::WB(){
    opcode = "null";
    signal = "null";
    rs = -1;
    rt = -1;
    rd = -1;
    RegWriteValue = -1;
}

void WB::intoWB(string op, string sig, int s, int t, int d, int rwv, int rmv, int *reg){
    opcode=op;
    if(opcode == "null") {
        return;
    }
    signal="     "+sig.substr(5,7);

    rs=s;
    rt=t;
    rd=d;
    RegWriteValue = rwv;
    if(opcode == "lw"){
        reg[rt] = rmv;
    }
    else if(opcode == "add"){
        reg[rd] = RegWriteValue;
    }
    else if(opcode == "sub"){
        reg[rd] = RegWriteValue;
    }
}

void WB::printResult(){
    if(opcode == "null") cout<<setw(5)<<"wb"<<'|'<<setw(5)<<opcode<<'|'<<setw(9)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(8)<<'|'<<setw(6)<<'|'<<setw(6)<<'|'<< setw(12)<<'|'<<setw(15)<<'|'<<setw(16)<<'|'<<endl;
    else cout<<setw(5)<<"wb"<<'|'<<setw(5)<<opcode<<'|'<<setw(8)<<signal<<'|'<<setw(3)<<rs<<'|'<<setw(3)<<rt<<'|'<<setw(3)<<rd<<'|'<<endl;
}