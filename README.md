# 2022計組期末專題 - CPU pipeline

## 環境
* Ubuntu 22.04.1 LTS
* Vscode
* C/C++ standard: C11
* C/C++ compiler: g++
> Windows系統可以編譯，但因為cmd指令不同，clean、clean-all無法使用


## 如何使用

> 使用makefile的方式避免編譯環境上的問題，你只需要確保你有開發環境中的編譯器及make的工具 \
> 如果沒有make的工具，在Linux系統的cmd中輸入 
> ```cmd 
> sudo apt install make
> ```


首先，開啟你的bash界面，並輸入以下指令，將此專案下載到本地端

```cmd
cd Desktop
git clone https://github.com/Sunny1928/CO_mid_pipline.git
```
進入 CO_mid_pipline 中，並進行編譯
```cmd
cd CO_mid_pipline
make
```
開始執行
```cmd
#使用預設
./main 

# 放入檔案路徑
./main <file_path>
```
清除所有.o檔，不包含執行檔
```cmd
make clean
```
清除所有.o檔，包含執行檔
```cmd
make clean-all
```

## 專案架構
```
CO-mid_pipline
├── main.cpp
├── Makefile
├── Flow_Chart.png
├── README.md
├── lib
│   ├── include
│   │   ├── CPU_pipeline.h
│   │   ├── EX.h
│   │   ├── ID.h
│   │   ├── IF.h
│   │   ├── MEM.h
│   │   └── WB.h
│   └── src
│       ├── CPU_pipeline.cpp
│       ├── EX.cpp
│       ├── ID.cpp
│       ├── IF.cpp
│       ├── MEM.cpp
│       └── WB.cpp
└── test_data
    ├── q1.txt
    ├── q2.txt
    ├── q3.txt
    ├── q4.txt
    ├── q5.txt
    ├── q6.txt
    ├── q7.txt
    └── q8.txt

```
## 程式流程及主要功能介紹
<img src="https://github.com/Sunny1928/CO_mid_pipline/blob/main/Flow_Chart.png" width = "70%">

#### 撰寫基礎
* 在ID所使用的值為IF/ID register中的值，在EX所用的值為ID/EX register中的值,以此類推。
* 為了方便處理每個regiter都一定會傳入rs,rt,rd和offset，沒有用到的就會填0。
* stall或是目前stage沒有指令，均會填入null做區別。

### 程式可以分成main.cpp、CPU_pipeline.cpp和CPU pipeline的五個階段IF、ID、EX、MEM、WB：

### Main.cpp : 
- 程式的進入點。
- 讀取MIPS指令，並做字串處理將每行指令分開。
### CPU_pipeline.cpp:
- 將記憶體、暫存器與cycle數初始化。
- 使用index模擬PC變化
- 計算花費的cycle數，循環的順序為WB->MEM->EX->ID->IF。
- 判斷EX hazard和MEM hazard情況
### IF:
- 將讀入的指令字串切割，例如讀入add $1,$2,$3,處理後為[add,$1,$2,$3,]
### ID:
- Decode將讀入指令，根據對應的操作轉換成signal，例如：<br>讀到指令lw，轉換成0101011<br>讀到指令add或是sub，轉換成1000010<br>而指令rs,rt,rd或offset，則直接用字串處理取得使用，過程不會轉換成machine code。

- 利用rs, rt取出要使用的暫存器存到reg1, reg2
### EX:
- 根據opcode是add,sub,lw,sw，決定要執行哪種操作(ALUresult)
### MEM:
- 如果MemRead為1，從記憶體對應的位置取出資料，對應的位置為在EX計算完的值。
- 如果MemWrite為1，則將資料寫入記憶體對應的位置，對應的位置為在EX計算完的值。
### WB:
- 如果MemtoReg為1，則從記憶體取出的值，且RegWrite為1，更新到暫存器rt中。
- 如果MemtoReg為0，則把從ALU中計算出的值，且RegWrite為1，更新到暫存器rd中。

## 程式重點

> 更詳細的內容請詳閱程式碼註解！ 

* ### Data Hazard判別
![image](https://user-images.githubusercontent.com/88101776/210197860-c670a2f4-91b8-43f5-9dc1-63d9aadee6e7.png)
* ### Beq 判別，改變PC
![image](https://user-images.githubusercontent.com/88101776/210197894-642fc4f8-d4f9-458a-9c54-51113ec8c48d.png)

## 執行結果
![image](https://user-images.githubusercontent.com/88101776/210249312-6800dd11-4fee-4b46-94d2-cb5da4afdacf.png)


## 遇到問題
1. 指令讀取處理
   * prob: 轉成machine code後，指令在ID階段讀取不方便。
   * sol: 放棄轉成machine code，到ID階段再使用字串切割分割出十進制的值。
2. Data Hazard處理
   * prob 1: 沒有單純做stall的電路架構
   * sol: 參考forwarding的電路架構，使用一樣的EX hazard、MEM hazard的判別方式，但不做提前把值做更新的操作。
   * prob 2:軟體無法模擬硬體的同步執行，導致hazard的判斷無法放在ID階段。
   * sol: 將hazard的判斷留到一個cycle執行完再判斷。


## 分工

在討論完整體架構後，我們將工作分為前半部，架構撰寫包含pipelined的五個階段，後半部為beq和data hazard的判斷及彙整程式碼。會這樣分配的原因是從頭建立架構比較麻煩，所以將較麻煩的stall處理拆出來，順便進行程式碼的檢查並彙整。
其餘的報告、Readme、makefile均為兩人合力討論寫出來的內容。


|Name|工作內容|
| :-----|:-----|
|莊郁誼 | 程式架構設計（前半部）、撰寫、寫報告、Readme、makefile|
|廖怡誠 |程式架構設計(後半部）、撰寫、寫報告、Readme、makefile| 

## Contributors
|Name|Github Link|
| :-----|:-----|
|Yu-Yi Chuang | https://github.com/Sunny1928|
|Yi-Cheng Liao |https://github.com/yeeecheng| 
