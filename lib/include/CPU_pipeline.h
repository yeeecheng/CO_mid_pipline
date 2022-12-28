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
        int reg[32];
        int mem[32];
        // 判斷要不要插入新的指令
        bool again;
        // cycle的數量
        int cycle;
        Pipelined();
        void circle(vector<string> arr);
};

#endif