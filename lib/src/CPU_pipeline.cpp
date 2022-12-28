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


    // 跑array裏element的數量
    for(int index = 0; index<arr.size(); index++){

        // 使用do是，因為在again為false的情況下，至少跑一次
        do{
            if(
                // 當lw, sw，在MEM階段的rt, rd，在ID階段的rs, rt有用到，就要加入stall
                (memo.signal[5] == '1' &&  ido.opcode !="null" &&
                (ido.rs == memo.rt || ido.rt == memo.rt || ido.rt == memo.rd)) ||
                
                // 當lw, sw，在EX階段的rt, rd，在ID階段的rs, rt有用到，就要加入stall
                (exo.signal[5] == '1' && ido.opcode !="null" &&
                (ido.rs == exo.rt || ido.rt == exo.rt || ido.rt == exo.rd)) || 
                
                // 當sub, add，在MEM階段的rd，在ID階段的rs, rt有用到，就要加入stall
                (memo.signal[6] == '0' &&
                (ido.rs == memo.rd || ido.rt == memo.rd)) || 

                // 當sub, add，在EX階段的rd，在ID階段的rs, rt有用到，就要加入stall
                (exo.signal[6] == '0' &&
                (ido.rs == exo.rd || ido.rt == exo.rd))
            ){
                
                // MEM的指令進入WB
                wbo.intoWB(memo.opcode, memo.signal, memo.rs, memo.rt, memo.rd, memo.ALUresult, memo.ReadmemValue, reg);
                
                // EX的指令進入MEM
                memo.intoMEM(exo.opcode, exo.signal, exo.rs, exo.rt, exo.rd, exo.ALUresult, exo.reg2, mem);
                
                // 在EX加入stall，使原本的ID停留在ID
                exo.intoEX("null", "null", -1, -1, -1, -1, -1, -1);
                
                // 讀取ID階段在rs, rt位置的暫存器
                ido.readReg(reg);
                
                // 要循環
                again = true;
            }
            // 正常執行
            else{
                
                // MEM的指令進入WB
                wbo.intoWB(memo.opcode, memo.signal, memo.rs, memo.rt, memo.rd, memo.ALUresult, memo.ReadmemValue, reg);
                
                // EX的指令進入MEM
                memo.intoMEM(exo.opcode, exo.signal, exo.rs, exo.rt, exo.rd, exo.ALUresult, exo.reg2, mem);
                
                // ID的指令進入EX
                exo.intoEX(ido.opcode, ido.signal, ido.rs, ido.rt, ido.rd, ido.offset, ido.reg1, ido.reg2);
                
                // 若ID的opcode是beq，且兩個暫存器相等
                if(ido.opcode == "beq" && ido.beq()){
                    // 計算指令要跳到的位置，且讓ID先清空
                    index = index+ ido.offset-1;
                    vector<string> n;
                    n.push_back("null");
                    ido.intoID(n, reg);
                }
                // 若否，則IF的指令進入ID
                else ido.intoID(ifo.value, reg);

                // 指令進入IF
                ifo.intoIF(arr[index]);

                // 不用循環
                again = false;
            }

            // 循環加一
            cycle++; 

            // 輸出所有結果
            cout<<"cycle: "<<cycle<<endl;
            cout<<setw(5)<<"stage"<<'|'<<setw(5)<<"op"<<'|'<<setw(8)<<"signal"<<'|'<<setw(3)<<"rs"<<'|'<<setw(3)<<"rt"<<'|'<<setw(3)<<"rd"<<'|'<<setw(7)<<"offset"<<'|'<<setw(5)<<"reg1"<<'|'<<setw(5)<<"reg2"<<'|'<<setw(11)<<"ALUresult"<<'|'<<setw(14)<<"ReadmemValue"<<'|'<<setw(15)<<"RegWriteValue"<<'|'<<endl;
            ifo.printResult();
            ido.printResult();
            exo.printResult();
            memo.printResult();
            wbo.printResult();

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
            
        }while(again);
    }
        
}