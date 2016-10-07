#include "EightGridPuzzleMap.h"

//g++ -Wall -std=c++11 *.cpp -o test

//g++ -Wall -std=c++11 *.cpp

//g++ -Wall -std=c++11 *.cpp 2>wrong.log 1>&2


extern void GgpMapTest();
extern void TestEgpNode();
extern void TestEgpNodeAddList();
extern void RunTest();


int main(void)
{
    GgpMapTest();
    //TestEgpNode();
    //TestEgpNodeAddList();
    RunTest();
    return 0;
}

