#ifndef WB_H
#define WB_H

#include <string>
using namespace std;

class WB{
public:
    string opcode;
    string signal;
    int rs;
    int rt;
    int rd;
    int RegWriteValue;

    WB();
    void intoWB(string, string, int, int, int, int, int, int *);
    void printResult();

};


#endif