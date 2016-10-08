#include <assert.h>
#include <algorithm>
#include <memory>

#include "EightGridPuzzleNode.h"

void EgpNode::AddNextPossStepsToList(vector<EgpNode>& vcOpenList, vector<EgpNode>& vcClosedList)
{
    vector<EgpNode> vcNextPossSteps;

    if (m_ulY >= 1)
    {
        EgpMap<char, 9> objNextMap(m_objEgpMap);
        objNextMap.SetEle(m_ulX, m_ulY - 1, m_objEgpMap.GetEle(m_ulX, m_ulY));
        objNextMap.SetEle(m_ulX, m_ulY, m_objEgpMap.GetEle(m_ulX, m_ulY - 1));
        
        EgpNode objUpNode(objNextMap, m_ulX, m_ulY - 1);
        objUpNode.CalcFn(this, m_pEgpMap);

        AddNodeToList(objUpNode, vcOpenList, vcClosedList);
    }

    if (m_ulY + 1 < m_objEgpMap.GetHeight())
    {
        EgpMap<char, 9> objNextMap(m_objEgpMap);
        objNextMap.SetEle(m_ulX, m_ulY + 1, m_objEgpMap.GetEle(m_ulX, m_ulY));
        objNextMap.SetEle(m_ulX, m_ulY, m_objEgpMap.GetEle(m_ulX, m_ulY + 1));
        
        EgpNode objUpNode(objNextMap, m_ulX, m_ulY + 1);
        objUpNode.CalcFn(this, m_pEgpMap);

        AddNodeToList(objUpNode, vcOpenList, vcClosedList);
    }

    if (m_ulX >= 1)
    {
        EgpMap<char, 9> objNextMap(m_objEgpMap);
        objNextMap.SetEle(m_ulX - 1, m_ulY, m_objEgpMap.GetEle(m_ulX, m_ulY));
        objNextMap.SetEle(m_ulX, m_ulY, m_objEgpMap.GetEle(m_ulX - 1, m_ulY));
        
        EgpNode objUpNode(objNextMap, m_ulX - 1, m_ulY);
        objUpNode.CalcFn(this, m_pEgpMap);

        AddNodeToList(objUpNode, vcOpenList, vcClosedList);
    }

    if (m_ulX + 1 < m_objEgpMap.GetWidth())
    {
        EgpMap<char, 9> objNextMap(m_objEgpMap);
        objNextMap.SetEle(m_ulX + 1, m_ulY, m_objEgpMap.GetEle(m_ulX, m_ulY));
        objNextMap.SetEle(m_ulX, m_ulY, m_objEgpMap.GetEle(m_ulX + 1, m_ulY));
        
        EgpNode objUpNode(objNextMap, m_ulX + 1, m_ulY);
        objUpNode.CalcFn(this, m_pEgpMap);

        AddNodeToList(objUpNode, vcOpenList, vcClosedList);
    }
}

void EgpNode::AddNodeToList(EgpNode objEgpNode, vector<EgpNode>& vcOpenList, vector<EgpNode>& vcClosedList)
{
    if (!objEgpNode.IsInList(vcClosedList))
    {
        bool isInOpenList = false;
        for (auto &i : vcOpenList)
        {
            if (objEgpNode.IsMapEqualTo(i))
            {
                isInOpenList = true;
                //break;
                if (this != i.GetPreNode())
                {
                    //EgpNode objTempNode(i);
                    //objTempNode.CalcFn(this, m_pEgpMap);
                    if (objEgpNode.GetFn() <= i.GetFn())
                    {
                        i.CalcFn(this, m_pEgpMap);
                        assert(i == objEgpNode);
                    }
                    else
                    {
                        assert(objEgpNode.GetFn() > i.GetFn());
                    }
                }                    
            }
        }
    
        if (!isInOpenList)
        {
            vcOpenList.push_back(objEgpNode);
        }
    }
}

void TestEgpNode()
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

        //objEgpNodeA.Show();
        //objEgpNodeC.Show();

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
        cout << "TestEgpNode failed!" << endl;
        return;
    }
    
    cout << "TestEgpNode success!" << endl;
}

void TestEgpNodeAddList()
{
    char acTestMapEnd[] = 
    {
        "123"
        "456"
        "78 "
    };

    char acTestMapStart[] = 
    {
        "782"
        "1 3"
        "456"
    };

    try{
        EgpMap<char, 9> objEgpMapEnd(acTestMapEnd, 3, 3);
        EgpMap<char, 9> objEgpMapStart(acTestMapStart, 3, 3);

        vector<EgpNode> vcOpenList;
        vector<EgpNode> vcClosedList;

        EgpNode objEgpNodeStart(objEgpMapStart, 1, 1);

        objEgpNodeStart.CalcFn(NULL, &objEgpMapEnd);

        objEgpNodeStart.AddNextPossStepsToList(vcOpenList, vcClosedList);

        assert(vcOpenList.size() == 4);
        assert(vcClosedList.size() == 0);

        for (auto i : vcOpenList)
        {
            i.Show();
        }
    }
    catch(const char *expInfo)
    {
        cout << expInfo << endl;
        cout << "TestEgpNodeAddList failed!" << endl;
        return;
    }

    cout << "TestEgpNodeAddList success!" << endl;
}

void ParseSolution(const EgpNode & objEgpNode)
{
    vector<EgpNode> vcSolution;

    EgpNode objStepNode = objEgpNode;

    //vcSolution.push_back(objStepNode);

    int i = 0;
    do
    {
        //objStepNode.Show();
        vcSolution.push_back(objStepNode);
        //cout << "ParseSolution: objStepNode.GetPreNode() = " << objStepNode.GetPreNode() << endl;
        //(objStepNode.GetPreNode())->Show();
        //cout << &objStepNode << endl;
        objStepNode = *(objStepNode.GetPreNode()); 
    }while ((NULL != objStepNode.GetPreNode()) && (i++ < 30));

    cout << "ParseSolution Success!Solution len = " << vcSolution.size() << endl;
}

void RunTest()
{
    char acTestMapEnd[] = 
    {
        "123"
        "456"
        "78*"
    };

    #if 0
    char acTestMapStart[] = 
    {
        "782"
        "1*3"
        "456"
    };
    #elif 0
    char acTestMapStart[] = 
    {
        "128"
        "4*5"
        "763"
    };
    #else
    char acTestMapStart[] = 
    {
        "368"
        "742"
        "1*5"
    };
    #endif

    try{
        EgpMap<char, 9> objEgpMapEnd(acTestMapEnd, 3, 3);
        EgpMap<char, 9> objEgpMapStart(acTestMapStart, 3, 3);

        vector<EgpNode> vcOpenList;
        vector<EgpNode> vcClosedList;
        vector<EgpNode> vcExistList(10000);

        //EgpNode objEgpNodeEnd(objEgpMapEnd, 2, 2);
        EgpNode objEgpNodeStart(objEgpMapStart, 1, 1);

        objEgpNodeStart.CalcFn(NULL, &objEgpMapEnd);

        vcOpenList.push_back(objEgpNodeStart);

        int iStopCnt = 0;
        while ((vcOpenList.size() > 0) && (iStopCnt++ < 10000))
        //while ((vcOpenList.size() > 0))
        {   
            //EgpNode objEgpNode = vcOpenList.at(0);
            //shared_ptr<EgpNode> pobjEgpNode(new EgpNode(vcOpenList.at(0)));
            //EgpNode *pobjEgpNode = new EgpNode(vcOpenList.at(0));
            vcExistList.push_back(vcOpenList.at(0));
            EgpNode *pobjEgpNode = &vcExistList.back();
 
            cout << "=====" << iStopCnt << ", " << vcOpenList.size() << "=====" << endl;
            cout << "chose ";
            //cout << "pobjEgpNode: " << pobjEgpNode << endl;
            pobjEgpNode->Show();

            /*if ((32 == iStopCnt) || (33 == iStopCnt))
            {
                cout << "something wrong" << endl;
                vcExistList[iStopCnt - 2].Show();
                vcExistList[iStopCnt - 1].Show();
                cout << "find something?" << endl;
            }*/
            
            if (pobjEgpNode->IsMapEqualTo(objEgpMapEnd))
            {
                cout << "Good!Got a solution!" << endl;
                cout << "OpenList size = " << vcOpenList.size() << endl;
                cout << "ClosedList size = " << vcClosedList.size() << endl;
                cout << "ExistList size = " << vcExistList.size() << endl;
                /*for (auto &i : vcExistList)
                {
                    cout << &i << ", " << i.GetPreNode() << endl;
                    i.Show();
                }*/
                ParseSolution(*pobjEgpNode);
                return;
            }
            
            pobjEgpNode->AddNextPossStepsToList(vcOpenList, vcClosedList);
            vcOpenList.erase(vcOpenList.begin());
            vcClosedList.push_back(*pobjEgpNode);
            
            sort(vcOpenList.begin(), vcOpenList.end());

            #if 0
            cout << "----------vcOpenList--------->" << endl;
            for (auto i : vcClosedList)
            {
                i.Show();
            }
            cout << "<---------vcOpenList----------" << endl;
            #endif

            #if 1
            /*cout << "----------vcClosedList--------->" << endl;
            for (auto i : vcClosedList)
            {
                //(*(i.GetPreNode())).Show();
                cout << "PreNode: " << i.GetPreNode() << endl;
                i.Show();
            }
            cout << "<---------vcClosedList----------" << endl;*/
            #endif
            
        }

        #if 0
        cout << "----------vcExistList--------->" << endl;
        for (auto &i : vcExistList)
        {
            cout << &i << ", " << i.GetPreNode() << endl;
            i.Show();
        }
        cout << "<----------vcExistList---------" << endl;
        #endif

        /*objEgpNodeStart.AddNextPossStepsToList(vcOpenList, vcClosedList);

        assert(vcOpenList.size() == 4);
        assert(vcClosedList.size() == 0);

        for (auto i : vcOpenList)
        {
            i.Show();
        }*/
    }
    catch(const char *expInfo)
    {
        cout << expInfo << endl;
        cout << "RunTest failed!" << endl;
        return;
    }

    cout << "Cann't find a solution!RunTest Failed!" << endl;
}


