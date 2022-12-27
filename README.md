# 2022計組期末專題 - CPU pipeline (沒有forwading版本）

## 如何使用
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
./main file_path
```

## 專案架構
```CO-mid_pipline
│   README.md
│   main.cpp
│   Makefile
│
└───lib
│   │
│   └───include
│   │   │   file111.txt
│   │   │   file112.txt
│   │   │   ...
│
│
└───folder2
    │   file021.txt
    │   file022.txt
```
