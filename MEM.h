#ifndef MEM_H
#define MEM_H
#include <string>
using namespace std;

class MEM{
public:
    string opcode;
    string signal;
    int rs;
    int rt;
    int rd;
    int ALUresult;
    int ReadmemValue;

    MEM();
    void intoMEM(string , string , int , int , int , int , int , int *);
    void printResult();
};


#endif