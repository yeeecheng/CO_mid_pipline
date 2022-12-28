#include "EX.h"
#include <iostream>
#include <string>
using namespace std;

// EX建構值
// 初始化opcode, signal, rs, rt, rd, reg1, reg2, offset
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

// 進入EX
// 傳入ID的opcode, signal, rs, rt, rd, offset, reg1, reg2
void EX::intoEX(string op, string sig, int s, int t, int d, int o, int r1, int r2){
    
    // 存入EX對應到的變數中
    opcode=op;
    signal = sig;
    rs=s;
    rt=t;
    rd=d;
    reg1 = r1;
    reg2 = r2;
    offset = o;

    // 若opcode是null，則結束EX程序
    if(opcode == "null") {
        return;
    }

    // 若opcode是add，則兩個暫存器的值做相加，存到ALUresult中
    if(opcode == "add"){
        ALUresult = reg1+reg2;
    }
    // 若opcode是sub，則兩個暫存器的值做相減，存到ALUresult中
    else if(opcode == "sub"){
        ALUresult = reg1-reg2;
    }
    // 若opcode是lw或sw，則offset先除以四(1 word)，再加暫存器一的值，存到ALUresult中
    else if(opcode == "lw" || opcode == "sw"){
        ALUresult = reg1+offset/4;
    }
}

// 輸出EX的結果
// 也就是opcode, siginal, rs, rt, rd, offset, reg1, reg2, ALUresult的值
void EX::printResult(){
    if(opcode == "null") cout<<setw(5)<<"ex"<<'|'<<setw(5)<<opcode<<'|'<<setw(9)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(8)<<'|'<<setw(6)<<'|'<<setw(6)<<'|'<< setw(12)<<'|'<<setw(15)<<'|'<<setw(16)<<'|'<<endl;
        else cout<<setw(5)<<"ex"<<'|'<<setw(5)<<opcode<<'|'<<setw(8)<<signal<<'|'<<setw(3)<<rs<<'|'<<setw(3)<<rt<<'|'<<setw(3)<<rd<<'|'<<setw(7)<<offset<<'|'<<setw(5)<<reg1<<'|'<<setw(5)<<reg2<<'|'<<setw(11)<<ALUresult<<'|'<<setw(15) <<'|'<<setw(16) <<'|'<<endl;
}