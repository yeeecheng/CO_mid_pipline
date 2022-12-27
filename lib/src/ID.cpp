#include <iostream>
#include "ID.h"
#include <iomanip>
using namespace std;

ID::ID(){
    opcode = "null";
    signal = "null";
    rs = -1;
    rt = -1;
    rd = -1;
    reg1 = -1;
    reg2 = -1;
}

void ID::intoID(vector<string> o, int *reg){
    opcode=o[0];
    if(opcode == "null") {
        return;
    }
    signal="";
    rs=0;
    rt=0;
    rd=0;
    offset=0;
    if(opcode == "lw"){
        signal = "0101011";
        rt = stoi(o[1].substr(o[1].find('$')+1, o[1].find(',')));
        rs = stoi(o[2].substr(o[2].find('$')+1, o[2].find(')')));
        offset = stoi(o[2].substr(0, o[2].find('(')));
        this->readReg(reg);
    }
    else if(opcode == "sw"){
        signal = "x10010x";
        rt = stoi(o[1].substr(o[1].find('$')+1, o[1].find(',')));
        rs = stoi(o[2].substr(o[2].find('$')+1, o[2].find(')')));
        offset = stoi(o[2].substr(0, o[2].find('(')));
        this->readReg(reg);

    }
    else if(opcode == "add" || opcode == "sub"){
        signal = "1000010";
        rd = stoi(o[1].substr(o[1].find('$')+1, o[1].find(',')));
        rs = stoi(o[2].substr(o[2].find('$')+1, o[2].find(',')));
        rt = stoi(o[3].substr(o[3].find('$')+1, o[3].length()));
        this->readReg(reg);
    }
    else if(opcode == "beq"){
        signal = "x01000x";
        rs = stoi(o[1].substr(o[1].find('$')+1, o[1].find(',')));
        rt = stoi(o[2].substr(o[2].find('$')+1, o[2].length()));
        offset = stoi(o[3]);
        this->readReg(reg);
    }
}

void ID::readReg(int*reg){
    if(opcode == "lw"){
        reg1 = reg[rs];
    }else{
        reg1 = reg[rs];
        reg2 = reg[rt];
    }
}

bool ID::beq(){
    
    return reg1 == reg2;
}

void ID::printResult(){
    if(opcode == "null") cout<<setw(5)<<"id"<<'|'<<setw(5)<<opcode<<'|'<<setw(9)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(8)<<'|'<<setw(6)<<'|'<<setw(6)<<'|'<< setw(12)<<'|'<<setw(15)<<'|'<<setw(16)<<'|'<<endl;
        else cout<<setw(5)<<"id"<<'|'<<setw(5)<<opcode<<'|'<<setw(8)<<signal<<'|'<<setw(3)<<rs<<'|'<<setw(3)<<rt<<'|'<<setw(3)<<rd<<'|'<<setw(7)<<offset<<'|'<<setw(5)<<reg1<<'|'<<setw(5)<<reg2<<'|'<<setw(12) <<'|'<<setw(15) <<'|'<<setw(16) <<'|'<<endl;
}