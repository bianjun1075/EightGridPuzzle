#ifndef _EIGHT_GRID_PUZZLE_H_
#define _EIGHT_GRID_PUZZLE_H_

#include <assert.h>
#include "EightGridPuzzleMap.h"

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
    //const EgpMap<char, 9> *m_pEgpMap;

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
        //m_pEgpMap = objEgpNode.m_pEgpMap;
    }

    void ObjCheck(const EgpMap<char, 9> & objEgpMap, unsigned long ulX, unsigned long ulY)
    {
        if ((ulX >= objEgpMap.GetWidth()) || (ulY >= objEgpMap.GetHeight()))
        {
            throw "EgpNode: ObjCheck para error!";
        }
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
        //m_pEgpMap = NULL;
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

    void Show()
    {
        cout << "obj(" << m_ulX << "," << m_ulY << "): " << endl;
        cout << "m_iFn = " << m_iFn;
        cout << "m_iGn = " << m_iFn;
        cout << "m_iHn = " << m_iFn << endl;
    }

    int GetFn() const {return m_iFn;}
    int GetHn() const {return m_iHn;}
    int GetGn() const {return m_iGn;}
        
    void CalcFn(const EgpNode *pobjPreEgpNode, const EgpMap<char, 9> *pEgpMap)
    {
        m_pobjPreEgpNode = pobjPreEgpNode;
        //m_pEgpMap = pEgpMap;
    }

    
};

#endif
