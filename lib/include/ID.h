#ifndef ID_H
#define ID_H

#include <vector>
#include <string>
#include <sstream>
using namespace std;


class ID{
    
    public:
        
        ID();
        void intoID(vector<string>, int *);
        void decode(vector<string>);
        void readReg(int *);
        bool beq();
        void printResult();
        
        
        // opcode是指令
        string opcode;
        // signal是由 RegDst, ALUSrc,　Branch, MemRead, MemWrite,　RegWrite, MemtoReg組成的
        string signal;
        int rs;
        int rt;
        int rd;
        int offset;
        int reg1;
        int reg2;


};


#endif  