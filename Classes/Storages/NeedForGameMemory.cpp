//
//  NeedForGameMemory.cpp
//  NabuzaI
//
//  Created by Lee Samgu on 7/18/13.
//
//

#include "NeedForGameMemory.h"

static NeedForGameMemory *s_SharedNeedForGameMemory = NULL;

NeedForGameMemory::NeedForGameMemory() {
    
}

NeedForGameMemory* NeedForGameMemory::sharedNeedForGameMemory(void)
{
    if (!s_SharedNeedForGameMemory)
    {
        s_SharedNeedForGameMemory = new NeedForGameMemory();
        s_SharedNeedForGameMemory->init();
    }
    
    return s_SharedNeedForGameMemory;
}

bool NeedForGameMemory::init()
{
    this->reset();
    
    return true;
}

#pragma mark -
#pragma mark Getters / Setters

void NeedForGameMemory::setJadeCount(unsigned int v) {
    this->jadeCount = v;
}

unsigned int NeedForGameMemory::getJadeCount() {
    return this->jadeCount;
}

void NeedForGameMemory::setCardCount(int v) {
    this->cardCount = v;
}

unsigned int NeedForGameMemory::getCardCount() {
    return this->cardCount;
}

void NeedForGameMemory::reset() {
    this->jadeCount  = 0;
    this->cardCount = 0;
}

void NeedForGameMemory::addJadeCount(unsigned int v) {
    this->jadeCount += v;
}

void NeedForGameMemory::minusJadeCount(unsigned int v) {
    this->jadeCount -= v;
}