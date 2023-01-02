#include <iostream>
#include <iomanip>
#include "CPU_pipeline.h"

using namespace std;

// Pipelined建構值
// 初始化again, cycle, 記憶體和暫存器
Pipelined::Pipelined(){
    again = false; 
    cycle = 0; 
    reg[0] = 0;
    for(int i=1; i<32; i++){
        reg[i]=1;
    }
    for(int i=0; i<32; i++){
        mem[i]=1;
    }
}

// 開始跑所有指令
// 傳入所有指令
void Pipelined::circle(vector<string> arr){

    // 用index模擬PC的變化
    // 跑array裏element的數量 index為第幾個指令
    for(int index = 0; index < arr.size(); index++){

        // 使用do是，因為在again為false的情況下，至少跑一次
        do{
            if(
                // 當lw, sw，在MEM階段的rt, rd，在ID階段的rs, rt有用到，就要加入stall (MEM hazard)
                (memStage.signal[5] == '1' &&  idStage.opcode !="null" &&
                (idStage.rs == memStage.rt || idStage.rt == memStage.rt || idStage.rt == memStage.rd)) ||
                
                // 當lw, sw，在EX階段的rt, rd，在ID階段的rs, rt有用到，就要加入stall (EX hazard)
                (exStage.signal[5] == '1' && idStage.opcode !="null" &&
                (idStage.rs == exStage.rt || idStage.rt == exStage.rt || idStage.rt == exStage.rd)) || 
                
                // 當sub, add，在MEM階段的rd，在ID階段的rs, rt有用到，就要加入stall (MEM hazard)
                (memStage.signal[6] == '0' &&
                (idStage.rs == memStage.rd || idStage.rt == memStage.rd)) || 

                // 當sub, add，在EX階段的rd，在ID階段的rs, rt有用到，就要加入stall (EX hazard)
                (exStage.signal[6] == '0' &&
                (idStage.rs == exStage.rd || idStage.rt == exStage.rd))
            ){
                
                // MEM的指令進入WB
                wbStage.intoWB(memStage.opcode, memStage.signal, memStage.rs, memStage.rt, memStage.rd, memStage.ALUresult, memStage.ReadmemValue, reg);
                
                // EX的指令進入MEM
                memStage.intoMEM(exStage.opcode, exStage.signal, exStage.rs, exStage.rt, exStage.rd, exStage.ALUresult, exStage.reg2, mem);
                
                // 在EX加入stall，使原本的ID停留在ID，也就是不讓ID的值傳入
                exStage.intoEX("null", "null", -1, -1, -1, -1, -1, -1);
                
                // 讀取ID階段在rs, rt位置的暫存器，因為前面WB會修改
                idStage.readReg(reg);
                
                // 要循環
                again = true;
            }
            // 正常執行
            else{
                
                // MEM的指令進入WB
                wbStage.intoWB(memStage.opcode, memStage.signal, memStage.rs, memStage.rt, memStage.rd, memStage.ALUresult, memStage.ReadmemValue, reg);
                
                // EX的指令進入MEM
                memStage.intoMEM(exStage.opcode, exStage.signal, exStage.rs, exStage.rt, exStage.rd, exStage.ALUresult, exStage.reg2, mem);
                
                // ID的指令進入EX
                exStage.intoEX(idStage.opcode, idStage.signal, idStage.rs, idStage.rt, idStage.rd, idStage.offset, idStage.reg1, idStage.reg2);
                
                // 若ID的opcode是beq，且兩個暫存器相等
                if(idStage.opcode == "beq" && idStage.beq()){
                    // 計算指令要跳到的位置，且讓ID先清空
                    index = index+ idStage.offset-1;
                    vector<string> n;
                    n.push_back("null");
                    idStage.intoID(n, reg);
                }
                // 若否，則IF的指令進入ID
                else idStage.intoID(ifStage.value, reg);

                // 指令進入IF
                ifStage.intoIF(arr[index]);

                // 不用循環
                again = false;
            }

            // 循環加一
            cycle++; 
            
            // 輸出所有結果
            logCycle();
            
        }while(again);
    }
        
}

// 輸出現階段的cycle資料
void Pipelined::logCycle(){

    cout<<"cycle: "<<cycle<<endl;
    cout<<setw(5)<<"stage"<<'|'<<setw(5)<<"op"<<'|'<<setw(8)<<"signal"<<'|'<<setw(3)<<"rs"<<'|'<<setw(3)<<"rt"<<'|'<<setw(3)<<"rd"<<'|'<<setw(7)<<"offset"<<'|'<<setw(5)<<"reg1"<<'|'<<setw(5)<<"reg2"<<'|'<<setw(11)<<"ALUresult"<<'|'<<setw(14)<<"ReadmemValue"<<'|'<<setw(15)<<"RegWriteValue"<<'|'<<endl;
    ifStage.printResult();
    idStage.printResult();
    exStage.printResult();
    memStage.printResult();
    wbStage.printResult();

    cout<<endl;
    cout<<"index|";
    for(int i = 0; i<32; i++){
        cout<<setw(2)<<i<<"|";
    }
    cout<<endl;
    cout<<"reg  |";
    for(int i = 0; i<32; i++){
        cout<<setw(2)<<reg[i]<<"|";
    }
    cout<<endl;
    cout<<"mem  |";
    for(int i = 0; i<32; i++){
        cout<<setw(2)<<mem[i]<<"|";
    }
    cout<<endl;
    cout<<endl;
            
}