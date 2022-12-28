#ifndef IF_H
#define IF_H

#include <vector>
#include <string>
#include <sstream>
using namespace std;

class IF{
    public:

        // value存指令
        vector<string> value;

        IF();
        void intoIF(string);
        void printResult();
        

};

#endif