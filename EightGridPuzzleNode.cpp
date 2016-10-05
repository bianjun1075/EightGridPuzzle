#include <assert.h>
#include "EightGridPuzzleNode.h"

void TestGgpNode()
{
    char acTestMap[] = 
    {
        "123"
        "456"
        "78 "
    };

    char acTestMapC[] = 
    {
        "78 "
        "123"
        "456"
    };

    try{
        EgpMap<char, 9> objEgpMapA(acTestMap, 3, 3);

        EgpMap<char, 9> objEgpMapC(acTestMapC, 3, 3);

        EgpNode objEgpNodeA(objEgpMapA, 0, 0);
        EgpNode objEgpNodeB(objEgpNodeA);

        EgpNode objEgpNodeC(objEgpMapC, 2, 2);
        EgpNode objEgpMapD = objEgpNodeC;

        assert(objEgpNodeA == objEgpNodeB);
        assert(!(objEgpNodeA == objEgpNodeC));
        assert(objEgpNodeC == objEgpMapD);

        objEgpNodeA.Show();
        objEgpNodeC.Show();

        objEgpNodeA.CalcFn(NULL, &objEgpMapC);
        assert(0 == objEgpNodeA.GetHn());
        assert(9 == objEgpNodeA.GetGn());
        assert(9 == objEgpNodeA.GetFn());

        objEgpNodeA.CalcFn(NULL, &objEgpMapC);
        assert(0 == objEgpNodeA.GetHn());
        assert(9 == objEgpNodeA.GetGn());
        assert(9 == objEgpNodeA.GetFn());

        objEgpNodeA.CalcFn(&objEgpNodeA, &objEgpMapC);
        assert(0 == objEgpNodeA.GetHn());
        assert(9 == objEgpNodeA.GetGn());
        assert(9 == objEgpNodeA.GetFn());

        objEgpNodeC.CalcFn(&objEgpNodeA, &objEgpMapC);
        assert(1 == objEgpNodeC.GetHn());
        assert(0 == objEgpNodeC.GetGn());
        assert(1 == objEgpNodeC.GetFn());
    }
    catch(const char *expInfo)
    {
        cout << expInfo << endl;
        cout << "TestGgpNode failed!" << endl;
        return;
    }
    
    cout << "TestGgpNode success!" << endl;
}
