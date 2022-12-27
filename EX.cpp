#include "EX.h"
#include <iostream>
#include <string>
using namespace std;

EX::EX(){
    opcode = "null";
    signal = "null";
    rs = -1;
    rt = -1;
    rd = -1;
    reg1 = -1;
    reg2 = -1;
    offset = -1;
}

void EX::intoEX(string op, string sig, int s, int t, int d, int o, int r1, int r2){
    opcode=op;
    signal = sig;
    rs=s;
    rt=t;
    rd=d;
    reg1 = r1;
    reg2 = r2;
    offset = o;

    if(opcode == "null") {
        return;
    }

    if(opcode == "add"){
        ALUresult = reg1+reg2;
    }else if(opcode == "sub"){
        ALUresult = reg1-reg2;
    }else if(opcode == "lw"){
        ALUresult = reg1+offset/4;
    }else if(opcode == "sw"){
        ALUresult = reg1+offset/4;
    }
}

void EX::printResult(){
    if(opcode == "null") cout<<setw(5)<<"ex"<<'|'<<setw(5)<<opcode<<'|'<<setw(9)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(8)<<'|'<<setw(6)<<'|'<<setw(6)<<'|'<< setw(12)<<'|'<<setw(15)<<'|'<<setw(16)<<'|'<<endl;
        else cout<<setw(5)<<"ex"<<'|'<<setw(5)<<opcode<<'|'<<setw(8)<<signal<<'|'<<setw(3)<<rs<<'|'<<setw(3)<<rt<<'|'<<setw(3)<<rd<<'|'<<setw(7)<<offset<<'|'<<setw(5)<<reg1<<'|'<<setw(5)<<reg2<<'|'<<setw(11)<<ALUresult<<'|'<<setw(15) <<'|'<<setw(16) <<'|'<<endl;
}