#ifndef ID_H
#define ID_H

#include <vector>
#include <string>
#include <sstream>
using namespace std;

class ID{
    
    public:
        string opcode;
        string signal;
        int rs;
        int rt;
        int rd;
        int offset;

        int reg1;
        int reg2;

        ID();
        void intoID(vector<string>, int *);
        void readReg(int *);
        bool beq();
        void printResult();

};


#endif  