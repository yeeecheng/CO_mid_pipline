CC = g++
# -Wall 輸出編譯錯誤指令 , -std=c++11 用此進行編譯 , 
# -I ./lib/include 將此目錄加入搜尋路徑中
CFLAGS = -Wall -std=c++11 -I./lib/include
# 需要編譯的.cpp檔 , wildcard 是找出 lib/src下所以的.cpp檔
SOURCES = main.cpp $(wildcard lib/src/*.cpp)
# 將SOURCES中的lib/src/%.cpp 改成 build/%.o
OBJECTS = $(SOURCES:lib/src/%.cpp=build/%.o)
# 生成執行檔名稱
EXECUTABLE = main
# .o檔存的地方
OBJ_DIR = build

# 開始執行的地方
all: $(EXECUTABLE) 
	@echo "successfully built $(EXECUTABLE)"

# 生成 $(EXECUTABLE)檔 要執行的指令 ,為main
# $@ 為目標檔 , 為main
# g++ -Wall -std=c++11 -I./lib/include main.o **.cpp -o  main 
$(EXECUTABLE): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $@

# 將.cpp編譯成.o
# $< 依賴檔(:後) , $@ 目標檔(:前)
# g++ -Wall -std=c++11 -I./lib/include -c %.cpp -o %.o
build/%.o: lib/src/%.cpp | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

#其他指令 
.PHONY:  clean clean-all
# make clean 清除掉 build/中 全部的.o 檔
clean:
	@rm -rf $(OBJ_DIR)
	@echo "successfully remove all obj files"
# make clean 清除掉 build/中 全部的.o 檔 和 執行檔
clean-all: clean
	@rm $(EXECUTABLE)
	@echo "successfully remove .exe"
	