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
    }
    catch(const char *expInfo)
    {
        cout << expInfo << endl;
        cout << "TestGgpNode failed!" << endl;
        return;
    }
    
    cout << "TestGgpNode success!" << endl;
}
