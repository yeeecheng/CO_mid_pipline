#include "MEM.h"

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


MEM::MEM(){
    opcode = "null";
    signal = "null";
    rs = -1;
    rt = -1;
    rd = -1;
    ALUresult = -1;
    ReadmemValue = -1;
}


void MEM::intoMEM(string op, string sig, int s, int t, int d, int aluresult, int wd, int *mem){
    opcode=op;
    rs=s;
    rt=t;
    rd=d;
    ALUresult = aluresult;
    if(opcode == "null") {
        return;
    }
    signal="  "+sig.substr(2,7);
    
    // memory
    if(opcode == "lw"){
        ReadmemValue = mem[ALUresult];
    }else if(opcode == "sw"){
        mem[ALUresult] = wd;
    }
}

void MEM::printResult(){
    if(opcode == "null") cout<<setw(5)<<"mem"<<'|'<<setw(5)<<opcode<<'|'<<setw(9)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(8)<<'|'<<setw(6)<<'|'<<setw(6)<<'|'<< setw(12)<<'|'<<setw(15)<<'|'<<setw(16)<<'|'<<endl;
        else cout<<setw(5)<<"mem"<<'|'<<setw(5)<<opcode<<'|'<<setw(8)<<signal<<'|'<<setw(3)<<rs<<'|'<<setw(3)<<rt<<'|'<<setw(3)<<rd
                    <<'|'<<setw(8) <<'|'<<setw(6) <<'|' <<setw(6) <<'|' << setw(11)<<ALUresult<<'|'<<setw(14)<<ReadmemValue<<'|'<<setw(16)<<'|'<<endl;
}