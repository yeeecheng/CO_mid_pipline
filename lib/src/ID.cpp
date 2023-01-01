#include <iostream>
#include "ID.h"
#include <iomanip>
using namespace std;

// ID建構值，初始化opcode, signal, rs, rt, rd, offset, reg1, reg2
ID::ID(){
    opcode = "null";
    signal = "null";
    rs = -1;
    rt = -1;
    rd = -1;
    offset = -1;
    reg1 = -1;
    reg2 = -1;
}

// 進入ID
// 傳IF的指令vector和暫存器進入ID
void ID::intoID(vector<string> o, int *reg){

    // 第一個vector是opcode
    opcode=o[0];

    // 若opcode是null，則結束ID程序
    if(opcode == "null") {
        return;
    }

    // 若opcode不是null，則處理字串
    // 存入ID對應到的變數中
    signal="";
    rs=0;
    rt=0;
    rd=0;
    offset=0;

    // 指令解碼
    this->decode(o);

    // 讀完 rt, rs後，會再去讀對應到的暫存器
    this->readReg(reg);
}

void ID::decode(vector<string> o){
    // 若opcode是lw，signal會是0101011
    // 其指令會是lw rt, offset(rs)的形式，處理字串存入對應到的變數
    if(opcode == "lw"){
        signal = "0101011";
        rt = stoi(o[1].substr(o[1].find('$')+1, o[1].find(',')));
        rs = stoi(o[2].substr(o[2].find('$')+1, o[2].find(')')));
        offset = stoi(o[2].substr(0, o[2].find('(')));
    }
    // 若opcode是sw，signal會是x10010x
    // 其指令會是sw $rt, offset($rs)的形式，處理字串存入對應到的變數
    else if(opcode == "sw"){
        signal = "x10010x";
        rt = stoi(o[1].substr(o[1].find('$')+1, o[1].find(',')));
        rs = stoi(o[2].substr(o[2].find('$')+1, o[2].find(')')));
        offset = stoi(o[2].substr(0, o[2].find('(')));
    }
    // 若opcode是add或sub，signal會是1000010
    // 其指令會是add $rd, $rs, $rt的形式處理字串存入對應到的變數
    else if(opcode == "add" || opcode == "sub"){
        signal = "1000010";
        rd = stoi(o[1].substr(o[1].find('$')+1, o[1].find(',')));
        rs = stoi(o[2].substr(o[2].find('$')+1, o[2].find(',')));
        rt = stoi(o[3].substr(o[3].find('$')+1, o[3].length()));
    }
    // 若opcode是beq，signal會是x01000x
    // 其指令會是add $rs, $rt, offset的形式，處理字串存入對應到的變數
    else if(opcode == "beq"){
        signal = "x01000x";
        rs = stoi(o[1].substr(o[1].find('$')+1, o[1].find(',')));
        rt = stoi(o[2].substr(o[2].find('$')+1, o[2].length()));
        offset = stoi(o[3]);
    }

    

}

// 使用rs, rt讀取暫存器
void ID::readReg(int*reg){
    reg1 = reg[rs];
    reg2 = reg[rt];
}

// 判斷兩個暫存器是否一樣
bool ID::beq(){
    return reg1 == reg2;
}

// 輸出ID的結果
// 也就是opcode, siginal, rs, rt, rd, offset, reg1, reg2的值
void ID::printResult(){
    if(opcode == "null") cout<<setw(5)<<"id"<<'|'<<setw(5)<<opcode<<'|'<<setw(9)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(8)<<'|'<<setw(6)<<'|'<<setw(6)<<'|'<< setw(12)<<'|'<<setw(15)<<'|'<<setw(16)<<'|'<<endl;
        else cout<<setw(5)<<"id"<<'|'<<setw(5)<<opcode<<'|'<<setw(8)<<signal<<'|'<<setw(3)<<rs<<'|'<<setw(3)<<rt<<'|'<<setw(3)<<rd<<'|'<<setw(7)<<offset<<'|'<<setw(5)<<reg1<<'|'<<setw(5)<<reg2<<'|'<<setw(12) <<'|'<<setw(15) <<'|'<<setw(16) <<'|'<<endl;
}