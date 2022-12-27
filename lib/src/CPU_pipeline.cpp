#include <iostream>
#include <iomanip>
#include "CPU_pipeline.h"

using namespace std;

Pipelined::Pipelined(){
    again = false;
    reg[0] = 0;
    for(int i=1; i<32; i++){
        reg[i]=1;
    }
    for(int i=0; i<32; i++){
        mem[i]=1;
    }
}


void Pipelined::circle(vector<string> arr){

    cycle = 0;

    for(int index = 0; index<arr.size(); index++){

        do{
            if(memo.signal[5] == '1' &&  ido.opcode !="null" &&
                (ido.rs == memo.rt || ido.rt == memo.rt || ido.rt == memo.rd)){

                wbo.intoWB(memo.opcode, memo.signal, memo.rs, memo.rt, memo.rd, memo.ALUresult, memo.ReadmemValue, reg);
                memo.intoMEM(exo.opcode, exo.signal, exo.rs, exo.rt, exo.rd, exo.ALUresult, exo.reg2, mem);
                exo.intoEX("null", "null", -1, -1, -1, -1, -1, -1);
                ido.readReg(reg);
                again = true;

            }
            // sw, lw in ex 1000010
            else if(exo.signal[5] == '1' && ido.opcode !="null" &&
                (ido.rs == exo.rt || ido.rt == exo.rt || ido.rt == exo.rd)){
                    // cout<<"s2"<<endl;
                wbo.intoWB(memo.opcode, memo.signal, memo.rs, memo.rt, memo.rd, memo.ALUresult, memo.ReadmemValue, reg);
                memo.intoMEM(exo.opcode, exo.signal, exo.rs, exo.rt, exo.rd, exo.ALUresult, exo.reg2, mem);
                exo.intoEX("null", "null", -1, -1, -1, -1, -1, -1);
                ido.readReg(reg);
                again = true;

            }
            // sub add
            else if(memo.signal[6] == '0' &&
                (ido.rs == memo.rd || ido.rt == memo.rd)){
                
                wbo.intoWB(memo.opcode, memo.signal, memo.rs, memo.rt, memo.rd, memo.ALUresult, memo.ReadmemValue, reg);
                memo.intoMEM(exo.opcode, exo.signal, exo.rs, exo.rt, exo.rd, exo.ALUresult, exo.reg2, mem);
                exo.intoEX("null", "null", -1, -1, -1, -1, -1, -1);
                ido.readReg(reg);
                again = true;

            }
            else if(exo.signal[6] == '0' &&
                (ido.rs == exo.rd || ido.rt == exo.rd)){
                
                    wbo.intoWB(memo.opcode, memo.signal, memo.rs, memo.rt, memo.rd, memo.ALUresult, memo.ReadmemValue, reg);
                    memo.intoMEM(exo.opcode, exo.signal, exo.rs, exo.rt, exo.rd, exo.ALUresult, exo.reg2, mem);
                    exo.intoEX("null", "null", -1, -1, -1, -1, -1, -1);
                    ido.readReg(reg);
                    again = true;

            }
            else{
        
                wbo.intoWB(memo.opcode, memo.signal, memo.rs, memo.rt, memo.rd, memo.ALUresult, memo.ReadmemValue, reg);
                memo.intoMEM(exo.opcode, exo.signal, exo.rs, exo.rt, exo.rd, exo.ALUresult, exo.reg2, mem);
                exo.intoEX(ido.opcode, ido.signal, ido.rs, ido.rt, ido.rd, ido.offset, ido.reg1, ido.reg2);
                
                if(ido.opcode == "beq" && ido.beq()){
            
                    ido.readReg(reg);
                    index = index+ ido.offset-1;
                    vector<string> n;
                    n.push_back("null");
                    ido.intoID(n, reg);
                    
                }
                else ido.intoID(ifo.value, reg);
                ifo.intoIF(arr[index]);
                again = false;
            }

            cycle++;
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