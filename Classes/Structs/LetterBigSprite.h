//
//  LetterBigSprite.h
//  NabuzaI
//
//  Created by Lee Samgu on 8/20/13.
//
//

#ifndef __NabuzaI__LetterBigSprite__
#define __NabuzaI__LetterBigSprite__

#include "cocos2d.h"
USING_NS_CC;

class LetterBigSprite : public cocos2d::CCSprite
{
private:
    SEL_CallFunc selector;
public:
    static LetterBigSprite* createWithPosition(CCPoint pt, SEL_CallFunc selector);
    void runAnimation();
};

#endif /* defined(__NabuzaI__LetterBigSprite__) */
