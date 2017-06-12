//
//  BoughtSetsAndNum.cpp
//  KidTracer
//
//  Created by user on 14-10-22.
//
//

#include "BoughtSetsAndNum.h"


int* BoughtSetsAndNum::getBoughtSets()
{
    return boughtSets;
}

int BoughtSetsAndNum::getBoughtNum()
{
    return boughtNum;
}

void BoughtSetsAndNum::setBoughtSet(int* newSet)
{
    this->boughtSets = newSet;
}

void BoughtSetsAndNum::setBOughtNum(int newNum)
{
    this->boughtNum = newNum;
}

BoughtSetsAndNum::BoughtSetsAndNum(int* set, int num)
{
    this->boughtSets = set;
    this->boughtNum = num;
}