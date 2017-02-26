#pragma once


class CLineKongRandom  
{
public:
    CLineKongRandom(){m_unSeed = 0;};
    ~CLineKongRandom(){};
    
    //--------------------------------------------------------------------
    // �������������
    void SetSeed(unsigned int unSeed)
    {
        m_unSeed = unSeed;
    }
    
    //--------------------------------------------------------------------
    // ����һ�������
    unsigned int Random()
    {
        unsigned int next = m_unSeed;
        unsigned int result;
        
        next *= 1103515245;
        next += 12345;
        result = (unsigned int) (next >> 16) % 2048;
        
        next *= 1103515245;
        next += 12345;
        result <<= 10;
        result ^= (unsigned int) (next >> 16) % 1024;
        
        next *= 1103515245;
        next += 12345;
        result <<= 10;
        result ^= (unsigned int) (next >> 16) % 1024;
        
        m_unSeed = next;
        
        return result;
    }
    
    //--------------------------------------------------------------------
    // ����һ��[0, unRange - 1]֮��������
    unsigned int Random(unsigned int unRange)
    {
        if (unRange == 0)
            return 0;
        
        return Random() % unRange;
    }
    
    // ����һ��[unMinRange, unMaxRange - 1]֮��������
    unsigned int Random(unsigned int unMinRange, unsigned int unMaxRange)
    {
        if(unMinRange == unMaxRange)
            return unMaxRange;
        
        return Random(unMaxRange - unMinRange) + unMinRange;
    }
    
private:
    unsigned int m_unSeed;
};


