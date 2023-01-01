#include "MEM.h"

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// MEM建構值
// 初始化opcode, signal, rs, rt, rd, ALUresult, ReadmemValue
MEM::MEM(){
    opcode = "null";
    signal = "null";
    rs = -1;
    rt = -1;
    rd = -1;
    ALUresult = -1;
    ReadmemValue = -1;
}

// 進入MEM
// 傳入EX的opcode, signal, rs, rt, rd, ALU result, reg2, memory
void MEM::intoMEM(string op, string sig, int s, int t, int d, int alu_result, int write_data, int *mem){
    
    // 存入MEM對應到的變數中
    opcode=op;
    rs=s;
    rt=t;
    rd=d;
    ALUresult = alu_result;

    // 若opcode是null，則結束MEM程序
    if(opcode == "null") {
        return;
    }
    // 若opcode不是null，則切割signal字串
    signal="  "+sig.substr(2,7);

    // 若MemRead=1，則讀取mem且位置是ALUresult的資料(opcode=lw)
    if(signal[3] == '1'){
        ReadmemValue = mem[ALUresult];
    }
    // 若MemRead=0，且MemWrite=1，則把資料寫入mem且ALUresult的位置(opcode是sw)
    else if(signal[3] == '0' && signal[4] == '1'){
        mem[ALUresult] = write_data;
    }
}

// 輸出MEM的結果
// 也就是opcode, signal, rs, rt, rd, ALUresult, ReadmemValue的值
void MEM::printResult(){
    if(opcode == "null") cout<<setw(5)<<"mem"<<'|'<<setw(5)<<opcode<<'|'<<setw(9)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(8)<<'|'<<setw(6)<<'|'<<setw(6)<<'|'<< setw(12)<<'|'<<setw(15)<<'|'<<setw(16)<<'|'<<endl;
        else cout<<setw(5)<<"mem"<<'|'<<setw(5)<<opcode<<'|'<<setw(8)<<signal<<'|'<<setw(3)<<rs<<'|'<<setw(3)<<rt<<'|'<<setw(3)<<rd
                    <<'|'<<setw(8) <<'|'<<setw(6) <<'|' <<setw(6) <<'|' << setw(11)<<ALUresult<<'|'<<setw(14)<<ReadmemValue<<'|'<<setw(16)<<'|'<<endl;
}