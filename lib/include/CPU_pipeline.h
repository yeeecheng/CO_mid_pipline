#ifndef CPU_PIPELINE
#define CPU_PIPELINE

#include "IF.h"
#include "ID.h"
#include "EX.h"
#include "MEM.h"
#include "WB.h"

class Pipelined{
    public:
        IF ifo;
        ID ido;
        EX exo;
        MEM memo;
        WB wbo;
        bool again;
        int reg[32];
        int mem[32];
        int cycle;
        Pipelined();
        void circle(vector<string> arr);
};

#endif