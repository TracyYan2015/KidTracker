//
//  BoughtSetsAndNum.h
//  KidTracer
//
//  Created by user on 14-10-22.
//
//

#ifndef __KidTracer__BoughtSetsAndNum__
#define __KidTracer__BoughtSetsAndNum__

#include <iostream>

class BoughtSetsAndNum
{
private:
    int* boughtSets;
    int boughtNum;
    
public:
    BoughtSetsAndNum(int* set, int num);
    int* getBoughtSets();
    int getBoughtNum();
    
    void setBoughtSet(int* newSets);
    void setBOughtNum(int newNum);
};

#endif /* defined(__KidTracer__BoughtSetsAndNum__) */
