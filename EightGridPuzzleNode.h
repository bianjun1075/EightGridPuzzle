#ifndef _EIGHT_GRID_PUZZLE_H_
#define _EIGHT_GRID_PUZZLE_H_

#include <iostream>
#include <vector>
#include <assert.h>
#include "EightGridPuzzleMap.h"

using namespace std;

class EgpNode
{
private:
    EgpMap<char, 9> m_objEgpMap;
    unsigned long m_ulX;
    unsigned long m_ulY;

    int m_iFn;
    int m_iGn;
    int m_iHn;

private:
    const EgpNode *m_pobjPreEgpNode;
    const EgpMap<char, 9> *m_pEgpMap;

private:
    void ObjCopy(const EgpNode & objEgpNode)
    {
        m_objEgpMap = objEgpNode.m_objEgpMap;
        m_ulX = objEgpNode.m_ulX;
        m_ulY = objEgpNode.m_ulY;

        m_iFn = objEgpNode.m_iFn;
        m_iGn = objEgpNode.m_iGn;
        m_iHn = objEgpNode.m_iHn;

        m_pobjPreEgpNode = objEgpNode.m_pobjPreEgpNode;
        m_pEgpMap = objEgpNode.m_pEgpMap;
    }

    void ObjCheck(const EgpMap<char, 9> & objEgpMap, unsigned long ulX, unsigned long ulY)
    {
        if ((ulX >= objEgpMap.GetWidth()) || (ulY >= objEgpMap.GetHeight()))
        {
            cout << "objEgpMap.GetWidth() = " << objEgpMap.GetWidth() << ", ";
            cout << "objEgpMap.GetHeight() = " << objEgpMap.GetHeight() << ", " << endl;
            cout << "(" << ulX << ", " << ulY << ")" << endl;
            throw "EgpNode: ObjCheck para error!";
        }
    }

    void CalcGn(const EgpMap<char, 9> *pEgpMap)
    {
        m_iGn = m_objEgpMap - *pEgpMap;
    }
    
    void CalcHn(const EgpNode *pobjPreEgpNode)
    {
        if ((this == pobjPreEgpNode) || (NULL == pobjPreEgpNode))
        {
            return;
        }

        m_iHn = pobjPreEgpNode->m_iHn + 1;
    }

    void InitScores()
    {
        m_iFn = 0;
        m_iGn = 0;
        m_iHn = 0;
    }

public:
    EgpNode(const EgpMap<char, 9> & objEgpMap, unsigned long ulX, unsigned long ulY)
    {
        ObjCheck(objEgpMap, ulX, ulY);
            
        m_objEgpMap = objEgpMap;
        m_ulX = ulX;
        m_ulY = ulY;

        m_iFn = 0;
        m_iGn = 0;
        m_iHn = 0;

        m_pobjPreEgpNode = NULL;
        m_pEgpMap = NULL;
    }
    
    EgpNode(const EgpNode & objEgpNode)
    {
        ObjCopy(objEgpNode);
    }

    EgpNode& operator=(const EgpNode & objEgpNode)
    {
        ObjCopy(objEgpNode);
        return *this;
    }

    bool operator==(const EgpNode & objEgpNode)
    {
        return ((m_objEgpMap == objEgpNode.m_objEgpMap) && 
            (m_ulX == objEgpNode.m_ulX) && (m_ulY == objEgpNode.m_ulY) && 
            (m_iFn == objEgpNode.m_iFn) && (m_iGn == objEgpNode.m_iGn) && (m_iHn == objEgpNode.m_iHn) &&
            (m_pobjPreEgpNode == m_pobjPreEgpNode));
    }

    bool operator<(const EgpNode &objEgpNode)
    {
        return (m_iFn < objEgpNode.m_iFn);
    }

    void Show()
    {
        cout << "obj(" << m_ulX << "," << m_ulY << "): " << endl;
        cout << "m_iFn = " << m_iFn;
        cout << ", m_iGn = " << m_iGn;
        cout << ", m_iHn = " << m_iHn << endl;
    }

    int GetFn() const {return m_iFn;}
    int GetHn() const {return m_iHn;}
    int GetGn() const {return m_iGn;}

    const EgpNode *GetPreNode() const { return m_pobjPreEgpNode;}
        
    void CalcFn(const EgpNode *pobjPreEgpNode, const EgpMap<char, 9> *pEgpMap)
    {
        assert(NULL != pEgpMap);
        
        m_pobjPreEgpNode = pobjPreEgpNode;
        m_pEgpMap = pEgpMap;

        InitScores();
        CalcGn(pEgpMap);
        CalcHn(pobjPreEgpNode);

        m_iFn = m_iGn + m_iHn;
    }

    bool IsMapEqualTo(const EgpNode& objNode){return (m_objEgpMap == objNode.m_objEgpMap);}

    bool IsMapEqualTo(const EgpMap<char, 9>& objEgpMap) {return (m_objEgpMap == objEgpMap);}

    bool IsInList(const vector<EgpNode>& vcList)
    {
        for (auto i : vcList)
        {
            if (IsMapEqualTo(i))
            {
                return true;
            }
        }

        return false;
    }


    void AddNodeToList(EgpNode objEgpNode, vector<EgpNode>& vcOpenList, vector<EgpNode>& vcClosedList);
        
    void AddNextPossStepsToList(vector<EgpNode>& vcOpenList, vector<EgpNode>& vcClosedList);
    
};

#endif

