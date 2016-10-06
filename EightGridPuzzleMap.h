#ifndef _EIGHT_GRID_PUZZLE_MAP_H_
#define _EIGHT_GRID_PUZZLE_MAP_H_

#include <iostream>

using namespace std;

template <typename MAP_ELE_TYPE, unsigned long long MAP_ELE_NUM>
class EgpMap
{
private:
    MAP_ELE_TYPE m_acElements[MAP_ELE_NUM];
    unsigned long m_ulWidth;
    unsigned long m_ulHeight;

private:
    unsigned long long CoordinateToEleVectorIndex(unsigned long ulX, unsigned long ulY) const
    {
        return ulY * m_ulWidth + ulX;
    }

    void MapTypeCheck(const EgpMap &objEgpMap) const
    {
        if ((0 == m_ulWidth) && (0 == m_ulHeight))
        {
            return;
        }
        
        if ((GetMapEleNum() != objEgpMap.GetMapEleNum()) || 
            (m_ulWidth != objEgpMap.m_ulWidth) || (m_ulHeight != objEgpMap.m_ulHeight))
        {
            throw "MapTypeCheck para error!";
        }
    }

    void MapCopy(const EgpMap &objEgpMap)
    {
        MapTypeCheck(objEgpMap);

        for (unsigned long long ulEleIndex = 0; ulEleIndex < MAP_ELE_NUM; ulEleIndex++)
        {
            m_acElements[ulEleIndex] = objEgpMap.m_acElements[ulEleIndex];
        }

        m_ulWidth = objEgpMap.m_ulWidth;
        m_ulHeight = objEgpMap.m_ulHeight;
    }

public:

    unsigned long GetWidth() const {return m_ulWidth;}
    unsigned long GetHeight() const {return m_ulHeight;}

    unsigned long long GetMapEleNum() const {return MAP_ELE_NUM;}

    MAP_ELE_TYPE GetEle(unsigned long ulX, unsigned long ulY) const 
    {
        if ((ulX >= m_ulWidth) || (ulY >= m_ulHeight))
        {
            throw ("GetEle: Para(ulX or ulY) out of bounds!\n");
        }
        
        return m_acElements[CoordinateToEleVectorIndex(ulX, ulY)];
    }

    void SetEle(unsigned long ulX, unsigned long ulY, MAP_ELE_TYPE newMapEle)
    {
        if ((ulX >= m_ulWidth) || (ulY >= m_ulHeight))
        {
            throw ("SetEle: Para(ulX or ulY) out of bounds!\n");
        }

        m_acElements[CoordinateToEleVectorIndex(ulX, ulY)] = newMapEle;
    }

    EgpMap(MAP_ELE_TYPE acElements[MAP_ELE_NUM], unsigned long ulWidth, unsigned long ulHeight)
    {
        if (ulWidth * ulHeight != MAP_ELE_NUM)
        {
            throw "ulWidth * ulHeight != MAP_ELE_NUM!";
        }
    
        for (unsigned long long ulEleIndex = 0; ulEleIndex < MAP_ELE_NUM; ulEleIndex++)
        {
            m_acElements[ulEleIndex] = acElements[ulEleIndex];
        }

        m_ulWidth = ulWidth;
        m_ulHeight = ulHeight;
    }

    EgpMap(const EgpMap &objEgpMap)
    {
        //MapCopy(objEgpMap);
        //cout << "EgpMap(const EgpMap &objEgpMap)" << endl;
        if (GetMapEleNum() == objEgpMap.GetMapEleNum())
        {
            for (unsigned long long ulEleIndex = 0; ulEleIndex < MAP_ELE_NUM; ulEleIndex++)
            {
                m_acElements[ulEleIndex] = objEgpMap.m_acElements[ulEleIndex];
            }

            m_ulWidth = objEgpMap.m_ulWidth;
            m_ulHeight = objEgpMap.m_ulHeight;
        }
        else
        {
            throw "EgpMap(const EgpMap &objEgpMap): Not a same type for copy!";
        }
    }

    EgpMap(unsigned long ulWidth, unsigned long ulHeight)
    {
        m_ulWidth = ulWidth;
        m_ulHeight = ulHeight;
    }

    EgpMap()
    {
        m_ulWidth = 0;
        m_ulHeight = 0;
    }

    EgpMap & operator=(const EgpMap &objEgpMap)
    {
        //cout << "EgpMap & operator=(const EgpMap &objEgpMap)" << endl;
        MapCopy(objEgpMap);

        return *this;
    }

    bool operator==(const EgpMap &objEgpMap) const
    {
        MapTypeCheck(objEgpMap);

        for (unsigned long long ulEleIndex = 0; ulEleIndex < MAP_ELE_NUM; ulEleIndex++)
        {
            if (m_acElements[ulEleIndex] != objEgpMap.m_acElements[ulEleIndex])
            {
                return false;
            }
        }

        return true;
    }

    int operator-(const EgpMap &objEgpMap)
    {
        MapTypeCheck(objEgpMap);
        
        int iDifScore = 0;
        
        for (unsigned long long ulEleIndex = 0; ulEleIndex < MAP_ELE_NUM; ulEleIndex++)
        {
            if (m_acElements[ulEleIndex] != objEgpMap.m_acElements[ulEleIndex])
            {
                iDifScore++;
            }
        }

        return iDifScore;
    }
};

#endif
