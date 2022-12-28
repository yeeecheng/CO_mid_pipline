#ifndef EX_H
#define EX_H

#include <iomanip>
#include <string>
using namespace std;

class EX{

    public:
        
        EX();
        void intoEX(string, string, int, int, int, int, int, int);
        void printResult();
        
        string opcode;
        string signal;
        int rs;
        int rt;
        int rd;
        int reg1;
        int reg2;
        int ALUresult;
        int offset;

    
};




#endif