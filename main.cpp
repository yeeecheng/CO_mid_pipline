#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

static int cycle = 0;

class WB{
public:
    string opcode;
    string signal;
    int rs;
    int rt;
    int rd;
    WB(){
        opcode = "null";
        signal = "null";
        rs = -1;
        rt = -1;
        rd = -1;
    }
    WB(string op, string sig, int s, int t, int d, int *reg){
        opcode=op;
        if(opcode == "null") {
            return;
        }
        signal=sig.substr(3,5);
        rs=s;
        rt=t;
        rd=d;
        if(opcode == "lw"){
            reg[rt] = reg[rs];
        }

    }
    
    void printResult(){
        if(opcode == "null") cout<<setw(5)<<"wb"<<'|'<<setw(5)<<opcode<<'|'<<setw(9)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<endl;
        else cout<<setw(5)<<"wb"<<'|'<<setw(5)<<opcode<<'|'<<setw(8)<<signal<<'|'<<setw(3)<<rs<<'|'<<setw(3)<<rt<<'|'<<setw(3)<<rd<<'|'<<endl;
    }
};

class MEM{
public:
    string opcode;
    string signal;
    int rs;
    int rt;
    int rd;
    MEM(){
        opcode = "null";
        signal = "null";
        rs = -1;
        rt = -1;
        rd = -1;
    }
    MEM(string op, string sig, int s, int t, int d){
        opcode=op;
        if(opcode == "null") {
            return;
        }
        signal=sig.substr(2,7);
        // signal=sig.substr(3,5);
        rs=s;
        rt=t;
        rd=d;
    }
    void printResult(){
        if(opcode == "null") cout<<setw(5)<<"mem"<<'|'<<setw(5)<<opcode<<'|'<<setw(9)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<endl;
        else cout<<setw(5)<<"mem"<<'|'<<setw(5)<<opcode<<'|'<<setw(8)<<signal<<'|'<<setw(3)<<rs<<'|'<<setw(3)<<rt<<'|'<<setw(3)<<rd<<'|'<<endl;
    }
};

class EX{
public:
    string opcode;
    string signal;
    int rs;
    int rt;
    int rd;
    EX(){
        opcode = "null";
        signal = "null";
        rs = -1;
        rt = -1;
        rd = -1;
    }
    EX(string op, string sig, int s, int t, int d, int *reg){
        opcode=op;
        if(opcode == "null") {
            return;
        }
        // signal=sig.substr(2,7);
        signal = sig;
        rs=s;
        rt=t;
        rd=d;

        if(opcode == "add"){
            reg[rd] = reg[rs]+reg[rt];
        }else if(opcode == "sub"){
            reg[rd] = reg[rs]-reg[rt];
        }

    }

    void printResult(){
        if(opcode == "null") cout<<setw(5)<<"ex"<<'|'<<setw(5)<<opcode<<'|'<<setw(9)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<endl;
        else cout<<setw(5)<<"ex"<<'|'<<setw(5)<<opcode<<'|'<<setw(8)<<signal<<'|'<<setw(3)<<rs<<'|'<<setw(3)<<rt<<'|'<<setw(3)<<rd<<endl;
    }
};

class ID{
public:
    ID(){
        opcode = "null";
        signal = "null";
        rs = -1;
        rt = -1;
        rd = -1;
    }
    ID(vector<string> o){
        opcode=o[0];
        if(opcode == "null") {
            return;
        }
        signal="";
        rs=0;
        rt=0;
        rd=0;
        offset=0;

        // cout<< o[0]<<endl;
        if(opcode == "lw"){
            signal = "0101011";
            rt = stoi(o[1].substr(o[1].find('$')+1, o[1].find(',')));
            rs = stoi(o[2].substr(o[2].find('$')+1, o[2].find(')')));
            offset = stoi(o[2].substr(0, o[2].find('(')));
        }
        else if(opcode == "sw"){
            signal = "x10010x";
            rt = stoi(o[1].substr(o[1].find('$')+1, o[1].find(',')));
            rs = stoi(o[2].substr(o[2].find('$')+1, o[2].find(')')));
            offset = stoi(o[2].substr(0, o[2].find('(')));
        }
        else if(opcode == "add" || opcode == "sub"){
            signal = "1000010";
            rd = stoi(o[1].substr(o[1].find('$')+1, o[1].find(',')));
            rs = stoi(o[2].substr(o[2].find('$')+1, o[2].find(',')));
            rt = stoi(o[3].substr(o[3].find('$')+1, o[3].length()));
        }
        else if(opcode == "beq"){
            signal = "x01000x";
            rs = stoi(o[1].substr(o[1].find('$')+1, o[1].find(',')));
            rt = stoi(o[2].substr(o[2].find('$')+1, o[2].length()));
            offset = stoi(o[3]);
            cout<<offset;
        }

    }

    void printResult(){
        if(opcode == "null") cout<<setw(5)<<"id"<<'|'<<setw(5)<<opcode<<'|'<<setw(9)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<setw(4)<<'|'<<endl;
        else cout<<setw(5)<<"id"<<'|'<<setw(5)<<opcode<<'|'<<setw(8)<<signal<<'|'<<setw(3)<<rs<<'|'<<setw(3)<<rt<<'|'<<setw(3)<<rd<<'|'<<endl;
    }
    string opcode;
    string signal;
    int rs;
    int rt;
    int rd;
    int offset;
};

class IF{
public:
    vector<string> value;
    IF(){
        value.push_back("null");
    }

    IF(string s){
        while (1) {
            value.push_back(s.substr(0, s.find(" "))); 
            s = s.substr(s.find(" ") + 1, s.length()); 

            if (s.find(" ") == -1) {
                value.push_back(s);
                break;
            }
        }
    }

    void printResult(){
        cout<<setw(5)<<"if"<<'|'<<setw(5);
        for (auto& ret : value){
            cout<<ret;
        }
        cout<<endl;
    }
};

class Pipelined{
public:
    IF ifo;
    ID ido;
    EX exo;
    MEM memo;
    WB wbo;
    bool again;
    int reg[32];

    Pipelined(){
        again = false;
        reg[0] = 0;
        for(int i=1; i<32; i++){
            reg[i]=1;
        }
    }
    // RegDst ALUSrc Branch MemRead MemWrite RegWrite MemtoReg
    void circle(IF new_ifo){
        
        do{
            ID new_ido(ifo.value);
            EX new_exo(ido.opcode, ido.signal, ido.rs, ido.rt, ido.rd, reg);
            MEM new_memo(exo.opcode, exo.signal, exo.rs, exo.rt, exo.rd);
            WB new_wbo(memo.opcode, memo.signal, memo.rs, memo.rt, memo.rd, reg);

            // sw, lw in mem 00010
            if(memo.signal[3] == '1' && 
                (ido.rs == memo.rt || ido.rt == memo.rt || ido.rt == memo.rd)){
                exo = EX();
                memo = new_memo;
                wbo = new_wbo;
                again = true;
            }
            // sw, lw in ex 1000010
            else if(exo.signal[5] == '1' && 
                (ido.rs == exo.rt || ido.rt == exo.rt || ido.rt == exo.rd)){
                exo = EX();
                memo = new_memo;
                wbo = new_wbo;
                again = true;
            }
            else{
                ifo = new_ifo;
                ido = new_ido;
                exo = new_exo;
                memo = new_memo;
                wbo = new_wbo;
                again = false;
            }

            cycle++;
            cout<<"cycle: "<<cycle<<endl;
            cout<<setw(5)<<"stage"<<'|'<<setw(5)<<"op"<<'|'<<setw(8)<<"signal"<<'|'<<setw(3)<<"rs"<<'|'<<setw(3)<<"rt"<<'|'<<setw(3)<<"rd"<<'|'<<endl;
            ifo.printResult();
            ido.printResult();
            exo.printResult();
            memo.printResult();
            wbo.printResult();
            for(int i = 0; i<10; i++){
                cout<<reg[i]<<' ';
            }
            cout<<endl;
            cout<<endl;
            
        }while(again);

        
    }
};

int main(){
    ifstream ifs("q1.txt",ios::in);
    if(!ifs.is_open()){
        cout<<"fail to open this file"<<endl;
        return 1;
    }

    stringstream ss;
    ss << ifs.rdbuf();
    string str(ss.str());
    string s;
    ifs.close();

    Pipelined pipe;

    while(getline(ss, s)){
        // cout<<s;
        IF ifo(s);
        pipe.circle(ifo);
    }

    for(int i=0; i<4; i++){
        IF ifo;
        pipe.circle(ifo);
    }
    return 0;
}