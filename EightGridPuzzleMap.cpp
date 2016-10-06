#include <assert.h>

#include "EightGridPuzzleMap.h"

void GgpMapTest()
{
    char acTestMap[] = 
    {
        "123"
        "456"
        "78 "
    };

    char acTestMapB[] = 
    {
        "78 "
        "123"
        "456"
    };

    try{
        EgpMap<char, 9> objEgpMapA(acTestMap, 3, 3);

        EgpMap<char, 9> objEgpMapB(3, 3);

        EgpMap<char, 9> objEgpMapC(objEgpMapA);

        EgpMap<char, 9> objEgpMapD(acTestMapB, 3, 3);

        assert(objEgpMapA == objEgpMapC);
        assert(!(objEgpMapA == objEgpMapB));

        objEgpMapB = objEgpMapA;
        assert(objEgpMapA == objEgpMapB);

        assert(3 == objEgpMapA.GetHeight());
        assert(3 == objEgpMapA.GetWidth());

        assert('1' == objEgpMapA.GetEle(0, 0));
        assert(' ' == objEgpMapA.GetEle(2, 2));
        assert('6' == objEgpMapA.GetEle(2, 1));
        assert('5' == objEgpMapA.GetEle(1, 1));

        assert('1' == objEgpMapB.GetEle(0, 0));
        assert(' ' == objEgpMapB.GetEle(2, 2));
        assert('6' == objEgpMapB.GetEle(2, 1));
        assert('5' == objEgpMapB.GetEle(1, 1));

        objEgpMapA.SetEle(0, 0, '7');

        assert('7' == objEgpMapA.GetEle(0, 0));
        assert('7' == objEgpMapA.GetEle(0, 2));

        objEgpMapA.SetEle(0, 2, '1');
        assert('7' == objEgpMapA.GetEle(0, 0));
        assert('1' == objEgpMapA.GetEle(0, 2));

        assert('1' == objEgpMapC.GetEle(0, 0));
        assert(' ' == objEgpMapC.GetEle(2, 2));
        assert('6' == objEgpMapC.GetEle(2, 1));
        assert('5' == objEgpMapC.GetEle(1, 1));

        assert(2 == (objEgpMapA - objEgpMapB));
        assert(0 == (objEgpMapB - objEgpMapC));

        assert(9 == (objEgpMapB - objEgpMapD));

        assert(3 == objEgpMapC.GetHeight());
        assert(3 == objEgpMapC.GetWidth());

        //cout << "--------------------------" << endl;
        EgpMap<char, 9> objEgpMapE = objEgpMapA;
        //cout << "--------------------------" << endl;
        assert(3 == objEgpMapE.GetHeight());
        assert(3 == objEgpMapE.GetWidth());
    }
    catch(const char* expInfo)
    {
        cout << expInfo << endl;
        cout << "GgpMapTest Failed!" << endl;
        return ;
    }

    cout << "GgpMapTest success!" << endl;
}

