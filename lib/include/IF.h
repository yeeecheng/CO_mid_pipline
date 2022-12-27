#ifndef IF_H
#define IF_H

#include <vector>
#include <string>
#include <sstream>
using namespace std;

class IF{
    public:

        IF();
        void intoIF(string);
        void printResult();
        // value存指令
        vector<string> value;

};

#endif